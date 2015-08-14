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

QString VarBytesValueConverter::getShortValue(const QString &varType, const QByteArray &data)
{
    quint16 value = 0;
    for(int i=0;i<2;i++) {
        value |= (quint16)((quint8)data.at(i)) << (8*i);
    }
    if(isSigned(varType)) {
        qint16 res = (qint16)value;
        return QString::number(long(res));
    }else return QString::number(ulong(value));
}

QString VarBytesValueConverter::getLongLongValue(const QString &varType, const QByteArray &data)
{
    Q_UNUSED(varType)
    Q_UNUSED(data)
    return QString();
}

QString VarBytesValueConverter::getLongValue(const QString &varType, const QByteArray &data)
{
    return getIntValue(varType,data);
}

QString VarBytesValueConverter::getBitValue(const int bitNum, const QByteArray &data)
{
    quint8 value = data.at(0);
    if(value & 1<<bitNum) return QString("1");
    return QString("0");
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
    else if(varType.contains("time")) varSize=7;
    return varSize;
}

QByteArray VarBytesValueConverter::getWrData(VarItem var)
{
    QByteArray data;
    if(var.getDataType()=="unsigned char") {
        data+=(unsigned char)(var.getValue().toInt());
    }else if(var.getDataType()=="time") {
        QStringList inpData = var.getValue().split(" ");
        foreach (QString timeCell, inpData) {
           if(!timeCell.isEmpty()) {
               data += (unsigned char)(timeCell.toInt());
           }
        }
        while(data.count()<7) data+='\0'; // размер пакета данных для записи времени
    }
    return data;
}

QString VarBytesValueConverter::getValue(VarItem &var, const QByteArray &data)
{
    QString vType = var.getDataType();
    if(vType.contains("int")) return getIntValue(vType,data);
    if(vType.contains("char")) {
        if(var.getBitNum()>=0) return getBitValue(var.getBitNum(),data);
        return getCharValue(vType,data);
    }
    if(vType.contains("short")) return getShortValue(vType,data);
    if(vType.contains("long long")) return getLongLongValue(vType,data);
    if(vType.contains("long")) return getLongValue(vType,data);

    return QString();
}

VarBytesValueConverter::~VarBytesValueConverter()
{

}

