#include "plcscanner.h"
#include <QThread>
#include "AutoSearch/detectedcontroller.h"
#include "Protocols/asciidecorator.h"
#include <QMessageBox>
#include <QDateTime>
#include "Protocols/rk.h"

using namespace RkProtocol;

QString PLCScanner::reqToHexStr(Request &req)
{
    QString message = QDateTime::currentDateTime().time().toString()+":";
    QString msStr = QString::number(QDateTime::currentMSecsSinceEpoch()%1000);
    while(msStr.size()<3) msStr = "0" + msStr;
    message+=msStr;
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
    //CommandInterface* cmd = new GetCoreVersion();
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
            emit addMessage(reqToHexStr(req));
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
            emit addMessage(reqToHexStr(req));
        }
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
    //DetectedController* plc = &DetectedController::Instance();
    int cmdCnt=0;
    QSerialPort port;
    forever{
        mutex.lock();
        if(finishCmd) {port.close();startCmd=false;stopCmd=false;finishCmd=false;mutex.unlock();break;}
        if(startCmd) {
            if(!port.isOpen()) {
                port.setPortName(settings.getComSettings().portName);
                port.setBaudRate(settings.getComSettings().baudrate);
                if(!port.open(QSerialPort::ReadWrite)) {
                    emit addMessage(QDateTime::currentDateTime().time().toString() + ": невозможно открыть порт " + port.portName());
                    QThread::msleep(1000);
                }
                cmdCnt=0;
            }
            if(stopCmd) {port.close();stopCmd=false;startCmd=false;mutex.unlock();}
            else {
                mutex.unlock();
                QThread::msleep(1);
                if((scheduler!=nullptr)&&(port.isOpen())) {
                    CommandInterface* cmd = scheduler->getCmd();
                    if(cmd!=nullptr) {
                        Request req = scheduler->getReq();
                        if(settings.getComSettings().protocol=="ASCII") cmd = new AsciiDecorator(cmd);
                        req.setNetAddress(settings.getNetAddress());
                        if(cmd->execute(req,port)) {
                            emit updateCorrectRequestCnt(++cntCorrect);
                            if(req.hasKey("mem") && req.hasKey("rw") && req.getParam("rw")=="read") {
                                emit updateBlock(req.getParam("mem"),req.getMemAddress(),req.getRdData());
                            }
                            emit addMessage(reqToHexStr(req));
                        }else
                        {
                            emit updateErrorRequestCnt(++cntError);
                            emit addMessage(reqToHexStr(req));
                        }
                    }
                    scheduler->moveToNext();
                    if(cmdCnt==0) {
                        startReq(port);
                    }
                    cmdCnt++;
                    if(cmdCnt>=10) cmdCnt=0;
                    //delete cmd;
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


