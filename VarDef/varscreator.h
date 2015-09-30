#ifndef VARSCREATOR_H
#define VARSCREATOR_H

// класс для создания и обновления дерева переменных
// взаимодействия переменных с GUI и памятью

#include <QObject>
#include "idstorage.h"
#include "compositevar.h"
#include "iterator.h"
#include <QDomElement>
#include <QDomNodeList>
#include <QHash>
#include <QString>

class VarsCreator : public QObject
{
    Q_OBJECT

    Iterator* iter;
    IDStorage ids;

    QHash<int,int> elemByID; // key - id , value - индекс в allData
    QDomNodeList allData;

    void addVarToTree(const QDomElement &e, CompositeVar *var, CompositeVar* parent=0);
    void createSysVars(CompositeVar* parent);
    void addDiscrInputs(CompositeVar* parent);
    void addDiscrOutputs(CompositeVar* parent);
    void addAnalogInputs(CompositeVar* parent);
    void addAnalogOutputs(CompositeVar* parent);
    void addFactorySettings(CompositeVar* parent);
    void addDispVar(CompositeVar* parent);
    void addSituationNum(CompositeVar* parent);
public:
    explicit VarsCreator(QObject *parent = 0);
    void generateVarsTree(void);
    QStringList getIDList();
    bool checkID(QString id);
    VarItem getVarByID(QString idValue);
    bool updateVarByID(QString idValue, VarItem &var);
    IDStorage& getIDStorage() {return ids;}
    QString getFullNameOfVar(QString idValue);
    ~VarsCreator();

signals:

public slots:
};

#endif // VARSCREATOR_H
