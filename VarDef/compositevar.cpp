#include "compositevar.h"

CompositeVar::CompositeVar():VarItem()
{

}

const QStringList &CompositeVar::getChildren() const
{
    return affiliatedVarIDs;
}

CompositeVar::~CompositeVar()
{

}

