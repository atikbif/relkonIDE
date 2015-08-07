#include "varbytesvalueconverter.h"

QString VarBytesValueConverter::getIntValue(const QString &varType, const QByteArray &data)
{
    quint32 value = 0;
    for(int i=0;i<4;i++) {
        value |= (quint32)((quint8)data.at(i)) << (8*i);
    }
    if(isSigned(varType)) {
        qint32 res = (qint32)value;
        return QString::number(long(res));
    }else return QString::number(ulong(value));
}

QString VarBytesValueConverter::getCharValue(const QString &varType, const QByteArray &data)
{
    quint8 value = data.at(0);
    if(isSigned(varType)) {
        qint8 res = (qint8)value;
        return QString::number(long(res));
    }else return QString::number(ulong(value));
}

bool VarBytesValueConverter::isSigned(const QString &varType)
{
    if(varType.contains("unsigned")) return false;
    return true;
}

VarBytesValueConverter::VarBytesValueConverter()
{

}

int VarBytesValueConverter::getVarSize(const QString &varType)
{
    int varSize=0;
    if(varType.contains("char")) varSize=1;
    else if(varType.contains("short")) varSize=2;
    else if(varType.contains("int")) varSize=4;
    else if(varType.contains("long long")) varSize=8;
    else if(varType.contains("long")) varSize=4;
    else if(varType.contains("float")) varSize=4;
    else if(varType.contains("double")) varSize=8;
    return varSize;
}

QString VarBytesValueConverter::getValue(const QString &varType, const QByteArray &data)
{
    if(varType.contains("int")) return getIntValue(varType,data);
    if(varType.contains("char")) return getCharValue(varType,data);
    return QString();
}

VarBytesValueConverter::~VarBytesValueConverter()
{

}

