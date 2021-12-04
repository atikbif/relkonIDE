#include "plcutils.h"
#include <QRegExp>

const QString PLCUtils::f7Name = "X6X BH7/DBH7";

double PLCUtils::getADCCoeff(const QString &plcName)
{
    if(plcName==f7Name) return 0;
    QRegExp re1("^PC\\d{3,3}C$");
    if(re1.indexIn(plcName)!=-1) {
        return 125.0/127;
    }
    // B и D контроллеры
    return 1.0416;
}

bool PLCUtils::isBaseVersion(const QString &plcName)
{
    if(plcName==f7Name) return false;
    return true;
}

bool PLCUtils::isF7Version(const QString &plcName)
{
    if(plcName==f7Name) return true;
    return false;
}
