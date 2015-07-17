#include "plcscanner.h"
#include <QThread>

PLCScanner::PLCScanner(QObject *parent) : QObject(parent)
{
    startCmd=false;
    stopCmd=false;
    finishCmd = false;
}

PLCScanner::~PLCScanner()
{

}

void PLCScanner::scanProcess()
{
    static int a=0;
    forever{
        mutex.lock();
        if(finishCmd) {startCmd=false;stopCmd=false;finishCmd=false;mutex.unlock();break;}
        if(startCmd) {
            if(stopCmd) {stopCmd=false;startCmd=false;mutex.unlock();}
            else {
                mutex.unlock();
                QThread::msleep(1000);
                QByteArray data;
                data[0] = a++;
                data[1] = a>>8;
                emit updateBlock("RAM",0,data);
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


