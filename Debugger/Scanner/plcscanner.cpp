#include "plcscanner.h"
#include <QThread>
#include "AutoSearch/detectedcontroller.h"
#include <QSerialPort>
#include "Protocols/asciidecorator.h"

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
    DetectedController* plc = &DetectedController::Instance();
    QSerialPort port;
    forever{
        mutex.lock();
        if(finishCmd) {port.close();startCmd=false;stopCmd=false;finishCmd=false;mutex.unlock();break;}
        if(startCmd) {
            if(!port.isOpen()) {
                port.setPortName(plc->getUartName());
                port.setBaudRate(plc->getBaudrate());
                port.open(QSerialPort::ReadWrite);
            }
            if(stopCmd) {port.close();stopCmd=false;startCmd=false;mutex.unlock();}
            else {
                mutex.unlock();
                QThread::msleep(1);
                if(scheduler!=nullptr) {
                    CommandInterface* cmd = scheduler->getCmd();
                    if(cmd!=nullptr) {
                        Request req = scheduler->getReq();
                        if(plc->getAsciiMode()) cmd = new AsciiDecorator(cmd);
                        req.setNetAddress(plc->getNetAddress());
                        if(cmd->execute(req,port)) {
                            emit updateCorrectRequestCnt(++cntCorrect);
                            if(req.hasKey("mem") && req.hasKey("rw") && req.getParam("rw")=="read") {
                                emit updateBlock(req.getParam("mem"),req.getMemAddress(),req.getRdData());
                            }
                        }else emit updateErrorRequestCnt(++cntError);
                    }
                    scheduler->moveToNext();
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


