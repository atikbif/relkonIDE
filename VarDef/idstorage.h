#ifndef IDSTORAGE_H
#define IDSTORAGE_H

// класс для хранения соответствия переменных и их идентификаторов

#include <QHash>
#include "compositevar.h"

class IDStorage
{
    QHash<QString,CompositeVar*> idVar;
public:
    IDStorage();
    void addVar(CompositeVar* var);
    bool getVarByID(const QString& idValue, CompositeVar &var);
    bool setVarByID(const QString& idValue, CompositeVar &var);
    void clear();   // очистить список
    const QStringList getIDs(void); // вернуть список идентификаторов
    ~IDStorage();
};

#endif // IDSTORAGE_H
