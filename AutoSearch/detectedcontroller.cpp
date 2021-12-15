#include "detectedcontroller.h"
#include <QMutexLocker>

void DetectedController::updateData(const SearchController &contr)
{
    setBaudrate(contr.getBaudrate());
    setNetAddress(contr.getNetAddress());
    setUartName(contr.getUartName());
    setAsciiMode(contr.getAsciiMode());
    setBootMode(contr.getBootMode());
    setCanName(contr.getCanName());
    setMcuType(contr.getMcuType());
}

DetectedController::DetectedController()
{

}

DetectedController::~DetectedController()
{

}
