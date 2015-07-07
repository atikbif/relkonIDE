#include "varguiconnector.h"

void VarGUIConnector::clear()
{
    link.clear();
}

void VarGUIConnector::addLink(VarItem *var, QTreeWidgetItem *item)
{
    link.insert(var,item);
}

VarItem *VarGUIConnector::getVar(QTreeWidgetItem *ptr)
{
    if(link.values().contains(ptr)) return link.key(ptr);
    return nullptr;
}

bool VarGUIConnector::removeLink(VarItem *var)
{
    if(!link.keys().contains(var)) return false;
    link.remove(var);
    return true;
}

bool VarGUIConnector::removeLink(QTreeWidgetItem *item)
{
    VarItem* var = getVar(item);
    if(var==nullptr) return false;
    link.remove(var);
    return true;
}

VarGUIConnector::VarGUIConnector(QObject *parent) : QObject(parent)
{

}

VarGUIConnector::~VarGUIConnector()
{

}

