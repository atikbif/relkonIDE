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

int PultVarDefinition::getPosInStr() const
{
    return posInStr;
}

void PultVarDefinition::setPosInStr(int value)
{
    posInStr = value;
}


bool PultVarDefinition::isEditable() const
{
    return isEdit;
}

void PultVarDefinition::setEditable(bool value)
{
    isEdit = value;
}

bool PultVarDefinition::getForceSign() const
{
    return forceSign;
}

void PultVarDefinition::setForceSign(bool value)
{
    forceSign = value;
}

bool PultVarDefinition::isEEVar() const
{
    return isEE;
}

void PultVarDefinition::setEEVar(bool value)
{
    isEE = value;
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

bool PultVarDefinition::isExist() const
{
    return isItExist;
}

void PultVarDefinition::setExist(bool value)
{
    isItExist = value;
}

PultVarDefinition::PultVarDefinition():
    pattern(""),name(""),dataType(""),posInStr(0),isEdit(false),
    forceSign(false), isEE(false),EEposInSettingsTable(0),
    isItExist(false)
{

}

PultVarDefinition::~PultVarDefinition()
{

}

