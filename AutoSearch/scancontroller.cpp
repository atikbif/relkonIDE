#include "scancontroller.h"


ScanController::ScanController(const QString &pName, QObject *parent) : QObject(parent)
{
    this->pName = pName;
    scanWorker = new ScanUART();
    scanWorker->moveToThread(&scanThread);
    connect(&scanThread,SIGNAL(finished()),scanWorker,SLOT(deleteLater()));
    connect(scanWorker,SIGNAL(percentUpdate(float)),this,SLOT(percentUpdate(float)));
    connect(scanWorker,SIGNAL(plcHasBeenFound(DetectedController*)),this,SLOT(plcHasBeenFound(DetectedController*)));
    connect(scanWorker,SIGNAL(scanIsFinished(QString)),this,SLOT(scanIsFinished(QString)));
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

void ScanController::scanIsFinished(const QString &message)
{
    emit finished(message);
}

void ScanController::plcHasBeenFound(DetectedController* plc)
{
    emit found(plc,pName);
}

