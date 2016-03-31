#ifndef MATCHBOXEXISTANCE_H
#define MATCHBOXEXISTANCE_H

// класс проверки доступных для проект входов/выходов

#include <QString>

class MatchboxExistance
{
public:
    MatchboxExistance();
    QString getMatchboxFile();
    bool checkIO(const QString &ioName, const QString &ioList);
};

#endif // MATCHBOXEXISTANCE_H
