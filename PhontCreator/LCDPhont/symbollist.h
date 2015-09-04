#ifndef SYMBOLLIST_H
#define SYMBOLLIST_H

#include <QAbstractListModel>
#include "symboldata.h"
#include <QList>


class SymbolList : public QAbstractListModel
{
    Q_OBJECT
    QList<SymbolData*> sList;
public:
    explicit SymbolList(QObject *parent);
    ~SymbolList();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
public slots:
    void updateSymbol(int code, SymbolData *ptr);
};

#endif // SYMBOLLIST_H
