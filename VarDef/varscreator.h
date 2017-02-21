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
#include <QRegExp>

class VarsCreator : public QObject
{
    Q_OBJECT

    Iterator* iter;
    IDStorage ids;
    QHash<QString,QString> idPultName;

    static const QRegExp numExp;
    static const QRegExp memExp;
    static const QRegExp memIExp;
    static const QRegExp memLExp;
    static const QRegExp eeExp;
    static const QRegExp eeIExp;
    static const QRegExp eeLExp;
    static const QRegExp sitExp;

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
    void addDisplVars(CompositeVar* parent);
    void addModbusVars(CompositeVar* parent);
    void addExchangeBufs(CompositeVar* parent);
    void addTimeVars(CompositeVar* parent);
public:
    explicit VarsCreator(QObject *parent = 0);
    void generateVarsTree(void);
    QStringList getIDList();
    bool checkID(QString id);
    VarItem getVarByID(QString idValue);
    QString getIdByPultVarName(const QString &pultVarName);
    QString getVarPultNameById(const QString &idValue);
    bool updateVarByID(QString idValue, VarItem &var);
    IDStorage& getIDStorage() {return ids;}
    QString getFullNameOfVar(const QString& idValue);
    QString getPultNameOfVar(const QString& idValue);
    QString getSimilarID(const QString& pultNameOfVar);
    void createPultNames(void);
    ~VarsCreator();

signals:

public slots:
};

#endif // VARSCREATOR_H
