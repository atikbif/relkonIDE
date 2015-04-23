#ifndef FREERTOSFACTORY_H
#define FREERTOSFACTORY_H

#include "abstractchfilesfactory.h"

class FreeRtosFactory : public AbstractCHFilesFactory
{
public:
    FreeRtosFactory();
    CHGenerator* createCHGenerator();
};

#endif // FREERTOSFACTORY_H
