#include "patterneditorwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QIcon>
#include <QDesktopWidget>
#include <QRegExp>
#include <QMessageBox>

void PatternEditorWidget::treeBuilder(const QString &varID, QTreeWidgetItem &item)
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
    }
}

bool PatternEditorWidget::checkVar()
{
    if(curVarID.isEmpty()) return false;
    return true;
}

PatternEditorWidget::PatternEditorWidget(Display &d, VarsCreator &vCr, QWidget *parent) :
    QWidget(parent), varOwner(vCr), displ(d),
    currentX(0), currentY(0)
{
    setMinimumSize(100,100);
    iter = new NameSortIterator(vCr.getIDStorage());

    QGridLayout* grLayout = new QGridLayout(this);
    setLayout(grLayout);

    tree = new QTreeWidget();

    connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(doubleClickedVar(QTreeWidgetItem*,int)));

    QStringList header;
    header << "имя" << "тип";
    tree->setHeaderLabels(header);
    grLayout->addWidget(tree,0,0,10,4);

    QDesktopWidget desk;
    int editWidth = desk.availableGeometry().width()*0.15;

    QLabel* nameLabel = new QLabel("имя:");
    nameEdit = new QLineEdit();
    nameEdit->setFixedWidth(editWidth);

    grLayout->addWidget(nameLabel,2,4,1,1);
    grLayout->addWidget(nameEdit,2,5,1,2);

    QLabel* typeLabel = new QLabel("тип:");
    typeEdit = new QLineEdit();
    typeEdit->setFixedWidth(editWidth);

    grLayout->addWidget(typeLabel,3,4,1,1);
    grLayout->addWidget(typeEdit,3,5,1,2);

    QLabel* commentLabel = new QLabel("комментарий:");
    commentEdit = new QLineEdit();
    commentEdit->setFixedWidth(editWidth);
    grLayout->addWidget(commentLabel,4,4,1,1);
    grLayout->addWidget(commentEdit,4,5,1,2);

    QLabel* patternLabel = new QLabel("шаблон:");
    patternEdit = new QLineEdit();
    patternEdit->setFixedWidth(editWidth);
    grLayout->addWidget(patternLabel,5,4,1,1);
    grLayout->addWidget(patternEdit,5,5,1,2);

    isEditable = new QCheckBox("разрешить изменение с пульта");
    grLayout->addWidget(isEditable,6,4,1,2);

    isSigned = new QCheckBox("принудительная знаковость");
    grLayout->addWidget(isSigned,7,4,1,2);

    applyButton = new QPushButton(QIcon(":/edit_32.ico"),"Вставить");
    connect(applyButton,SIGNAL(clicked()),this,SLOT(applyVar()));
    grLayout->addWidget(applyButton,9,6,1,1);


    QTreeWidgetItem* item = new QTreeWidgetItem(tree);

    if(varOwner.getIDList().count()) {
        iter->goToID(varOwner.getIDList().at(0));
        if(iter->topFirst()) {
            item->setText(0,varOwner.getVarByID(iter->currentID()).getName());
            treeBuilder(iter->currentID(),*item);
        }
    }

    QString style = "QTreeWidget::item:!selected "
       "{ border: 1px solid gainsboro; border-left: none; border-top: none; }";

    tree->setStyleSheet(style);
    tree->setStyleSheet(style);

    tree->setItemExpanded(item,true);
    tree->header()->resizeSections(QHeaderView::ResizeToContents);

    setFocusPolicy(Qt::ClickFocus);
}

void PatternEditorWidget::updateVarsTree()
{
    tree->clear();
    QTreeWidgetItem* item = new QTreeWidgetItem(tree);
    if(varOwner.getIDList().count()) {
        iter->goToID(varOwner.getIDList().at(0));
        if(iter->topFirst()) {
            item->setText(0,varOwner.getVarByID(iter->currentID()).getName());
            treeBuilder(iter->currentID(),*item);
        }
    }
    tree->setItemSelected(item,true);
    tree->setItemExpanded(item,true);
    tree->header()->resizeSections(QHeaderView::ResizeToContents);
}

