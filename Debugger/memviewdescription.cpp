#include "memviewdescription.h"
#include "memstorage.h"

MemViewDescription::MemViewDescription(int r, int c):
    memType(RAM), rowCount(r), colCount(c)
{

}

void MemViewDescription::setMemType(int memCode)
{
    switch(memCode) {
        case FRAM:memType = FRAM;break;
        case RAM:memType = RAM;break;
    }
}

int MemViewDescription::getMemType() const
{
    return memType;
}

int MemViewDescription::getRowCount() const
{
    return rowCount;
}

int MemViewDescription::getcolumnCount() const
{
    return colCount;
}

bool MemViewDescription::checkAddress(int address) const
{
    const int maxFRAMAddr = MemStorage::framMemSize;
    const int maxRAMAddress = MemStorage::ramMemSize;
    if(address<0) return false;
    if((memType==FRAM)&&(address<maxFRAMAddr)) return true;
    if((memType==RAM)&&(address<maxRAMAddress)) return true;
    return false;
}

