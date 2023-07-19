#include "plcscanner.h"
#include <QThread>
#include "Protocols/asciidecorator.h"
#include "Protocols/udpdecorator.h"
#include <QDateTime>
#include "Protocols/rk.h"
#include <QSerialPort>
#include <QUdpSocket>

using namespace RkProtocol;

QString PLCScanner::reqToHexStr(Request &req)
{
    // текущее время с миллисекундами
    QString message = QDateTime::currentDateTime().time().toString()+":";
    QString msStr = QString::number(QDateTime::currentMSecsSinceEpoch()%1000);
    while(msStr.size()<3) msStr = "0" + msStr;
    message+=msStr;
    // запрос и ответ
    message+=" [TX:] ";
    QByteArray body = req.getBody();
    QString str;
    foreach(quint8 byteValue,body) {
        str = QString::number(byteValue,16);
        if(str.size()<2) str="0"+str;
        message+=str.toUpper() + " ";
    }
    message+="[RX:] ";
    body = req.getAnswerData();
    foreach(quint8 byteValue,body) {
        str = QString::number(byteValue,16);
        if(str.size()<2) str="0"+str;
        message+=str.toUpper() + " ";
    }
    return message;
}

void PLCScanner::startReq(QIODevice &port)
{
    // чтение времени
    CommandInterface* cmd = new ReadTime();
    if(cmd!=nullptr) {
        Request req;
        req.setNetAddress(settings.getNetAddress());
        req.setMemAddress(0);
        req.setDataNumber(7);
        if(isUdp) cmd = new UdpDecorator(cmd);
        else if(settings.getComSettings().protocol=="ASCII") cmd = new AsciiDecorator(cmd);
        req.setNetAddress(settings.getNetAddress());
        if(cmd->execute(req,port)) {
            emit updateCorrectRequestCnt(++cntCorrect);
            int secs = (req.getRdData().at(0) & 0x0F) + 10*(req.getRdData().at(0)>>4);
            QString secStr = QString::number(secs);if(secStr.size()<2) secStr = "0"+secStr;
            int mins = (req.getRdData().at(1) & 0x0F) + 10*(req.getRdData().at(1)>>4);
            QString minStr = QString::number(mins);if(minStr.size()<2) minStr = "0"+minStr;
            int hours = (req.getRdData().at(2) & 0x0F) + 10*(req.getRdData().at(2)>>4);
            QString hourStr = QString::number(hours);if(hourStr.size()<2) hourStr = "0"+hourStr;

            int date = (req.getRdData().at(4) & 0x0F) + 10*(req.getRdData().at(4)>>4);
            QString dateStr = QString::number(date);if(dateStr.size()<2) dateStr = "0"+dateStr;
            int month = (req.getRdData().at(5) & 0x0F) + 10*(req.getRdData().at(5)>>4);
            QString monthStr = QString::number(month);if(monthStr.size()<2) monthStr = "0"+monthStr;
            int year = (req.getRdData().at(6) & 0x0F) + 10*(req.getRdData().at(6)>>4);
            QString yearStr = QString::number(year);if(yearStr.size()<2) yearStr = "0"+yearStr;

            QString plcTime = hourStr + ":" + minStr + ":" + secStr +
                    "   " + dateStr+"."+monthStr+"."+yearStr;
            emit updateTimeStr(plcTime);
        }else
        {
            emit updateErrorRequestCnt(++cntError);
        }
        emit addMessage(reqToHexStr(req));
    }
    delete cmd;
}

PLCScanner::PLCScanner(QObject *parent) : QObject(parent),portOpenError(false)
{
    startCmd=false;
    stopCmd=false;
    finishCmd = false;
    scheduler = nullptr;
    cntCorrect = 0;
    cntError = 0;
    isUdp = true;
}

PLCScanner::~PLCScanner()
{

}

