#ifndef COMPOSITEVAR_H
#define COMPOSITEVAR_H

// компоновщик для построения древовидной структуры элементов VarItem

#include "varitem.h"
#include <QVector>
#include <QString>
#include <QStringList>


class CompositeVar : public VarItem
{
    QStringList affiliatedVarIDs;  // дочерние переменные
    QString parentID;

    void setParent(const VarItem &var) {parentID=var.getID();}
public:
    CompositeVar();
    int getChildrenCount(void) const{return affiliatedVarIDs.count();}
    const QStringList& getChildren() const;
    void addChild(CompositeVar &var) {affiliatedVarIDs+=var.getID();var.setParent(*this);}
    const QString& getParentID() {return parentID;}

    ~CompositeVar();
};

#endif // COMPOSITEVAR_H
