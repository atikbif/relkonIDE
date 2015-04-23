#include "moduleio.h"
#include <QRegExp>

ModuleIO::ModuleIO(dataType type)
{
    this->type = type;
}

void ModuleIO::setSpeed(ModuleIO::speedPriority speed)
{
    this->speed = speed;
}

ModuleIO::speedPriority ModuleIO::getSpeed() const
{
    return speed;
}

void ModuleIO::setNetAddress(int value)
{
    netAddress = value;
}

void ModuleIO::setNetAddress(const QString &modName)
{
    const int InMin=4, InMax=67;
    const int OutMin=4, OutMax=67;
    const int AdcMin=9, AdcMax=136;
    const int DacMin=5, DacMax=68;

    QString name = modName;

    int startAddr = 0;
    if(name.contains("IN")) {startAddr = 1;name.remove(QRegExp("IN"));}
    else if(name.contains("OUT")) {startAddr = 65;name.remove(QRegExp("OUT"));}
    else if(name.contains("ADC")) {startAddr = 129;name.remove(QRegExp("ADC"));}
    else if(name.contains("DAC")) {startAddr = 161;name.remove(QRegExp("DAC"));}

    bool convResult=false;
    int ioNum = name.toInt(&convResult);
    if((!convResult)||(startAddr==0)) startAddr = -1;
    else {
        if(startAddr<65) {
            if((ioNum<InMin)||(ioNum>InMax)) startAddr=-1;
            else startAddr = 1+ioNum-InMin;
        }
        else if(startAddr<129) {
            if((ioNum<OutMin)||(ioNum>OutMax)) startAddr=-1;
            else startAddr = 65+ioNum-OutMin;
        }
        else if(startAddr<161) {
            if((ioNum<AdcMin)||(ioNum>AdcMax)) startAddr=-1;
            else startAddr = 129 + (ioNum-AdcMin)/4;
        }
        else {
            if((ioNum<DacMin)||(ioNum>DacMax)) startAddr=-1;
            startAddr = 161 + (ioNum-DacMin)/2;
        }
    }
    if(startAddr>0) netAddress = startAddr; else netAddress = -1;
}

int ModuleIO::getNetAddress() const
{
    return netAddress;
}
