#include "patterneditorwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
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

void PatternEditorWidget::bitVarState()
{
    isEditable->setCheckState(Qt::Unchecked);
    isSigned->setCheckState(Qt::Unchecked);
    isEditable->setEnabled(false);
    isSigned->setEnabled(false);
}

void PatternEditorWidget::timeVarState()
{
    isEditable->setCheckState(Qt::Checked);
    isSigned->setCheckState(Qt::Unchecked);
    isEditable->setEnabled(false);
    isSigned->setEnabled(false);
    patternEdit->setEnabled(false);
}

void PatternEditorWidget::unexistVar(PultVarDefinition &vDef)
{
    nameEdit->setText(vDef.getName());
    typeEdit->setText(vDef.getDataType());
    commentEdit->setText("");
    patternEdit->setText(vDef.getPattern());
    curDef = vDef;
    curVarID = "";
}

void PatternEditorWidget::showEditAndSign(PultVarDefinition &vDef)
{
    isEditable->setEnabled(true);
    isSigned->setEnabled(true);

    if(vDef.isEditable()) isEditable->setCheckState(Qt::Checked);
        else isEditable->setCheckState(Qt::Unchecked);
    if(vDef.getForceSign()) isSigned->setCheckState(Qt::Checked);
    else isSigned->setCheckState(Qt::Unchecked);
}

void PatternEditorWidget::showVar(PultVarDefinition &vDef, const QString &comment)
{
    QString vName = varOwner.getFullNameOfVar(vDef.getId()).remove(QRegExp("^[^\\.]*\\.[^\\.]*\\."));
    if(!vName.contains(QRegExp(".*\\.\\d+.*"))) {
        QStringList names = vName.split(".");
        vName = names.last();
    }

    nameEdit->setStyleSheet("QLineEdit{background: yellow;}");
    nameEdit->setText(vName);
    typeEdit->setText(vDef.getDataType());
    commentEdit->setText(comment);
    patternEdit->setText(vDef.getPattern());
}

void PatternEditorWidget::noVar()
{
    applyButton->setText("Добавить переменную");
    nameEdit->setStyleSheet("QLineEdit{background: white;}");
    nameEdit->setText("");
    typeEdit->setText("");
    commentEdit->setText("");
    patternEdit->setText("");
    isEditable->setCheckState(Qt::Unchecked);
    isSigned->setCheckState(Qt::Unchecked);
    curVarID="";
}

PultVarDefinition PatternEditorWidget::getVar(VarItem &var)
{
    PultVarDefinition vp;
    vp.setId(curVarID);
    QString pText = patternEdit->text();
    pText.replace(',','.');
    vp.setPattern(pText);
    vp.setDataType(var.getDataType());
    vp.setName(varOwner.getPultNameOfVar(curVarID));
    vp.setForceSign(isSigned->isChecked());
    vp.setEditable(isEditable->isChecked());
    vp.setExist(true);
    QRegExp eeExp("^EE(\\d+)");
    if(eeExp.indexIn(var.getName()) != -1) {
        int num = eeExp.cap(1).toInt();
        vp.setEEVar(true);
        vp.setEEposInSettingsTable(num);
    }else {
        vp.setEEVar(false);
    }
    return vp;
}

void PatternEditorWidget::updVar(VarItem &var)
{
    var.setComment(commentEdit->text());
    var.setEditable(isEditable->isChecked());
    var.setSigned(isSigned->isChecked());
    varOwner.updateVarByID(curVarID,var);
}

