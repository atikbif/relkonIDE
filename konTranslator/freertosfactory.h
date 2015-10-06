#ifndef FREERTOSFACTORY_H
#define FREERTOSFACTORY_H

#include "abstractchfilesfactory.h"
#include "LCD/display.h"

class FreeRtosFactory : public AbstractCHFilesFactory
{
public:
    FreeRtosFactory();
    CHGenerator* createCHGenerator(const Display& d);
};

#endif // FREERTOSFACTORY_H
