#include "namesortiterator.h"
#include <QMultiMap>
#include <QStringList>
#include "compositevar.h"

void NameSortIterator::createCash(const QString &varID)
{
    cash.clear();
    posIncash=-1;

    CompositeVar var;
    if(ids.getVarByID(varID,var)) {
        QString parID = var.getParentID();
        if(!parID.isEmpty()) {
            if(ids.getVarByID(parID,var)) {
                QStringList childrenIDs = var.getChildren();
                QMultiMap<QString,QString> vars;
                foreach (QString id, childrenIDs) {
                    CompositeVar child;
                    if(ids.getVarByID(id,child)) {
                        vars.insert(child.getName(),id);
                    }
                }
                QStringList varNames = vars.keys();
                varNames.removeDuplicates();
                varNames.sort();
                int curId=0;
                foreach (QString vName, varNames) {
                   QStringList varsByName = vars.values(vName);
                   foreach (QString cVar, varsByName) {
                      cash += cVar;
                      if(cVar==varID) posIncash = curId;
                      curId++;
                   }
                }
                return;
            }
        }else {
            cash += varID;
            posIncash=0;
        }
    }
}

bool NameSortIterator::testCashState()
{
    if((posIncash<0)||(cash.count()==0)) return false;
    return true;
}

NameSortIterator::NameSortIterator(IDStorage &idStor):ids(idStor)
{
    cash.clear();
    posIncash=-1;
    if(ids.getIDs().count()) {
        createCash(ids.getIDs().at(0));
    }
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

bool NameSortIterator::first()
{
    if(testCashState()==false) return false;
    posIncash = 0;
    return true;
}

bool NameSortIterator::isNode()
{
    if(testCashState()==false) return false;
    CompositeVar var;
    if(ids.getVarByID(cash.at(posIncash),var)) {
        if(var.getChildrenCount()) return true;
    }
    return false;
}

bool NameSortIterator::up()
{
    if(testCashState()==false) return false;
    CompositeVar var;
    if(ids.getVarByID(cash.at(0),var)){
        QString id = var.getParentID();
        if(id>0) {
            createCash(id);
            return true;
        }
    }
    return false;
}

bool NameSortIterator::down()
{
    if(testCashState()==false) return false;
    CompositeVar var;
    if(ids.getVarByID(cash.at(posIncash),var)){
        if(var.getChildrenCount()) {
            createCash(var.getChildren().at(0));
            posIncash=0;
            return true;
        }
    }
    return false;
}

bool NameSortIterator::topFirst()
{
    if(testCashState()==false) return false;
    while(up());
    return true;
}

bool NameSortIterator::goToID(const QString &id)
{
    CompositeVar var;
    if(ids.getVarByID(id,var)){
        createCash(id);
        return testCashState();
    }
    return false;
}

QString NameSortIterator::currentID()
{
    if(testCashState()==false) return QString();
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

