#include "requestscheduler.h"
#include "Protocols/rk.h"

using namespace RkProtocol;

RequestScheduler::RequestScheduler(QObject *parent) : QObject(parent)
{
    i = 0;
}

CommandInterface *RequestScheduler::getCmd()
{
    QMutexLocker locker(&mutex);
    CommandInterface* ptr = nullptr;
    if(cmdQueue.count()) {
        ptr = cmdQueue.at(i)->cmd;
    }
    return ptr;
}

Request RequestScheduler::getReq()
{
    QMutexLocker locker(&mutex);
    Request r;
    if(cmdQueue.count()) {
        r = *(cmdQueue.at(i)->req);
    }
    return r;
}

void RequestScheduler::moveToNext()
{
    QMutexLocker locker(&mutex);
    i++;
    if(i>=cmdQueue.count()) i=0;
}

void RequestScheduler::addReadOperation(VarItem v)
{
    QMutexLocker locker(&mutex);
    CommandInterface* cmd = nullptr;
    if(v.getPriority()==0) return;
    int cnt = 0;
    if(v.getDataType().contains("char")) cnt=1;
    else if(v.getDataType().contains("short")) cnt=2;
    else if(v.getDataType().contains("int")) cnt=4;
    else if(v.getDataType().contains("long long")) cnt=8;
    else if(v.getDataType().contains("long")) cnt=4;
    else if(v.getDataType().contains("float")) cnt=4;
    else if(v.getDataType().contains("double")) cnt=8;
    if(v.getMemType()=="RAM") {
        cmd = new ReadRam();
    }else if(v.getMemType()=="FRAM") {
        cmd = new ReadFram();
    }
    if(cmd!=nullptr) {
        Request* req = new Request();
        req->setDataNumber(cnt);
        req->setMemAddress(v.getMemAddress());
        CmdData* cmdStruct = new CmdData;
        cmdStruct->cmd = cmd;
        cmdStruct->req = req;
        cmdQueue += cmdStruct;
    }
}

void RequestScheduler::removeReadOperation(VarItem v)
{
    Q_UNUSED(v)
}

void RequestScheduler::addWriteOperation(VarItem v)
{
    Q_UNUSED(v)
}

void RequestScheduler::clearQueue()
{
    QMutexLocker locker(&mutex);
    i=0;
    foreach (CmdData* cmdStruct, cmdQueue) {
       delete cmdStruct->cmd;
       delete cmdStruct->req;
       delete cmdStruct;
    }
    cmdQueue.clear();
}

void RequestScheduler::schedule()
{

}

RequestScheduler::~RequestScheduler()
{
    foreach (CmdData* cmdStruct, cmdQueue) {
       delete cmdStruct->cmd;
       delete cmdStruct->req;
       delete cmdStruct;
    }
}

