#ifndef DEBUGGERFORM_H
#define DEBUGGERFORM_H

#include <QWidget>
#include "compositevar.h"
#include <QTreeWidgetItem>
#include "varguiconnector.h"

namespace Ui {
class DebuggerForm;
}

class DebuggerForm : public QWidget
{
    Q_OBJECT

    VarGUIConnector varGui;

    void createTree();
    void updateTrees();
    void treeBuilder(CompositeVar* var, QTreeWidgetItem &item);
    CompositeVar* vars;
public:
    explicit DebuggerForm(QWidget *parent = 0);
    ~DebuggerForm();

private slots:
    void on_treeWidgetMain_customContextMenuRequested(const QPoint &pos);


    void on_treeWidgetMain_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidgetWatch_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::DebuggerForm *ui;
};

#endif // DEBUGGERFORM_H
