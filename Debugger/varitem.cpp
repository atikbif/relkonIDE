#include "varitem.h"

const QString VarItem::charType = "char";
const QString VarItem::ucharType = "unsigned char";
const QString VarItem::shortType = "short";
const QString VarItem::ushortType = "unsigned short";
const QString VarItem::intType = "int";
const QString VarItem::uintType = "unsigned int";
const QString VarItem::longType = "long";
const QString VarItem::ulongType = "unsigned long";
const QString VarItem::longLongType = "long long";
const QString VarItem::floatType = "float";
const QString VarItem::doubleType = "double";
const QString VarItem::timeType = "time";

bool VarItem::getReadOnly() const
{
    return readOnly;
}

void VarItem::setReadOnly(bool value)
{
    readOnly = value;
}

void VarItem::updateID()
{
    QString str = name+memType+dataType+QString::number(memAddress)+QString::number(bitNum);
    id = str;
}

VarItem::VarItem(): priority(0), memAddress(0), bitNum(-1), readOnly(false)
{

}

VarItem::~VarItem()
{

}
