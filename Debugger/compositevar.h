#ifndef COMPOSITEVAR_H
#define COMPOSITEVAR_H

// паттерн компоновщик для построения древовидной структуры элементов VarItem

#include "varitem.h"
#include <QVector>

class CompositeVar : public VarItem
{
    Q_OBJECT
    QVector<CompositeVar*> affiliatedVars;  // дочерние переменные
    CompositeVar* varParent;
public:
    explicit CompositeVar(CompositeVar* varParent=0, QObject *parent = 0);
    int getChildrenCount(void) const{return affiliatedVars.count();}
    QVector<CompositeVar*> getChildren();
    void addChild(CompositeVar* var) {affiliatedVars+=var;}
    CompositeVar* getParent() const {return varParent;}
    ~CompositeVar();
};

#endif // COMPOSITEVAR_H
