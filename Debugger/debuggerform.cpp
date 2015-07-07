#include "debuggerform.h"
#include "ui_debuggerform.h"

#include "namesortiterator.h"
#include <QMenu>
#include <QStringList>
#include <QLineEdit>


void DebuggerForm::createTree()
{
    vars = new CompositeVar();
    vars->setName("Переменные");
    CompositeVar* sysVars = new CompositeVar();
    sysVars->setName("Системные");
    sysVars->setDataType("sysNode");
    CompositeVar* userVars = new CompositeVar();
    userVars->setName("Пользовательские");
    userVars->setDataType("userNode");
    CompositeVar* var1 = new CompositeVar(userVars);
    CompositeVar* var2 = new CompositeVar(userVars);
    CompositeVar* var3 = new CompositeVar(userVars);
    var1->setName("a");var1->setDataType("unsigned int");
    var2->setName("b");var2->setDataType("float");
    var3->setName("c");var3->setDataType("char");
    var1->setMemType("ram");var1->setMemAddress(0);
    var2->setMemType("ram");var2->setMemAddress(4);
    var3->setMemType("ram");var3->setMemAddress(8);

    vars->addChild(sysVars);
    vars->addChild(userVars);
    CompositeVar* inoutVars = new CompositeVar();
    inoutVars->setName("входы/выходы");
    sysVars->addChild(inoutVars);
    CompositeVar* in0 = new CompositeVar();
    in0->setName("IN0");
    CompositeVar* in1 = new CompositeVar();
    in1->setName("IN1");
    inoutVars->addChild(in1);
    inoutVars->addChild(in0);
    for(int i=0;i<8;i++) {
        CompositeVar* ptr1 = new CompositeVar(in0);
        ptr1->setName("bit"+QString::number(i));
        ptr1->setDataType("bit");
        ptr1->setMemType("io");ptr1->setMemAddress(0);ptr1->setBitNum(i);
        CompositeVar* ptr2 = new CompositeVar(in1);
        ptr2->setName("bit"+QString::number(i));
        ptr2->setDataType("bit");
        ptr2->setMemType("io");ptr2->setMemAddress(1);ptr2->setBitNum(i);
    }
    CompositeVar* out0 = new CompositeVar(inoutVars);
    out0->setName("OUT0");
    CompositeVar* out1 = new CompositeVar(inoutVars);
    out1->setName("OUT1");
    CompositeVar* out2 = new CompositeVar(inoutVars);
    out2->setName("OUT2");
    for(int i=0;i<8;i++) {
        CompositeVar* ptr1 = new CompositeVar(out0);
        ptr1->setName("bit"+QString::number(i));
        ptr1->setDataType("bit");
        ptr1->setMemType("io");ptr1->setMemAddress(2);ptr1->setBitNum(i);
        CompositeVar* ptr2 = new CompositeVar(out1);
        ptr2->setName("bit"+QString::number(i));
        ptr2->setDataType("bit");
        ptr2->setMemType("io");ptr2->setMemAddress(3);ptr2->setBitNum(i);
        CompositeVar* ptr3 = new CompositeVar(out2);
        ptr3->setName("bit"+QString::number(i));
        ptr3->setDataType("bit");
        ptr3->setMemType("io");ptr3->setMemAddress(4);ptr3->setBitNum(i);
    }

    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidgetMain);
    item->setText(0,vars->getName());
    treeBuilder(vars,*item);

    QString style = "QTreeWidget::item:!selected "
       "{ "
         "border: 1px solid gainsboro; "
         "border-left: none; "
         "border-top: none; "
       "}"
       "QTreeWidget::item:selected {}";



    ui->treeWidgetMain->setStyleSheet(style);
    ui->treeWidgetMain->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),
                    SLOT(on_treeWidgetMain_customContextMenuRequested(const QPoint&)));
    ui->treeWidgetMain->setItemExpanded(item,true);
    ui->treeWidgetMain->header()->resizeSections(QHeaderView::ResizeToContents);
}

void DebuggerForm::updateTrees()
{

}

void DebuggerForm::treeBuilder(CompositeVar *var, QTreeWidgetItem &item)
{
    NameSortIterator iter(var);
    if(iter.isNode()) {
        if(iter.down()){
            for(int i=0;i<iter.getItemCount();i++) {
                VarItem* childVar = iter.current();
                QTreeWidgetItem* curItem = new QTreeWidgetItem(&item);
                curItem->setText(0,childVar->getName());
                curItem->setText(1,childVar->getDataType());

                if(iter.isNode()) treeBuilder(dynamic_cast<CompositeVar*>(childVar),*curItem);
                else {
                    varGui.addLink(childVar,curItem);
                }
                iter.next();
            }
        }
    }else {
        QTreeWidgetItem* singleItem = new QTreeWidgetItem(&item);
        singleItem->setText(0,var->getName());
        singleItem->setText(1,var->getDataType());
        varGui.addLink(var,singleItem);
    }
}

DebuggerForm::DebuggerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebuggerForm)
{
    ui->setupUi(this);
    ui->tabWidget->setFont(QFont("Courier",10,QFont::Normal,false));
    createTree();
}

DebuggerForm::~DebuggerForm()
{
    delete ui;
    delete vars;
}

void DebuggerForm::on_treeWidgetMain_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* item = ui->treeWidgetMain->itemAt(pos);
    if(item) {
        VarItem* var = varGui.getVar(item);
        if(var!=nullptr) {
            QMenu *menu=new QMenu(this);

            menu->addAction("добавить в список");//, this,SLOT(on_copy()));

            menu->popup(ui->treeWidgetMain->viewport()->mapToGlobal(pos));
        }
    }


}


void DebuggerForm::on_treeWidgetMain_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    VarItem* var = varGui.getVar(item);
    if(var!=nullptr) {
        QStringList sList;
        QString varName = var->getName();
        CompositeVar* cVar = dynamic_cast<CompositeVar*>(var);
        if(cVar) {
            CompositeVar* parVar = cVar->getParent();
            if(parVar) {
                if((parVar->getDataType()!="userNode")&&(parVar->getDataType()!="sysNode"))
                varName = parVar->getName()+"."+varName;
            }
        }
        sList << varName << "" << "" << "" << var->getDataType();
        QTreeWidgetItem* newItem = new QTreeWidgetItem(sList);
        ui->treeWidgetWatch->addTopLevelItem(newItem);
        ui->treeWidgetWatch->setItemWidget(newItem,5,new QLineEdit("-",ui->treeWidgetWatch));

    }
}

void DebuggerForm::on_treeWidgetWatch_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    ui->treeWidgetWatch->removeItemWidget(item,5);
    delete item;
}
