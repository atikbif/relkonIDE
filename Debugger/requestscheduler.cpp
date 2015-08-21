#include "requestscheduler.h"
#include "Protocols/rk.h"
#include "varbytesvalueconverter.h"

using namespace RkProtocol;

void RequestScheduler::clearBin()
{
    foreach (CmdData* cmdStruct, binQueue) {
       delete cmdStruct->cmd;
       delete cmdStruct->req;
       delete cmdStruct;
    }
    binQueue.clear();
}

CommandInterface *RequestScheduler::getRdCmdByMemType(const QString &memType)
{
    CommandInterface* ptr = nullptr;
    if(memType=="RAM") ptr = new ReadRam();
    else if(memType=="FRAM") ptr = new ReadFram();
    else if(memType=="IO") ptr = new ReadIO();
    else if(memType=="USER") ptr = new ReadDispRam();
    return ptr;
}

CommandInterface *RequestScheduler::getWrCmdByMemType(const QString &memType)
{
    CommandInterface* ptr = nullptr;
    if(memType=="RAM") ptr = new WriteRam();
    else if(memType=="FRAM") ptr = new WriteFram();
    else if(memType=="TIME") ptr = new WriteTime();
    else if(memType=="IO") ptr = new WriteIO();
    else if(memType=="USER") ptr = new WriteDispRam();
    return ptr;
}

void RequestScheduler::scanMap(const QString &memType)
{
    QBitArray map = devMap.value(memType);
    if(map.count()) {
        int startAddr=-1;
        int stopAddr=-1;
        int holeCnt=0;
        int i=0;

        while(1) {
            startAddr = -1;
            stopAddr = -1;
            holeCnt = 0;
            if(i>=map.count()) break;
            while (1) {
               if(map.at(i)) {
                   holeCnt=0;
                   if(startAddr<0) startAddr = i;
                   if(startAddr>=0) {
                      if(i-startAddr+1>maxLength) break;
                      stopAddr = i;
                   }

               }else {
                   if(startAddr>=0) {
                       holeCnt++;
                       if(holeCnt>=maxHole) break;
                   }
               }
               i++;
               if(i>=map.count()) break;
            }
            if(startAddr>=0) {  // new request
                CommandInterface* cmd = getRdCmdByMemType(memType);
                if(cmd!=nullptr) {
                    Request* req = new Request();
                    req->setDataNumber(stopAddr-startAddr+1);
                    req->setMemAddress(startAddr);
                    CmdData* cmdStruct = new CmdData;
                    cmdStruct->cmd = cmd;
                    cmdStruct->req = req;
                    cmdQueue += cmdStruct;
                }
            }
        }

    }
}

RequestScheduler::RequestScheduler(QObject *parent) : QObject(parent)
{
    i = 0;
    removeWr = false;
    devMap.clear();
}

CommandInterface *RequestScheduler::getCmd()
{
    QMutexLocker locker(&mutex);
    CommandInterface* ptr = nullptr;

    // проверка очереди на запись
    if(wrQueue.count()) {
        ptr = wrQueue.first()->cmd;
        removeWr = true;
    }else if(cmdQueue.count()) {
        ptr = cmdQueue.at(i)->cmd;
    }
    // возвращает новый объект чтобы внешняя программа могла его удалить
    // связано с использованием декораторов
    // т.к. они автоматически удаляют базовые объекты
    if(ptr) return ptr->clone();
    return nullptr;
}

Request RequestScheduler::getReq()
{
    QMutexLocker locker(&mutex);
    Request r;
    // проверка очереди на запись
    if(wrQueue.count()) {
        r = *(wrQueue.first()->req);
        removeWr = true;
    }else if(cmdQueue.count()) {
        r = *(cmdQueue.at(i)->req);
    }
    return r;
}

void RequestScheduler::moveToNext()
{
    QMutexLocker locker(&mutex);
    clearBin();
    if(removeWr) {
        removeWr = false;
        if(wrQueue.count()) {
            CmdData* cmdStruct = wrQueue.first();
            delete cmdStruct->cmd;
            delete cmdStruct->req;
            delete cmdStruct;
            wrQueue.remove(0);
        }
    }
    i++;
    if(i>=cmdQueue.count()) {
        i=0;
    }
}

void RequestScheduler::addReadOperation(VarItem v)
{
    QMutexLocker locker(&mutex);
    int cnt = VarBytesValueConverter::getVarSize(v.getDataType());
    if(v.getPriority()==0) return;
    if(devMap.contains(v.getMemType())) {
        int beginPos = v.getMemAddress();
        int endPos = beginPos+cnt;
        QBitArray map = devMap.value(v.getMemType());
        if(map.size()<endPos) map.resize(endPos);
        map.fill(true,beginPos,endPos);
        devMap.insert(v.getMemType(),map);
    }else {
        QBitArray map(v.getMemAddress()+cnt);
        map.fill(true,v.getMemAddress(),map.count());
        devMap.insert(v.getMemType(),map);
    }

}

void RequestScheduler::removeReadOperation(VarItem v)
{
    QMutexLocker locker(&mutex);
    int cnt = VarBytesValueConverter::getVarSize(v.getDataType());
    if(devMap.contains(v.getMemType())) {
        int beginPos = v.getMemAddress();
        int endPos = beginPos+cnt;
        QBitArray map = devMap.value(v.getMemType());
        if(map.size()<endPos) return;
        map.fill(false,beginPos,endPos);
        devMap.insert(v.getMemType(),map);
    }
}

void RequestScheduler::addWriteOperation(VarItem v)
{
    CommandInterface* cmd = getWrCmdByMemType(v.getMemType());
    if(cmd!=nullptr) {
        int cnt = VarBytesValueConverter::getVarSize(v.getDataType());
        Request* req = new Request();
        req->setDataNumber(cnt);
        req->setMemAddress(v.getMemAddress());
        req->setWrData(VarBytesValueConverter::getWrData(v));
        CmdData* cmdStruct = new CmdData;
        cmdStruct->cmd = cmd;
        cmdStruct->req = req;
        wrQueue += cmdStruct;
    }
}

void RequestScheduler::schedule()
{
    QMutexLocker locker(&mutex);
    i=0;
    binQueue+=cmdQueue;
    cmdQueue.clear();
    scanMap("RAM");
    scanMap("FRAM");
    scanMap("IO");
    scanMap("USER");
}

void RequestScheduler::clear()
{
    QMutexLocker locker(&mutex);
    i=0;
    binQueue+=cmdQueue;
    cmdQueue.clear();
    devMap.clear();
}

RequestScheduler::~RequestScheduler()
{
    clearBin();
    foreach (CmdData* cmdStruct, cmdQueue) {
       delete cmdStruct->cmd;
       delete cmdStruct->req;
       delete cmdStruct;
    }
    foreach (CmdData* cmdStruct, wrQueue) {
       delete cmdStruct->cmd;
       delete cmdStruct->req;
       delete cmdStruct;
    }
}

