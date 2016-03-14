#ifndef MATCHBOXEXISTANCE_H
#define MATCHBOXEXISTANCE_H

#include <QString>

class MatchboxExistance
{
public:
    MatchboxExistance();
    QString getMatchboxFile();
    bool checkIO(const QString &ioName, const QString &ioList);
};

#endif // MATCHBOXEXISTANCE_H
