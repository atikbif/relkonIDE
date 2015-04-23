#ifndef ABSTRACTCHFILESFACTORY_H
#define ABSTRACTCHFILESFACTORY_H

#include "chgenerator.h"

class AbstractCHFilesFactory
{
public:
    AbstractCHFilesFactory();
    virtual CHGenerator* createCHGenerator()=0;
};

#endif // ABSTRACTCHFILESFACTORY_H
