#include "pultvardefinition.h"


QString PultVarDefinition::getPattern() const
{
    return pattern;
}

void PultVarDefinition::setPattern(const QString &value)
{
    pattern = value;
}

QString PultVarDefinition::getName() const
{
    return name;
}

void PultVarDefinition::setName(const QString &value)
{
    name = value;
}

QString PultVarDefinition::getDataType() const
{
    return dataType;
}

void PultVarDefinition::setDataType(const QString &value)
{
    dataType = value;
}

int PultVarDefinition::getStrNum() const
{
    return strNum;
}

void PultVarDefinition::setStrNum(int value)
{
    strNum = value;
}

int PultVarDefinition::getSubStrNum() const
{
    return subStrNum;
}

void PultVarDefinition::setSubStrNum(int value)
{
    subStrNum = value;
}

int PultVarDefinition::getPosInStr() const
{
    return posInStr;
}

void PultVarDefinition::setPosInStr(int value)
{
    posInStr = value;
}


bool PultVarDefinition::getIsEditable() const
{
    return isEditable;
}

void PultVarDefinition::setIsEditable(bool value)
{
    isEditable = value;
}

bool PultVarDefinition::getForceSign() const
{
    return forceSign;
}

void PultVarDefinition::setForceSign(bool value)
{
    forceSign = value;
}

bool PultVarDefinition::getIsEEVar() const
{
    return isEEVar;
}

void PultVarDefinition::setIsEEVar(bool value)
{
    isEEVar = value;
}

int PultVarDefinition::getEEposInSettingsTable() const
{
    return EEposInSettingsTable;
}

void PultVarDefinition::setEEposInSettingsTable(int value)
{
    EEposInSettingsTable = value;
}

QString PultVarDefinition::getId() const
{
    return id;
}

void PultVarDefinition::setId(const QString &value)
{
    id = value;
}

bool PultVarDefinition::getIsExist() const
{
    return isExist;
}

void PultVarDefinition::setIsExist(bool value)
{
    isExist = value;
}
PultVarDefinition::PultVarDefinition():
    pattern(""),name(""),dataType(""),strNum(0),
    subStrNum(0),posInStr(0),isEditable(false),
    forceSign(false), isEEVar(false),EEposInSettingsTable(0),
    isExist(false), isTime(false)
{

}

PultVarDefinition::~PultVarDefinition()
{

}

