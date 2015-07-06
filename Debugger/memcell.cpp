#include "memcell.h"

MemCell::MemCell(int address, QObject *parent) : QObject(parent),value(0)
{
    this->address= address;
}

void MemCell::setValue(unsigned char newValue)
{
    if(value!=newValue) {
        value = newValue;
        timeLabel = QDateTime::currentDateTime();
        emit dataUpdate(*this);
    }
}

void MemCell::setQuality(int newQuality)
{
    if(quality!=newQuality) {
        quality = newQuality;
        emit dataUpdate(*this);
    }
}

MemCell::~MemCell()
{

}

