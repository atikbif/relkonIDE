#ifndef VARBYTESVALUECONVERTER_H
#define VARBYTESVALUECONVERTER_H

#include <QString>
#include <QByteArray>
#include "varitem.h"

class VarBytesValueConverter
{
    static QString getIntValue(const QString &varType, const QByteArray &data);
    static QString getCharValue(const QString &varType, const QByteArray &data);
    static QString getShortValue(const QString &varType, const QByteArray &data);
    static QString getLongLongValue(const QString &varType, const QByteArray &data);
    static QString getLongValue(const QString &varType, const QByteArray &data);
    static QString getBitValue(const int bitNum, const QByteArray &data);
    static bool isSigned(const QString &varType);
public:
    VarBytesValueConverter();
    static int getVarSize(const QString &varType);
    static QByteArray getWrData(VarItem var);
    static QString getValue(VarItem &var, const QByteArray &data);
    ~VarBytesValueConverter();
};

#endif // VARBYTESVALUECONVERTER_H
