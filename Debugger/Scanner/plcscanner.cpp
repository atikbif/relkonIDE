#include "plcscanner.h"
#include <QThread>
#include "Protocols/asciidecorator.h"
#include <QDateTime>
#include "Protocols/rk.h"

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
        str.toUpper();
         message+=str.toUpper() + " ";
    }
    return message;
}

void PLCScanner::startReq(QSerialPort &port)
{
    // чтение времени
    CommandInterface* cmd = new ReadTime();
    if(cmd!=nullptr) {
        Request req;
        req.setNetAddress(settings.getNetAddress());
        req.setMemAddress(0);
        req.setDataNumber(7);
        if(settings.getComSettings().protocol=="ASCII") cmd = new AsciiDecorator(cmd);
        req.setNetAddress(settings.getNetAddress());
        if(cmd->execute(req,port)) {
            emit updateCorrectRequestCnt(++cntCorrect);
            int secs = (req.getRdData().at(0) & 0x0F) + 10*(req.getRdData().at(0)>>4);
            QString secStr = QString::number(secs);if(secStr.size()<2) secStr = "0"+secStr;
            int mins = (req.getRdData().at(1) & 0x0F) + 10*(req.getRdData().at(1)>>4);
            QString minStr = QString::number(mins);if(minStr.size()<2) minStr = "0"+minStr;
            int hours = (req.getRdData().at(2) & 0x0F) + 10*(req.getRdData().at(2)>>4);
            QString hourStr = QString::number(hours);if(hourStr.size()<2) hourStr = "0"+hourStr;
            QString plcTime = hourStr + ":" + minStr + ":" + secStr;
            emit updateTimeStr(plcTime);
        }else
        {
            emit updateErrorRequestCnt(++cntError);
        }
        emit addMessage(reqToHexStr(req));
    }
    delete cmd;
}

PLCScanner::PLCScanner(QObject *parent) : QObject(parent)
{
    startCmd=false;
    stopCmd=false;
    finishCmd = false;
    scheduler = nullptr;
    cntCorrect = 0;
    cntError = 0;
}

PLCScanner::~PLCScanner()
{

}

void PLCScanner::scanProcess()
{
    int cmdCnt=0;   // счётчик для периодического включения системных запросов
    QSerialPort port;
    forever{
        QThread::msleep(1);
        mutex.lock();
        if(finishCmd) { // завершение процесса
            port.close();
            startCmd=false;
            stopCmd=false;
            finishCmd=false;
            mutex.unlock();
            break;
        }
        if(startCmd) {
            // открытие порта если он закрыт
            if(!port.isOpen()) {
                port.setPortName(settings.getComSettings().portName);
                port.setBaudRate(settings.getComSettings().baudrate);
                if(!port.open(QSerialPort::ReadWrite)) {
                    // ошибка открытия порта
                    emit addMessage(QDateTime::currentDateTime().time().toString() + ": невозможно открыть порт " + port.portName());
                    QThread::msleep(1000);
                }
                cmdCnt=0;
            }
            if(stopCmd) {   // приостановить опрос
                port.close();
                stopCmd=false;
                startCmd=false;
                mutex.unlock();
            }
            else {
                // опрос контроллера
                mutex.unlock();
                QThread::msleep(1);
                if((scheduler!=nullptr)&&(port.isOpen())) {
                    // получение команды и запроса от планировщика
                    CommandInterface* cmd = scheduler->getCmd();
                    if(cmd!=nullptr) {
                        Request req = scheduler->getReq();
                        if(settings.getComSettings().protocol=="ASCII") cmd = new AsciiDecorator(cmd);
                        req.setNetAddress(settings.getNetAddress());
                        if(cmd->execute(req,port)) {
                            emit updateCorrectRequestCnt(++cntCorrect);
                            // обновление памяти по результатам чтения
                            if(req.hasKey("mem") && req.hasKey("rw") && req.getParam("rw")=="read") {
                                emit updateBlock(req.getParam("mem"),req.getMemAddress(),req.getRdData());
                            }
                        }else emit updateErrorRequestCnt(++cntError);
                        // вывод сообщения в лог
                        emit addMessage(reqToHexStr(req));
                    }
                    // переместить планировщик на следущие команду и запрос
                    scheduler->moveToNext();
                    // периодический вызов системных команд
                    if(cmdCnt==0) startReq(port);
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


