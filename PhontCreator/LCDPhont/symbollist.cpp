#include "symbollist.h"

SymbolList::SymbolList(QObject *parent):QAbstractListModel(parent)
{
    for(int i=0;i<256;i++) {
        SymbolData* s = new SymbolData(i);
        sList += s;
    }
}

SymbolList::~SymbolList()
{
    foreach (SymbolData* s, sList) {
       delete s;
    }
}

int SymbolList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return sList.count();
}

QVariant SymbolList::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    switch(role) {
        case Qt::DisplayRole:
            int i = index.row();
            if((i<0)||(i>=sList.count())) return QVariant();
            return QVariant::fromValue((void*)sList.at(i));
            break;
    }
    return QVariant();
}

bool SymbolList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) return false;
    switch (role) {
    case Qt::EditRole:
        sList[index.row()] = static_cast<SymbolData*>(value.value<void*>());
        break;
    }
    return true;
}

Qt::ItemFlags SymbolList::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void SymbolList::updateSymbol(int code, SymbolData* ptr)
{
    for(int i=0;i<sList.count();i++) {
       SymbolData* s =sList.at(i);
       if(s->getCode()==code) {
           s->setData(ptr->getData());

           QModelIndex ind = index(i);
           QVector<int> roles;
           roles << Qt::DisplayRole;
           emit dataChanged(ind,ind,roles);
           break;
       }
    }

}

