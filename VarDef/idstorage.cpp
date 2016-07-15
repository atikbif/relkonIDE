#include "idstorage.h"
#include "varscreator.h"

IDStorage::IDStorage()
{

}

void IDStorage::addVar(CompositeVar *var)
{
    idVar.insert(var->getID(),var);
}

bool IDStorage::getVarByID(const QString &idValue, CompositeVar &var)
{
    if(idVar.contains(idValue)) {
        var = *(idVar.value(idValue));
        return true;
    }
    return false;
}

bool IDStorage::setVarByID(const QString &idValue, CompositeVar &var)
{
    if(idVar.contains(idValue)) {
        *(idVar.value(idValue)) = var;
        return true;
    }
    return false;
}

void IDStorage::clear()
{
    foreach(VarItem* var,idVar.values()){
        delete var;
    }
    idVar.clear();
}

const QStringList IDStorage::getIDs()
{
    return idVar.keys();
}

IDStorage::~IDStorage()
{
    clear();
}

