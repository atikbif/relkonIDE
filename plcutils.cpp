#include "plcutils.h"
#include <QRegExp>
#include <vector>
#include <algorithm>

const QString PLCUtils::f7Name = "X6X BH7/DBH7";
const QString PLCUtils::defaultPLCName = "X6X H/DH";
const QString PLCUtils::bTypePLCName = "X6X BH/DBH";
const QString PLCUtils::plc470Name = "PC470";
const QString PLCUtils::mc23Name = "MC2302";

double PLCUtils::getADCCoeff(const QString &plcName)
{
    if(plcName==f7Name) return 0;
    if(plcName==defaultPLCName) return 125.0/127;
    if(plcName==bTypePLCName) return 1.0416;

    return 0;
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

QString PLCUtils::convertPLCType(const QString &plcName)
{
    std::vector<QString> x6xTypes = {"PC164C","PC165C","PC263C","PC264C","PC265C","PC363C","PC364C","PC365C"};
    std::vector<QString> x6xBTypes = {"PC164B","PC165B","PC263B","PC264B","PC265B","PC363B","PC364B","PC365B","PC164DB","PC165DB","PC263DB","PC264DB","PC265DB","PC363DB","PC364DB","PC365DB"};
    std::vector<QString> plc470Types = {"PC474"};
    std::vector<QString> mcTypes = {"MC3501"};
    auto it = std::find(x6xTypes.begin(),x6xTypes.end(),plcName);
    if(it!=x6xTypes.end()) return PLCUtils::defaultPLCName;
    it = std::find(x6xBTypes.begin(),x6xBTypes.end(),plcName);
    if(it!=x6xBTypes.end()) return PLCUtils::bTypePLCName;
    it = std::find(plc470Types.begin(),plc470Types.end(),plcName);
    if(it!=plc470Types.end()) return PLCUtils::plc470Name;
    it = std::find(mcTypes.begin(),mcTypes.end(),plcName);
    if(it!=mcTypes.end()) return PLCUtils::mc23Name;
    return plcName;
}

bool PLCUtils::hasNoIO(const QString &plcName)
{
    std::vector<QString> types = {"MC2302","MMB507"};
    auto it = std::find(types.begin(),types.end(),plcName);
    if(it!=types.end()) return true;
    return false;
}
