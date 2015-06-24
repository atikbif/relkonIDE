#include "ymodem.h"
#include <QThread>
#include <QMutexLocker>
#include "Protocols/checksum.h"
#include <QFile>

bool Ymodem::sendHeader()
{
    if(port!=nullptr) {
        if(port->isOpen()) {
            QByteArray txBuf(3+128,'\0');
            txBuf[0] = 0x01;
            txBuf[1] = 0x00;
            txBuf[2] = 0xFF;
            QString fName = "project.bin";
            for(int i=0;i<fName.size();i++) {
                txBuf[3+i] = fName.toUtf8().at(i);
            }

            QString fSize = QString::number(file->size());
            for(int i=0;i<fSize.size();i++) {
                txBuf[4+fName.size()+i] = fSize.toUtf8().at(i);
            }
            int crc = CheckSum::getCRCXModem(txBuf.mid(3,128));
            txBuf += crc >> 8;
            txBuf += crc & 0xFF;

            QByteArray answer;

            for(int j=0;j<3;j++) {
                answer.clear();
                port->write(txBuf);
                port->waitForBytesWritten(100);
                port->waitForReadyRead(1500);
                answer+=port->readAll();
                if(answer.count()) {
                    if(answer.contains(0x06)&&answer.contains('C')) return true;
                }
            }
        }
    }
    return false;
}

bool Ymodem::sendStartYmodem()
{
    if(port!=nullptr) {
        if(port->isOpen()) {
            int maxCnt = 20;
            int cnt=0;

            port->write("1",1);
            port->waitForBytesWritten(100);
            emit percentUpdate(1);
            QByteArray answer;
            while(port->waitForReadyRead(100)) {
                port->readAll();
                cnt++;if(cnt>=maxCnt) break;
            }
            port->waitForReadyRead(1500);
            answer+=port->readAll();
            if(answer.contains(0x43)) return true;
        }
    }
    return false;
}

bool Ymodem::sendData(int reqNum)
{
    if(port!=nullptr) {
        if(port->isOpen()) {
            QByteArray txBuf;
            txBuf[0] = 0x02;
            txBuf[1] = reqNum & 0xFF;
            txBuf[2] = 0xFF - txBuf[1];
            if(file->isOpen()) {
                file->seek((reqNum-1)*1024);
                QByteArray dataBlock = file->read(1024);
                int delta = 1024 - dataBlock.count();
                if(delta) dataBlock += QByteArray(delta,'\0');

                txBuf += dataBlock;
                int crc = CheckSum::getCRCXModem(dataBlock);
                txBuf += crc >> 8;
                txBuf += crc & 0xFF;

                QByteArray answer;

                for(int j=0;j<3;j++) {
                    answer.clear();
                    port->write(txBuf);
                    port->waitForBytesWritten(150);
                    port->waitForReadyRead(150);
                    answer+=port->readAll();
                    if(answer.count()) {
                        if(answer.contains(0x06)) return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Ymodem::sendEOT()
{
    if(port!=nullptr) {
        if(port->isOpen()) {
            QByteArray tx;
            tx+= 0x04;
            port->write(tx);
            port->waitForBytesWritten(100);

            QByteArray answer;
            port->waitForReadyRead(100);
            answer+=port->readAll();
            if(answer.contains(0x06) && answer.contains('C')) return true;
        }
    }
    return false;
}

bool Ymodem::sendLastReq()
{
    if(port!=nullptr) {
        if(port->isOpen()) {
            QByteArray txBuf(3+128,'\0');
            txBuf[0] = 0x01;
            txBuf[1] = 0x00;
            txBuf[2] = 0xFF;
            int crc = CheckSum::getCRCXModem(txBuf.mid(3,128));
            txBuf += crc >> 8;
            txBuf += crc & 0xFF;

            QByteArray answer;

            for(int j=0;j<3;j++) {
                answer.clear();
                port->write(txBuf);
                port->waitForBytesWritten(100);
                port->waitForReadyRead(1500);
                answer+=port->readAll();
                if(answer.count()) {
                    if(answer.contains(0x06)) return true;
                }
            }
        }
    }
    return false;
}

Ymodem::Ymodem(QObject *parent) : QObject(parent)
{
    stopCmd = false;
    port = nullptr;
    file = nullptr;
}

Ymodem::~Ymodem()
{
    delete port;
    delete file;
}

void Ymodem::stopProcess()
{
    QMutexLocker locker(&mutex);
    stopCmd = true;
}

void Ymodem::startProcess(const QString &pName, const QString &filePath)
{
    file = new QFile(filePath);
    if(file->open(QIODevice::ReadOnly)) {
        port = new QSerialPort(pName);
        port->setBaudRate(QSerialPort::Baud115200);
        if(port->open(QSerialPort::ReadWrite)) {
            bool errFlag = false;
            if(sendStartYmodem()) {
                if(sendHeader()) {
                    int byteQuantity = file->size();
                    int reqQuantity = byteQuantity / 1024;
                    if(byteQuantity % 1024) reqQuantity++;
                    float curPercent = 0;
                    float stepPercent = 100/(float)reqQuantity;
                    for(int i=1;i<=reqQuantity;i++) {
                        mutex.lock();
                        if(stopCmd) {mutex.unlock();break;}
                        mutex.unlock();
                        if(sendData(i)==false) {
                            emit bootError("Ошибка передачи файла");
                            errFlag = true;
                            break;
                        }
                        curPercent+=stepPercent;
                        emit percentUpdate(curPercent);
                    }
                    QMutexLocker locker(&mutex);
                    if(stopCmd) {
                        port->close();
                        file->close();
                        return;
                    }
                    locker.unlock();
                    if(errFlag==false) {
                        sendEOT();
                        sendLastReq();
                        emit finished();
                    }
                }else {
                    emit bootError("Ошибка передачи параметров файла контроллеру");
                }
            }else
            {
                emit bootError("Контроллер не готов к приёму данных");
            }
            port->close();
        }
        file->close();
    }
}

