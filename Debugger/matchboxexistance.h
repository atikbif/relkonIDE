#ifndef MATCHBOXEXISTANCE_H
#define MATCHBOXEXISTANCE_H

// класс проверки доступных для проект входов/выходов

#include <QString>
#include "plcutils.h"

class MatchboxExistance
{
    QString plc;
public:
    MatchboxExistance(const QString &plcType=PLCUtils::defaultPLCName);
    QString getMatchboxFile();
    bool checkIO(const QString &ioName, const QString &ioList);
};

#endif // MATCHBOXEXISTANCE_H
