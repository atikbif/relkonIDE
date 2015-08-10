#include "debuggerform.h"
#include "ui_debuggerform.h"

#include "namesortiterator.h"
#include <QMenu>
#include <QStringList>
#include <QLineEdit>
#include "vartomemconnector.h"
#include "varbytesvalueconverter.h"
#include "varparser.h"
#include "RCompiler/rcompiler.h"
#include <QDateTime>


void DebuggerForm::createTree()
{
    ui->treeWidgetMain->clear();
    varOwner.generateVarsTree();
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidgetMain);

    if(varOwner.getIDList().count()) {
        iter->goToID(varOwner.getIDList().at(0));
        if(iter->topFirst()) {
            item->setText(0,varOwner.getVarByID(iter->currentID()).getName());
            treeBuilder(iter->currentID(),*item);
        }
    }

    QString style = "QTreeWidget::item:!selected "
       "{ border: 1px solid gainsboro; border-left: none; border-top: none; }";

    ui->treeWidgetMain->setStyleSheet(style);
    ui->treeWidgetWatch->setStyleSheet(style);

    ui->treeWidgetMain->setItemExpanded(item,true);
    ui->treeWidgetMain->header()->resizeSections(QHeaderView::ResizeToContents);

}

void DebuggerForm::treeBuilder(const QString &varID, QTreeWidgetItem &item)
{
    iter->goToID(varID);
    if(iter->isNode()) {
        if(iter->down()){
            for(int i=0;i<iter->getItemCount();i++) {
                QString curPos = iter->currentID();
                QTreeWidgetItem* curItem = new QTreeWidgetItem(&item);
                curItem->setText(0,varOwner.getVarByID(curPos).getName());
                curItem->setText(1,varOwner.getVarByID(curPos).getDataType());
                if(item.toolTip(0).isEmpty())
                curItem->setToolTip(0,item.text(0)+"."+curItem->text(0));
                else curItem->setToolTip(0,item.toolTip(0)+"."+curItem->text(0));
                if(iter->isNode()) {
                    treeBuilder(curPos,*curItem);
                    iter->goToID(curPos);
                }
                else idWidgetItem.insert(curPos,curItem);
                iter->next();
            }
        }
    }/*else {
        QTreeWidgetItem* singleItem = new QTreeWidgetItem(&item);
        singleItem->setText(0,varOwner.getVarByID(iter->currentID()).getName());
        singleItem->setText(1,varOwner.getVarByID(iter->currentID()).getDataType());
        idWidgetItem.insert(iter->currentID(),singleItem);
    }*/
}

DebuggerForm::DebuggerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebuggerForm)
{
    scan = nullptr;
    iter = nullptr;
    ui->setupUi(this);
    ui->tabWidget->setFont(QFont("Courier",10,QFont::Normal,false));
    iter = new NameSortIterator(varOwner.getIDStorage());
    ui->treeWidgetWatch->sortByColumn(0, Qt::AscendingOrder);
    connect(&memStor,SIGNAL(updateMemory(QStringList)),this,SLOT(updateMemory(QStringList)));
    scan = new ScanManager(&memStor);

    ui->tabWidget->setStyleSheet("QTabBar::tab {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                    "stop: 0 #FAFAFA, stop: 0.4 #F4F4F4,"
                                    "stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
        "border: 1px solid #C4C4C3;"
        "border-top-color: #C2C7CB; "
        "border-bottom-left-radius: 6px;"
        "border-bottom-right-radius: 6px;"
        "min-width: 8px;"
        "padding: 2px;"
        "}"
        "QTabBar::tab:selected {"
             "border-color: #9B9B9B;"
             "border-bottom-color: #FFFFFF;"
             "}"
        "QTabBar::tab:!selected {"
             "border-color: #9B9B9B;"
             "margin-top: 2px;"
             "}"
        "QTabBar::tab:selected, QTabBar::tab:hover {"
             "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                         "stop: 0 #f1f1f1, stop: 0.2 #dedede,"
                                         "stop: 0.3 #e8e8e8, stop: 1.0 #ffffff);"
             "}");
}

DebuggerForm::~DebuggerForm()
{
    delete ui;
    delete iter;
    delete scan;
}

