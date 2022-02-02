#ifndef PLCUTILS_H
#define PLCUTILS_H

#include <QString>

class PLCUtils
{
public:
    static const QString f7Name;
    static const QString defaultPLCName;
    static const QString bTypePLCName;
    static const QString dbTypePLCName;
    static const QString cTypePLCName;
    static const QString plc470Name;
    static const QString mc23Name;

    static double getADCCoeff(const QString &plcName);
    static bool hasI2C_ADC(const QString &plcName);
    static bool isBaseVersion(const QString &plcName);
    static bool isF7Version(const QString &plcName);
    static QString convertPLCType(const QString &plcName);
    static bool hasNoIO(const QString &plcName);
    PLCUtils() = default;
};

#endif // PLCUTILS_H
