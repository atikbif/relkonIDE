#ifndef DEBUGGERFORM_H
#define DEBUGGERFORM_H

// класс GUI для отладчика

#include <QWidget>
#include "compositevar.h"
#include <QTreeWidgetItem>
#include "idstorage.h"
#include "varscreator.h"
#include "namesortiterator.h"
#include <QHash>
#include "memstorage.h"
#include "Scanner/scanmanager.h"
#include "requestscheduler.h"

namespace Ui {
class DebuggerForm;
}

class DebuggerForm : public QWidget
{
    Q_OBJECT


    VarsCreator varOwner;
    NameSortIterator* iter;
    QHash<QString,QTreeWidgetItem*> idWidgetItem;   // переменные в основном GUI дереве
    QHash<QString,QTreeWidgetItem*> idActiveWidgetItem; // опрашиваемые переменные
    MemStorage memStor;
    ScanManager* scan;
    RequestScheduler scheduler;

    void createTree();
    void updateTrees();
    void treeBuilder(const QString& varID, QTreeWidgetItem &item);
    void updateValuesTree(void);

public:
    explicit DebuggerForm(QWidget *parent = 0);
    ~DebuggerForm();

private slots:

    void on_treeWidgetMain_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeWidgetWatch_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void updateMemory(QStringList ids);
    void updateCorrErrAnswerCount(int cnt, bool correctFlag);
public slots:
    void on_updateButton_clicked();

private:
    Ui::DebuggerForm *ui;

};

#endif // DEBUGGERFORM_H
