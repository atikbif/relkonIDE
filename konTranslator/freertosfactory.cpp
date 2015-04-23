#include "freertosfactory.h"
#include "freertosGenerator.h"

FreeRtosFactory::FreeRtosFactory(): AbstractCHFilesFactory()
{
}

CHGenerator *FreeRtosFactory::createCHGenerator()
{
    return new FreeRtosGenerator();
}
