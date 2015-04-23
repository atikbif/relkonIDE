#include "inpdatainterface.h"

InpDataInterface::InpDataInterface()
{
}

void InpDataInterface::updateData(const QString &label, const QList<int> inp)
{
    inpData.insert(label,inp);
}
