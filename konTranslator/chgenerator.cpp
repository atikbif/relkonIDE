#include "chgenerator.h"

CHGenerator::CHGenerator(const Display &d):
    lcd(d)
{
}

const QStringList &CHGenerator::getErrors() const
{
    return errorList;
}

