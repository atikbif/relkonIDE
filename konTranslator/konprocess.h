#ifndef PROCESS_H
#define PROCESS_H

//#include <QVector>
#include "situation.h"

class KonProcess
{
    int prNum;
    QVector<Situation> sit;
    Situation errSit;
public:
    explicit KonProcess(int num=0);
    const QVector<Situation>& getSituations(void) const;
    void addSituation(const Situation &s);
    Situation &getSituation(int numInList);
    int getNum(void) const {return prNum;}
};

#endif // PROCESS_H
