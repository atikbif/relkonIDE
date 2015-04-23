#include "konprocess.h"

KonProcess::KonProcess(int num)
{
    prNum = num;
}

const QVector<Situation> &KonProcess::getSituations() const
{
    return sit;
}

void KonProcess::addSituation(const Situation &s)
{
    sit += s;
}

Situation& KonProcess::getSituation(int numInList)
{
    if(sit.count()>numInList) return sit[numInList];
    return errSit;
}
