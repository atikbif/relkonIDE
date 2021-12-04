#include "freertosfactory.h"
#include "freertosgenerator.h"
#include "f7generator.h"
#include "plcutils.h"

FreeRtosFactory::FreeRtosFactory(const QString &plcName): AbstractCHFilesFactory(), plcName(plcName)
{

}

CHGenerator *FreeRtosFactory::createCHGenerator(const Display &d)
{

    if(ptr) {
        delete ptr;
        ptr = nullptr;
    }
    if(PLCUtils::isBaseVersion(plcName)) {
        ptr = new FreeRtosGenerator(d);
    }else if(PLCUtils::isF7Version(plcName)) {
        ptr = new F7Generator(d);
    }
    return ptr;
}

FreeRtosFactory::~FreeRtosFactory()
{
    if(ptr) delete ptr;
}
