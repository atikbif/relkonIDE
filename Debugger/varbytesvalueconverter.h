#ifndef VARBYTESVALUECONVERTER_H
#define VARBYTESVALUECONVERTER_H

#include <QString>
#include <QByteArray>

class VarBytesValueConverter
{
    static QString getIntValue(const QString &varType, const QByteArray &data);
    static QString getCharValue(const QString &varType, const QByteArray &data);
    static bool isSigned(const QString &varType);
public:
    VarBytesValueConverter();
    static int getVarSize(const QString &varType);
    static QString getValue(const QString &varType, const QByteArray &data);
    ~VarBytesValueConverter();
};

#endif // VARBYTESVALUECONVERTER_H
