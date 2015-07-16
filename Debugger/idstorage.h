#ifndef IDSTORAGE_H
#define IDSTORAGE_H

// класс для хранения соответствия к переменным по их идентификаторам

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
    void clear();
    const QStringList getIDs(void);
    ~IDStorage();
};

#endif // IDSTORAGE_H
