#include "freertosfactory.h"
#include "freertosGenerator.h"

FreeRtosFactory::FreeRtosFactory(): AbstractCHFilesFactory()
{
}

CHGenerator *FreeRtosFactory::createCHGenerator(const Display &d)
{
    return new FreeRtosGenerator(d);
}
