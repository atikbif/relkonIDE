#include "cleanmanager.h"

CleanManager::CleanManager(QObject *parent): QObject(parent)
{
    cleaner = new CleanProcess();
    cleaner->moveToThread(&cleanThread);
    connect(&cleanThread,SIGNAL(finished()),cleaner,SLOT(deleteLater()));
    connect(this,SIGNAL(startProcess()),cleaner,SLOT(startProcess()));
    cleanThread.start();
    emit startProcess();
}

CleanManager::~CleanManager()
{
    cleaner->finishProcess();
    cleanThread.quit();
    cleanThread.wait();
}

void CleanManager::startClean()
{
    cleaner->startClean();
}
