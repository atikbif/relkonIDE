#include "varpattern.h"

VarPattern::VarPattern(const QString &vID, const QString &vPattern):
    varId(vID),pattern(vPattern)
{

}

bool VarPattern::checkPattern() const
{
    return true;
}

VarPattern::~VarPattern()
{

}

