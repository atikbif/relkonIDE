#include "memblock.h"

MemBlock::MemBlock(const QString &typeOfMem, int count)
{
    Q_UNUSED(typeOfMem)
    Q_UNUSED(count)
}

quint8 MemBlock::getCell(int address) const
{
    if(address<data.count()) {
        return data.at(address);
    }
    return 0;
}

bool MemBlock::updateCell(int address, quint8 value)
{
    if(address<data.count()) {
        data[address]=value;
        return true;
    }
    return false;
}

QStringList MemBlock::getID(int addr)
{
    if(addr<data.count()) {
        return addrID.values(addr);
    }
    return QStringList();
}

bool MemBlock::addID(int addr, const QString &id)
{
    if(addr<data.count()) {
        addrID.insert(addr,id);
        return true;
    }
    return false;
}

MemBlock::~MemBlock()
{

}

