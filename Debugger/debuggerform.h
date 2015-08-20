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
#include "bitio.h"
#include "anio.h"

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
    QMultiHash<int,BitIO*> ioHash;
    QMultiHash<int,AnIO*> anIoHash;
    QHash<QString,QLineEdit*> ioComments;
    MemStorage memStor;
    ScanManager* scan;
    RequestScheduler scheduler;

    VarItem wrVar;      // переменная для записи


    void createTree();
    void updateTrees();
    void treeBuilder(const QString& varID, QTreeWidgetItem &item);
    void updateValuesTree(void);
    void updateComPortList(void);
    void buildIO(void);

public:
    explicit DebuggerForm(QWidget *parent = 0);
    void saveView();
    void openView();
    void clearView();
    ~DebuggerForm();

private slots:

    void on_treeWidgetMain_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeWidgetWatch_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void updateMemory(QStringList ids);
    void updateCorrErrAnswerCount(int cnt, bool correctFlag);
    void getMessageFromDebugProcess(QString message);
    void getTimeStr(QString timeStr);
    void on_pushButtonCOMUpdate_clicked();

    void on_pushButtonAutoSearch_clicked();

    void on_checkBoxLog_clicked();

    void on_pushButtonTimeWrite_clicked();

    void on_treeWidgetWatch_customContextMenuRequested(const QPoint &pos);
    void writeVar();
    void inOutClicked();
    void anInOutClicked();

    void on_tabWidget_currentChanged(int index);

public slots:
    void on_updateButton_clicked();

private:
    Ui::DebuggerForm *ui;

};

#endif // DEBUGGERFORM_H
