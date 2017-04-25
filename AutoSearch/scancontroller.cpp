#include "scancontroller.h"


ScanController::ScanController(const QString &pName, int progAddr, QObject *parent) : QObject(parent)
{
    this->pName = pName;
    scanWorker = new ScanUART();
    scanWorker->setProgAddr(progAddr);
    scanWorker->moveToThread(&scanThread);
    connect(&scanThread,SIGNAL(finished()),scanWorker,SLOT(deleteLater()));
    connect(scanWorker,SIGNAL(percentUpdate(float)),this,SLOT(percentUpdate(float)));
    connect(scanWorker,SIGNAL(portIsBusy()),this,SLOT(portIsBusy()));
    connect(scanWorker,SIGNAL(plcHasBeenFound(SearchController)),this,SLOT(plcHasBeenFound(SearchController)));
    connect(scanWorker,SIGNAL(scanIsFinished(QString)),this, SIGNAL(finished(QString)));
    connect(this,SIGNAL(startScan(QString)),scanWorker,SLOT(startScan(QString)));
    scanThread.start();
    emit startScan(pName);
}

ScanController::~ScanController()
{
    scanWorker->stopScan();
    scanThread.quit();
    scanThread.wait();
}

void ScanController::percentUpdate(float percValue)
{
    emit updated(percValue,pName);
}

void ScanController::plcHasBeenFound(SearchController plc)
{
    emit found(plc,pName);
}

void ScanController::portIsBusy()
{
    emit portIsBusy(pName);
}