void DebuggerForm::on_treeWidgetMain_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    // добавление элемента из основного дерева к дереву просмотра
    Q_UNUSED(column)
    if(idWidgetItem.values().contains(item)) {
        QString id = idWidgetItem.key(item);
        if(iter->goToID(id)) {
            VarItem var = varOwner.getVarByID(id);
            QStringList sList;
            QString varName;
            QString fullName = var.getName();
            if(iter->up()) {
                VarItem var = varOwner.getVarByID(iter->currentID());
                do{var = varOwner.getVarByID(iter->currentID());fullName = var.getName()+"."+fullName;}while (iter->up());
            }
            QStringList fNameList = fullName.split('.');
            fNameList.removeFirst();fNameList.removeFirst();
            foreach (QString s, fNameList) {
               varName += "." + s;
            }
            varName.remove(0,1);
            sList << varName << "" << "" << "0x"+QString::number(var.getMemAddress(),16).toUpper() << var.getDataType();
            QTreeWidgetItem* newItem = new QTreeWidgetItem(sList);
            idActiveWidgetItem.insert(id,newItem);
            var.setPriority(1);
            newItem->setToolTip(0,fullName);
            ui->treeWidgetWatch->addTopLevelItem(newItem);
            ui->treeWidgetWatch->setItemWidget(newItem,5,new QLineEdit("-",ui->treeWidgetWatch));

            scheduler.addReadOperation(var);
            scheduler.schedule();
        }
    }
}

void DebuggerForm::on_treeWidgetWatch_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    // удаление переменной из дерева просмотра
    Q_UNUSED(column)
    QString id = idActiveWidgetItem.key(item);
    VarItem var = varOwner.getVarByID(id);
    var.setPriority(0);
    varOwner.updateVarByID(id,var);
    idActiveWidgetItem.remove(id);
    ui->treeWidgetWatch->removeItemWidget(item,5);
    delete item;

    scheduler.removeReadOperation(var);
    scheduler.schedule();
}
void DebuggerForm::on_startButton_clicked()
{
    scan->setScheduler(&scheduler);
    scan->startDebugger();
}

void DebuggerForm::on_stopButton_clicked()
{
    scan->stopDebugger();
}

void DebuggerForm::updateMemory(QStringList ids)
{
    foreach (QString id, ids) {
        if(idActiveWidgetItem.contains(id)) {
            QTreeWidgetItem* item = idActiveWidgetItem.value(id);
            VarItem var = varOwner.getVarByID(id);
            int varSize=VarBytesValueConverter::getVarSize(var.getDataType());
            if(varSize) {
                QByteArray data = memStor.getData(var.getMemType(),var.getMemAddress(),varSize);
                if(data.count()==varSize) {
                    item->setText(1,VarBytesValueConverter::getValue(var.getDataType(),data));
                    item->setText(2,QDateTime::currentDateTime().time().toString());
                }
            }
        }
    }
}

void DebuggerForm::on_updateButton_clicked()
{
    idWidgetItem.clear();
    createTree();
    updateValuesTree();
    VarToMemConnector::updateConnection(memStor,varOwner.getIDStorage());
    update();
}

void DebuggerForm::updateValuesTree()
{
    QHash<QString,QString> fullNames;
    foreach (QTreeWidgetItem* item, idWidgetItem.values()) {
       QString fName = item->toolTip(0);
       fullNames.insert(fName,idWidgetItem.key(item));
    }
    QList<QTreeWidgetItem*> actItems = idActiveWidgetItem.values();
    for(int i=0;i<actItems.count();i++) {
        QString curId = idActiveWidgetItem.key(actItems.at(i));
        QString curFullName = actItems.at(i)->toolTip(0);
        QString newId = fullNames.value(curFullName);
        if(!newId.isEmpty()) {
            if(curId != newId) {
                VarItem var = varOwner.getVarByID(newId);
                idActiveWidgetItem.remove(curId);
                idActiveWidgetItem.insert(newId,actItems.at(i));
                actItems[i]->setText(3,"0x"+QString::number(var.getMemAddress(),16).toUpper());
                actItems[i]->setText(4,var.getDataType());
            }
        }
    }


}
