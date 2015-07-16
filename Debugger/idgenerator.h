#ifndef IDGENERATOR_H
#define IDGENERATOR_H

// генерирует уникальный идентификатор по входной строке

#include <QtGlobal>

class IdGenerator
{
public:
    IdGenerator();
    static QString getID(const QString &inpString);
    ~IdGenerator();
};

#endif // IDGENERATOR_H
