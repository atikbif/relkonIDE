#include "varwatcher.h"
#include <QThread>

VarWatcher::VarWatcher(QObject *parent) : QObject(parent),finishFlag(false)
{

}

void VarWatcher::finishProcess()
{
    finishFlag = true;
}

void VarWatcher::updateProcess()
{
    forever {
        if(finishFlag) break;
        QThread::msleep(100);
        emit quickInfoRequest();
    }
}
