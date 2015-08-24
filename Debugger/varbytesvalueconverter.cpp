#include "varbytesvalueconverter.h"

QString VarBytesValueConverter::getFloatValue(const QString &varType, const QByteArray &data)
{
    Q_UNUSED(varType)
    float f;
    if (data.count() >= (int)sizeof(f))
    {
      f = *reinterpret_cast<const float*>(data.data());
      return QString::number(f);
    }
    return QString();
}

QString VarBytesValueConverter::getDoubleValue(const QString &varType, const QByteArray &data)
{
    Q_UNUSED(varType)
    double d;
    if (data.count() >= (int)sizeof(d))
    {
      d = *reinterpret_cast<const double*>(data.data());
      return QString::number(d);
    }
    return QString();
}

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
    quint64 value = 0;
    for(int i=0;i<8;i++) {
        value |= (quint64)((quint8)data.at(i)) << (8*i);
    }
    return QString::number(qlonglong(value));
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
    if(varType.contains(VarItem::charType)) varSize=1;
    else if(varType.contains(VarItem::shortType)) varSize=2;
    else if(varType.contains(VarItem::intType)) varSize=4;
    else if(varType.contains(VarItem::longLongType)) varSize=8;
    else if(varType.contains(VarItem::longType)) varSize=4;
    else if(varType.contains(VarItem::floatType)) varSize=4;
    else if(varType.contains(VarItem::doubleType)) varSize=8;
    else if(varType.contains(VarItem::timeType)) varSize=7;
    return varSize;
}

QByteArray VarBytesValueConverter::getWrData(VarItem var)
{
    QByteArray data;
    if(var.getDataType().contains(VarItem::charType)) {
        data+=(unsigned char)(var.getValue().toInt());
    }else if(var.getDataType().contains(VarItem::shortType)) {
        int value = var.getValue().toInt();
        data += value & 0xFF;
        data += (value>>8) &0xFF;
    }else if(var.getDataType().contains(VarItem::intType)) {
        int value = var.getValue().toInt();
        data += value & 0xFF;
        data += (value>>8) &0xFF;
        data += (value>>16) &0xFF;
        data += (value>>24) &0xFF;
    }else if(var.getDataType().contains(VarItem::longLongType)) {
            quint64 value = var.getValue().toLongLong();
            data += value & 0xFF;
            data += (value>>8) &0xFF;
            data += (value>>16) &0xFF;
            data += (value>>24) &0xFF;
            data += (value>>32) &0xFF;
            data += (value>>40) &0xFF;
            data += (value>>48) &0xFF;
            data += (value>>56) &0xFF;
    }else if(var.getDataType().contains(VarItem::longType)) {
        quint32 value = var.getValue().toLong();
        data += value & 0xFF;
        data += (value>>8) &0xFF;
        data += (value>>16) &0xFF;
        data += (value>>24) &0xFF;
    }else if(var.getDataType()==VarItem::floatType) {
        float f = var.getValue().toFloat();
        QByteArray ba(reinterpret_cast<const char *>(&f), sizeof (f));
        data += ba;
    }else if(var.getDataType()==VarItem::doubleType) {
        double d = var.getValue().toDouble();
        QByteArray ba(reinterpret_cast<const char *>(&d), sizeof (d));
        data += ba;
    }else if(var.getDataType()==VarItem::timeType) {
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
    if(vType.contains(VarItem::intType)) return getIntValue(vType,data);
    if(vType.contains(VarItem::charType)) {
        if(var.getBitNum()>=0) return getBitValue(var.getBitNum(),data);
        return getCharValue(vType,data);
    }
    if(vType.contains(VarItem::shortType)) return getShortValue(vType,data);
    if(vType.contains(VarItem::longLongType)) return getLongLongValue(vType,data);
    if(vType.contains(VarItem::longType)) return getLongValue(vType,data);
    if(vType.contains(VarItem::floatType)) return getFloatValue(vType,data);
    if(vType.contains(VarItem::doubleType)) return getDoubleValue(vType,data);

    return QString();
}

VarBytesValueConverter::~VarBytesValueConverter()
{

}

