#ifndef VARGUICONNECTOR_H
#define VARGUICONNECTOR_H

#include <QObject>
#include <QHash>
#include <QTreeWidgetItem>
#include "varitem.h"

class VarGUIConnector : public QObject
{
    Q_OBJECT
    QHash<VarItem*,QTreeWidgetItem*> link;
public:
    void clear();
    void addLink(VarItem* var,QTreeWidgetItem* item);
    QTreeWidgetItem* getItem(VarItem* ptr);
    VarItem* getVar(QTreeWidgetItem* ptr);
    bool removeLink(VarItem* var);
    bool removeLink(QTreeWidgetItem* item);
    explicit VarGUIConnector(QObject *parent = 0);
    ~VarGUIConnector();

signals:

public slots:
};

#endif // VARGUICONNECTOR_H
