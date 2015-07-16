#ifndef VARSCREATOR_H
#define VARSCREATOR_H

// класс для создания и обновления дерева переменных
// взаимодействия переменных с GUI и памятью

#include <QObject>
#include "idstorage.h"
#include "compositevar.h"
#include "iterator.h"

class VarsCreator : public QObject
{
    Q_OBJECT

    Iterator* iter;
    IDStorage ids;

public:
    explicit VarsCreator(QObject *parent = 0);
    void generateVarsTree(void);
    QStringList getIDList();
    bool checkID(QString id);
    VarItem getVarByID(QString idValue);
    bool updateVarByID(QString idValue, VarItem &var);
    IDStorage& getIDStorage() {return ids;}
    ~VarsCreator();

signals:

public slots:
};

#endif // VARSCREATOR_H
