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

bool VarItem::isEditable() const
{
    return isEdit;
}

void VarItem::setEditable(bool value)
{
    isEdit = value;
}

int VarItem::getByteCount()
{
    if(dataType==charType) return 1;
    if(dataType==ucharType) return 1;
    if(dataType==shortType) return 2;
    if(dataType==ushortType) return 2;
    if(dataType==intType) return 4;
    if(dataType==uintType) return 4;
    if(dataType==longType) return 4;
    if(dataType==ulongType) return 4;
    if(dataType==longLongType) return 8;
    if(dataType==floatType) return 4;
    if(dataType==doubleType) return 8;
    return 0;
}

void VarItem::updateID()
{
    QString str = name+memType+dataType+QString::number(memAddress)+QString::number(bitNum);
    id = str;
}

VarItem::VarItem(): priority(0), memAddress(0), comment(""),
    bitNum(-1), isEdit(true), forceSign(false)
{

}

VarItem::~VarItem()
{

}