PatternEditorWidget::~PatternEditorWidget()
{

}

void PatternEditorWidget::newProject()
{
    updTree();
}

void PatternEditorWidget::saveProject()
{

}

void PatternEditorWidget::openProject()
{
    updTree();
}

void PatternEditorWidget::updTree()
{
    idWidgetItem.clear();
    updateVarsTree();
}

void PatternEditorWidget::cursorPosChanged(int x, int y)
{
    currentX = x;
    currentY = y;
    DisplayStr str = displ.getString(y,displ.getCurSubStrNum(y));
    if(str.isVarHere(x)) {
        applyButton->setText("Изменить");
        QString id = str.getVarID(x);
        QString pattern = str.getVarPatern(x);
        if(!id.isEmpty()) {
            VarItem var = varOwner.getVarByID(id);
            nameEdit->setText(varOwner.getFullNameOfVar(id).remove(QRegExp("^[^\\.]*\\.[^\\.]*\\.")));
            typeEdit->setText(var.getDataType());
            commentEdit->setText(var.getComment());
            patternEdit->setText(pattern);
            if(var.isEditable()) isEditable->setCheckState(Qt::Checked);
                else isEditable->setCheckState(Qt::Unchecked);
            if(var.isSigned()) isSigned->setCheckState(Qt::Checked);
                else isSigned->setCheckState(Qt::Unchecked);
            curVarID = id;
        }
    }else {
        applyButton->setText("Вставить");
        nameEdit->setText("");
        typeEdit->setText("");
        commentEdit->setText("");
        patternEdit->setText("");
        isEditable->setCheckState(Qt::Unchecked);
        isSigned->setCheckState(Qt::Unchecked);
        curVarID="";
    }
}

void PatternEditorWidget::doubleClickedVar(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    if(idWidgetItem.values().contains(item)) {
        QString id = idWidgetItem.key(item);
        VarItem var = varOwner.getVarByID(id);
        nameEdit->setText(item->toolTip(0).remove(QRegExp("^[^\\.]*\\.[^\\.]*\\.")));
        typeEdit->setText(var.getDataType());
        commentEdit->setText(var.getComment());
        curVarID = id;
    }
}

void PatternEditorWidget::applyVar()
{
    if(checkVar()) {
        VarPattern vp(curVarID,patternEdit->text());
        QString dataType = varOwner.getVarByID(curVarID).getDataType();
        if(vp.checkPattern(dataType)) {
            DisplayStr str = displ.getString(currentY,displ.getCurSubStrNum(currentY));
            if(str.isVarHere(currentX)) {
                QString id = str.getVarID(currentX);
                if(!id.isEmpty()) {
                    if(displ.updVar(vp)) {
                        VarItem var = varOwner.getVarByID(curVarID);
                        var.setComment(commentEdit->text());
                        var.setEditable(isEditable->isChecked());
                        var.setSigned(isSigned->isChecked());
                        varOwner.updateVarByID(curVarID,var);
                    }
                }
            }else {
                if(displ.addVar(vp)) {
                    VarItem var = varOwner.getVarByID(curVarID);
                    var.setComment(commentEdit->text());
                    var.setEditable(isEditable->isChecked());
                    var.setSigned(isSigned->isChecked());
                    varOwner.updateVarByID(curVarID,var);
                    applyButton->setText("Изменить");
                }
            }
            emit updFocus();
        }else {
            QMessageBox::warning(this, tr("Редактор переменных"),
                                           tr("Некорректный шаблон вывода переменной"),
                                           QMessageBox::Close);
        }
    }else {
        QMessageBox::warning(this, tr("Редактор переменных"),
                                       tr("Выбранную переменную невозможно отобразить на пульте"),
                                       QMessageBox::Close);
    }
}
