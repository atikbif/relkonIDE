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
//    QString fileName = QApplication::applicationDirPath();
//    fileName += "/src/input.kon";
//    VarParser parser(fileName);
//    parser.createXML();
//    createTree();
//    repaint();
    VarToMemConnector::updateConnection(memStor,varOwner.getIDStorage());
    connect(&memStor,SIGNAL(updateMemory(QStringList)),this,SLOT(updateMemory(QStringList)));
    scan = new ScanManager(&memStor);
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
            QString varName = var.getName();
            QString fullName = varName;
            if(iter->up()) {
                VarItem var = varOwner.getVarByID(iter->currentID());
                QString dataType = var.getDataType();
                if((dataType!="userNode")&&(dataType!="sysNode")){
                    varName = var.getName()+"."+varName;
                }
                do{var = varOwner.getVarByID(iter->currentID());fullName = var.getName()+"."+fullName;}while (iter->up());
            }
            sList << varName << "" << "" << "" << var.getDataType();
            QTreeWidgetItem* newItem = new QTreeWidgetItem(sList);
            idActiveWidgetItem.insert(id,newItem);
            var.setPriority(1);
            newItem->setToolTip(0,fullName);
            ui->treeWidgetWatch->addTopLevelItem(newItem);
            ui->treeWidgetWatch->setItemWidget(newItem,5,new QLineEdit("-",ui->treeWidgetWatch));
        }
    }
}

void DebuggerForm::on_treeWidgetWatch_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    // удаление переменной из дерева просмотра
    Q_UNUSED(column)
    QString id = idActiveWidgetItem.key(item);
    varOwner.getVarByID(id).setPriority(0);
    idActiveWidgetItem.remove(id);
    ui->treeWidgetWatch->removeItemWidget(item,5);
    delete item;
}
void DebuggerForm::on_startButton_clicked()
{
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
                }
            }
        }
    }
}

void DebuggerForm::on_updateButton_clicked()
{
    QString fileName = RCompiler::getKonFileName();
    VarParser parser(fileName);
    parser.createXML();
    createTree();
    update();
}
