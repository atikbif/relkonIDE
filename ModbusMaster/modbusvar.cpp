#include "modbusvar.h"

namespace modbusMaster {

ModbusVar::canType ModbusVar::getCanType() const
{
    return can;
}

void ModbusVar::setCanType(const canType &value)
{
    can = value;
}

ModbusVar::memType ModbusVar::getMemType() const
{
    return mem;
}

void ModbusVar::setMemType(const memType &value)
{
    mem = value;
}

int ModbusVar::getNetAddr() const
{
    return netAddr;
}

void ModbusVar::setNetAddr(int value)
{
    netAddr = value;
}

QString ModbusVar::getVarName() const
{
    return varName;
}

void ModbusVar::setVarName(const QString &value)
{
    varName = value;
}

bool ModbusVar::getWriteFlag() const
{
    return writeFlag;
}

void ModbusVar::setWriteFlag(bool value)
{
    writeFlag = value;
}

int ModbusVar::getMemAddr() const
{
    return memAddr;
}

void ModbusVar::setMemAddr(int value)
{
    memAddr = value;
}

bool ModbusVar::getActiv() const
{
    return activ;
}

void ModbusVar::setActiv(bool value)
{
    activ = value;
}

QString ModbusVar::getComment() const
{
    return comment;
}

void ModbusVar::setComment(const QString &value)
{
    comment = value;
}

ModbusVar::ModbusVar(const QString &vName):can(CAN_MB),mem(HOLD_REG),netAddr(1),
    varName(vName), writeFlag(false), memAddr(0), activ(true), comment(QString())
{

}

}


