#ifndef MATCHBOXEXISTANCE_H
#define MATCHBOXEXISTANCE_H

// класс проверки доступных для проект входов/выходов

#include <QString>

class MatchboxExistance
{
    QString plc;
public:
    MatchboxExistance(const QString &plcType="PC365C");
    QString getMatchboxFile();
    bool checkIO(const QString &ioName, const QString &ioList);
};

#endif // MATCHBOXEXISTANCE_H
