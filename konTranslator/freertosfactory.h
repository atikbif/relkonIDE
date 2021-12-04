#ifndef FREERTOSFACTORY_H
#define FREERTOSFACTORY_H

#include "abstractchfilesfactory.h"
#include "LCD/display.h"
#include <QString>

class FreeRtosFactory : public AbstractCHFilesFactory
{
    QString plcName;
    CHGenerator *ptr = nullptr;
public:
    FreeRtosFactory(const QString &plcName);
    CHGenerator* createCHGenerator(const Display& d);
    ~FreeRtosFactory();
};

#endif // FREERTOSFACTORY_H
