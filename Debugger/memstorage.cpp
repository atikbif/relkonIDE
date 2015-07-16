#include "memstorage.h"

MemStorage::MemStorage(QObject *parent) : QObject(parent)
{
    MemBlock* io = new MemBlock("IO",256);
    MemBlock* ram = new MemBlock("RAM",20*1024);
    MemBlock* fram = new MemBlock("FRAM",32*1024);
    blocks += io;
    blocks += ram;
    blocks += fram;
}

bool MemStorage::updateBlock(const QString &memType, int addr, const QByteArray &data)
{
    QStringList ids;
    MemBlock* block=nullptr;
    foreach (MemBlock* bl, blocks) {
       if(bl->getMemType()==memType) {block=bl;break;}
    }
    if(block==nullptr) return false;
    foreach (quint8 cellValue, data) {
       if(!block->updateCell(addr,cellValue)) return false;
       ids+=block->getID(addr);
       addr++;
    }
    emit updateMemory(ids);
    return true;
}

QByteArray MemStorage::getData(const QString &memType, int addr, int count)
{
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

