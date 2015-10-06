#ifndef ABSTRACTCHFILESFACTORY_H
#define ABSTRACTCHFILESFACTORY_H

#include "chgenerator.h"
#include "LCD/display.h"

class AbstractCHFilesFactory
{
public:
    AbstractCHFilesFactory();
    virtual CHGenerator* createCHGenerator(const Display& d)=0;
};

#endif // ABSTRACTCHFILESFACTORY_H
