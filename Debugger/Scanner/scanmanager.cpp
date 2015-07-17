#include "scanmanager.h"

ScanManager::ScanManager(MemStorage *memStor, QObject *parent) : QObject(parent)
{
    scanner = new PLCScanner();
    scanner->moveToThread(&scanThread);
    connect(&scanThread,SIGNAL(finished()),scanner,SLOT(deleteLater()));
    connect(this,SIGNAL(startProcess()),scanner,SLOT(scanProcess()));
    connect(scanner,SIGNAL(updateBlock(QString,int,QByteArray)),memStor,SLOT(updateBlock(QString,int,QByteArray)));
    scanThread.start();
    emit startProcess();
}

ScanManager::~ScanManager()
{
    scanner->finishProcess();
    scanThread.quit();
    scanThread.wait();
}

void ScanManager::startDebugger()
{
    scanner->startScanCmd();
}

void ScanManager::stopDebugger()
{
    scanner->stopScanCmd();
}

