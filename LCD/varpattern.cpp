#include "varpattern.h"

VarPattern::VarPattern(const QString &vID, const QString &vPattern):
    varId(vID),pattern(vPattern)
{

}

bool VarPattern::checkPattern() const
{
    if(pattern.isEmpty()) return false;
    if(pattern.contains(" ")) return false;
    return true;
}

VarPattern::~VarPattern()
{

}