void PLCScanner::scanProcess()
{
    int cmdCnt=0;   // счётчик для периодического включения системных запросов
    QSerialPort port;
    QUdpSocket udp;

    forever{
        isUdp = settings.getUdpFlag();
        QThread::msleep(1);
        mutex.lock();
        if(finishCmd) { // завершение процесса
            if(!isUdp)  {
                port.close();
            }else {
                udp.disconnectFromHost();
                udp.close();
            }
            startCmd=false;
            stopCmd=false;
            finishCmd=false;
            mutex.unlock();
            break;
        }
        if(startCmd) {
            if(!isUdp) {
                // открытие порта если он закрыт
                if(!port.isOpen()) {
                    port.setPortName(settings.getComSettings().portName);
                    port.setBaudRate(settings.getComSettings().baudrate);
                    if(!port.open(QSerialPort::ReadWrite)) {
                        // ошибка открытия порта
                        QString message = QDateTime::currentDateTime().time().toString() + ": невозможно открыть порт " + port.portName();
                        emit addMessage(message);
                        if(portOpenError==false) {emit errMessage(message);}
                        portOpenError=true;
                        QThread::msleep(1000);
                    }else portOpenError=false;
                    cmdCnt=0;
                }
            }else {
                if(!udp.isOpen()) {
                    QString ipAddr = settings.getUdpSettings().ipAddress;
                    if(ipAddr.contains(QRegExp("^\\d{1,3}\\.\\d{1,3}.\\d{1,3}.\\d{1,3}"))) {
                        if(udp.state()==QAbstractSocket::UnconnectedState) {
                            udp.connectToHost(ipAddr,settings.getDefaultUDPPortNum());
                            udp.waitForConnected();
                        }
                    }
                    udp.open(QIODevice::ReadWrite);
                }
            }
            if(stopCmd) {   // приостановить опрос
                    port.close();
                    udp.disconnectFromHost();
                    udp.close();
                stopCmd=false;
                startCmd=false;
                mutex.unlock();
            }
            else {
                // опрос контроллера
                mutex.unlock();
                //QThread::currentThread()->msleep(5);
                if((scheduler!=nullptr)&&(((port.isOpen())&&(!isUdp)) || (isUdp)) ) {
                    // получение команды и запроса от планировщика
                    CommandInterface* cmd = scheduler->getCmd();
                    QIODevice *ptr = nullptr;
                    if(isUdp) ptr = &udp;else ptr = &port;
                    if(cmd!=nullptr) {
                        Request req = scheduler->getReq();
                        if(isUdp) cmd = new UdpDecorator(cmd);
                        else if(settings.getComSettings().protocol=="ASCII") cmd = new AsciiDecorator(cmd);
                        req.setNetAddress(settings.getNetAddress());
                        bool checkFlag = false;
                        for(int i=0;i<5;i++) {
                            if(cmd->execute(req,*ptr)) {
                                emit updateCorrectRequestCnt(++cntCorrect);
                                // обновление памяти по результатам чтения
                                if(req.hasKey("mem") && req.hasKey("rw") && req.getParam("rw")=="read") {
                                    emit updateBlock(req.getParam("mem"),req.getMemAddress(),req.getRdData());
                                }
                                checkFlag = true;
                                break;
                            }
                        }
                        if(checkFlag==false) emit updateErrorRequestCnt(++cntError);

                        // вывод сообщения в лог
                        emit addMessage(reqToHexStr(req));
                    }
                    // переместить планировщик на следущие команду и запрос
                    scheduler->moveToNext();
                    // периодический вызов системных команд
                    if(cmdCnt==0) startReq(*ptr);
                    cmdCnt++;if(cmdCnt>=sysReqPeriod) cmdCnt=0;
                    delete cmd;
                }
            }
        }else mutex.unlock();
    }
}

void PLCScanner::startScanCmd()
{
    QMutexLocker locker(&mutex);
    startCmd = true;
    stopCmd = false;
    portOpenError = false;
}

void PLCScanner::stopScanCmd()
{
    QMutexLocker locker(&mutex);
    stopCmd = true;

}

void PLCScanner::finishProcess()
{
    QMutexLocker locker(&mutex);
    finishCmd = true;
}

void PLCScanner::setScheduler(RequestScheduler *ptr)
{
    scheduler = ptr;
}


