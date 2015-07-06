#include "memstorage.h"

void MemStorage::createBlock(const QString &memType, int blSize)
{
    MemCell* ptr = new MemCell[blSize];
    blockSize.insert(memType,blSize);
    blockData.insert(memType,ptr);
    for(int i=0;i<blSize;i++) {
        ptr[i].setAdderss(i);
    }
}

int MemStorage::getCount(const QString &memType)
{
    return blockSize.value(memType);
}

MemCell *MemStorage::getCell(const QString &memType, int cellAddress)
{
    if(cellAddress<blockSize.value(memType)){
        MemCell *ptr = blockData.value(memType);
        return &ptr[cellAddress];
    }
    return nullptr;
}

MemStorage::MemStorage()
{

}

MemStorage::~MemStorage()
{
    foreach (MemCell* ptr, blockData.values()) {
       delete[] ptr;
    }
}