void PatternEditorWidget::createWidgets()
{
    QVBoxLayout* vLayout = new QVBoxLayout(this);

    tree = new QTreeWidget();
    connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(doubleClickedVar(QTreeWidgetItem*,int)));

    QStringList header;
    header << "имя" << "тип";
    tree->setHeaderLabels(header);
    vLayout->addWidget(tree,100);

    QLabel* nameLabel = new QLabel("имя:");
    nameEdit = new QLineEdit();
    nameEdit->setReadOnly(true);

    vLayout->addWidget(nameLabel,1);
    vLayout->addWidget(nameEdit,1);

    QLabel* typeLabel = new QLabel("тип:");
    typeEdit = new QLineEdit();
    typeEdit->setEnabled(false);

    vLayout->addWidget(typeLabel);
    vLayout->addWidget(typeEdit);

    QLabel* commentLabel = new QLabel("комментарий:");
    commentEdit = new QLineEdit();
    vLayout->addWidget(commentLabel);
    vLayout->addWidget(commentEdit);

    QLabel* patternLabel = new QLabel("шаблон:");
    patternEdit = new QLineEdit();
    vLayout->addWidget(patternLabel);
    vLayout->addWidget(patternEdit);

    isEditable = new QCheckBox("разрешить изменение с пульта");
    vLayout->addWidget(isEditable);

    isSigned = new QCheckBox("принудительная знаковость");
    vLayout->addWidget(isSigned);

    QHBoxLayout* hButtonLayout = new QHBoxLayout() ;
    applyButton = new QPushButton(QIcon(":/edit_32.ico"),"Добавить переменную");
    connect(applyButton,SIGNAL(clicked()),this,SLOT(applyVar()));

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    hButtonLayout->addWidget(spacer);
    hButtonLayout->addWidget(applyButton);
    vLayout->addLayout(hButtonLayout);
}

void PatternEditorWidget::fillVarsTree()
{
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
}

PatternEditorWidget::PatternEditorWidget(Display &d, VarsCreator &vCr, QWidget *parent) :
    QWidget(parent), varOwner(vCr), displ(d),
    currentX(0), currentY(0)
{
    setMinimumSize(100,100);
    iter = new NameSortIterator(vCr.getIDStorage());

    createWidgets();
    fillVarsTree();
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
    delete iter;
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
    patternEdit->setEnabled(true);
    if(str.isVarHere(x)) {
        PultVarDefinition cursVarDef;
        str.getVarInPos(x,cursVarDef);
        applyButton->setText("Изменить переменную");
        if(cursVarDef.isExist()) {
            QString id = cursVarDef.getId();
            if(!id.isEmpty()) {
                VarItem var = varOwner.getVarByID(id);

                if(var.getBitNum()!=-1) {
                    bitVarState();
                }else {
                    if(cursVarDef.getName().contains("sysTime_")) {timeVarState();}
                    else {showEditAndSign(cursVarDef);}
                }
                showVar(cursVarDef,var.getComment());
                curVarID = id;
                curDef = cursVarDef;
            }
        }else {unexistVar(cursVarDef);}
    }else {noVar();}
}

void PatternEditorWidget::doubleClickedVar(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    if(idWidgetItem.values().contains(item)) {
        QString id = idWidgetItem.key(item);
        VarItem var = varOwner.getVarByID(id);
        QString vName = item->toolTip(0).remove(QRegExp("^[^\\.]*\\.[^\\.]*\\."));
        if(!vName.contains(QRegExp(".*\\.\\d+.*"))) {
            QStringList names = vName.split(".");
            vName = names.last();
        }
        nameEdit->setStyleSheet("QLineEdit{background: red;}");
        nameEdit->setText(vName);
        typeEdit->setText(var.getDataType());
        commentEdit->setText(var.getComment());
        curVarID = id;
    }
}

void PatternEditorWidget::applyVar()
{
    if(checkVar()) {
        VarItem var = varOwner.getVarByID(curVarID);
        patternEdit->setEnabled(true);
        if(var.getBitNum()!=-1) {
            bitVarState();
        }else {
            isEditable->setEnabled(true);
            isSigned->setEnabled(true);
            if(varOwner.getPultNameOfVar(curVarID).contains("sysTime_")) {
                timeVarState();
                patternEdit->setText("11");
            }
        }

        PultVarDefinition vp = getVar(var);
        QString dataType = varOwner.getVarByID(curVarID).getDataType();
        if(VarPattern::checkPattern(vp.getPattern(),dataType)) {
            DisplayStr str = displ.getString(currentY,displ.getCurSubStrNum(currentY));
            if(str.isVarHere(currentX)) {
                updVar(var);
                displ.updVar(vp);
            }else {
                if(displ.addVar(vp)) {
                    updVar(var);
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
