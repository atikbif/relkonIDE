#ifndef PLCUTILS_H
#define PLCUTILS_H

#include <QString>

class PLCUtils
{
    static const QString f7Name;
public:
    static double getADCCoeff(const QString &plcName);
    static bool isBaseVersion(const QString &plcName);
    static bool isF7Version(const QString &plcName);
    PLCUtils() = default;
};

#endif // PLCUTILS_H
