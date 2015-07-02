#include "namesortiterator.h"
#include <QMultiMap>
#include <QStringList>

void NameSortIterator::createCash(CompositeVar *var)
{
    cash.clear();
    posIncash=-1;
    if(var==nullptr) return;
    CompositeVar* varParent = var->getParent();
    if(var!=nullptr) {
        QMultiMap<QString,CompositeVar*> vars;
        if(varParent!=nullptr) {
            foreach (CompositeVar* cVar, varParent->getChildren()) {
               vars.insertMulti(cVar->getName(),cVar);
            }
            QStringList varNames = vars.keys();
            varNames.removeDuplicates();
            varNames.sort();
            foreach (QString vName, varNames) {
               QList<CompositeVar*> varsByName = vars.values(vName);
               foreach (CompositeVar* cVar, varsByName) {
                  cash += cVar;
               }
            }
        }else {
            cash += var;
        }

    }
    if(cash.count()) posIncash=0;
}

bool NameSortIterator::testCashState()
{
    if((posIncash<0)||(cash.count()==0)) return false;
    return true;
}

NameSortIterator::NameSortIterator(CompositeVar *var)
{
    if(var!=nullptr) createCash(var);
}

bool NameSortIterator::next()
{
    if(testCashState()==false) return false;
    if(posIncash+1<cash.count()) {
        posIncash++;
        return true;
    }
    return false;
}

bool NameSortIterator::previous()
{
    if(testCashState()==false) return false;
    if(posIncash>0) {
        posIncash--;
        return true;
    }
    return false;
}

bool NameSortIterator::first()
{
    if(testCashState()==false) return false;
    posIncash = 0;
    return true;
}

bool NameSortIterator::isTop()
{
    if(testCashState()==false) return false;
    if(cash.count()==1) return true;
    return false;
}

bool NameSortIterator::isNode()
{
    if(testCashState()==false) return false;
    if(cash.at(posIncash)->getChildrenCount()) return true;
    return false;
}

bool NameSortIterator::up()
{
    if(testCashState()==false) return false;
    CompositeVar* varParent = cash.at(0)->getParent();
    if(varParent!=nullptr) {
        createCash(varParent);
        return true;
    }
    return false;
}

bool NameSortIterator::down()
{
    if(testCashState()==false) return false;
    if(cash.at(posIncash)->getChildrenCount()) {
        createCash(cash.at(posIncash)->getChildren().at(0));
        return true;
    }
    return false;
}

bool NameSortIterator::topFirst()
{
    if(testCashState()==false) return false;
    while(up());
    return true;
}

VarItem *NameSortIterator::current()
{
    if(testCashState()==false) return nullptr;
    return cash.at(posIncash);
}

int NameSortIterator::getItemCount()
{
    if(testCashState()==false) return -1;
    return cash.count();
}

NameSortIterator::~NameSortIterator()
{

}

