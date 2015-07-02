#include "compositevar.h"

CompositeVar::CompositeVar(CompositeVar *varParent, QObject *parent):VarItem(parent)
{
    this->varParent = varParent;
    if(varParent!=nullptr) {
        varParent->addChild(this);
    }
}

QVector<CompositeVar *> CompositeVar::getChildren()
{
    return affiliatedVars;
}

CompositeVar::~CompositeVar()
{
    for(int i=0;i<affiliatedVars.count();i++) delete affiliatedVars[i];
}

