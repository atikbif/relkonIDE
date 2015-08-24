#include "memstorage.h"
#include <QMutexLocker>

const QString MemStorage::ioMemName = "IO";
const QString MemStorage::ramMemName = "RAM";
const QString MemStorage::framMemName = "FRAM";
const QString MemStorage::userMemName = "USER";
const QString MemStorage::timeMemName = "TIME";

MemStorage::MemStorage(QObject *parent) : QObject(parent)
{
    MemBlock* io = new MemBlock(ioMemName,ioMemSize);
    MemBlock* ram = new MemBlock(ramMemName,ramMemSize);
    MemBlock* fram = new MemBlock(framMemName,framMemSize);
    MemBlock* dispRam = new MemBlock(userMemName,userMemSize);
    blocks += io;
    blocks += ram;
    blocks += fram;
    blocks += dispRam;
}

bool MemStorage::updateBlock(QString memType, int addr, QByteArray data)
{
    QMutexLocker locker(&mutex);
    QStringList ids;
    MemBlock* block=nullptr;
    foreach (MemBlock* bl, blocks) {
       if(bl->getMemType()==memType) {block=bl;break;}
    }
    if(block==nullptr) return false;
    foreach (quint8 cellValue, data) {
       if(!block->updateCell(addr,cellValue)) return false;
       ids+=block->getID(addr++);
    }
    ids.removeDuplicates();
    locker.unlock();
    emit updateMemory(ids);
    return true;
}

QByteArray MemStorage::getData(const QString &memType, int addr, int count)
{
    QMutexLocker locker(&mutex);
    MemBlock* block=nullptr;
    foreach (MemBlock* bl, blocks) {
       if(bl->getMemType()==memType) {block=bl;break;}
    }
    if(block!=nullptr) {
        if(addr+count<=block->getSize()) {
            QByteArray outData;
            for(int i=0;i<count;i++) {
                outData+=block->getCell(addr+i);
            }
            return outData;
        }
    }
    return QByteArray();
}

bool MemStorage::connectCellToID(const QString &memType, int addr, const QString &id)
{
    MemBlock* block=nullptr;
    foreach (MemBlock* bl, blocks) {
       if(bl->getMemType()==memType) {block=bl;break;}
    }
    if(block!=nullptr) {
        return block->addID(addr,id);
    }
    return false;
}

QStringList MemStorage::getMemTypes() const
{
    QStringList types;
    foreach (MemBlock* bl, blocks) {
       types+=bl->getMemType();
    }
    return types;
}

void MemStorage::clearIDs()
{
    foreach (MemBlock* bl, blocks) {
        bl->clearIDs();
    }
}

MemStorage::~MemStorage()
{
    for(int i=0;i<blocks.count();i++) {
        delete blocks.at(i);
    }
}

