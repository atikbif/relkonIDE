#include "strlistwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QRegExp>
#include <QMenu>
#include <QLabel>
#include <QApplication>

StrListWidget::StrListWidget(Display &d, QWidget *parent) : QWidget(parent),
    displ(d)
{
    phont = new LCDPhont();
    QVBoxLayout* layoutMain = new QVBoxLayout(this);
    QHBoxLayout* layoutHeader = new QHBoxLayout();
    QHBoxLayout* layoutData = new QHBoxLayout();
    for(int i=0;i<displ.getStrCount();i++) {
        QLabel *lab = new QLabel("<b>строка "+QString::number(i+1)+":</b>");
        lab->setTextFormat(Qt::RichText);
        lab->setAlignment(Qt::AlignHCenter);
        layoutHeader->addWidget(lab);
        QListWidget *w = new QListWidget();
        w->setSelectionMode(QAbstractItemView::ExtendedSelection);
        lists += w;
        layoutData->addWidget(lists.last());
        lists.last()->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(lists.last(),SIGNAL(customContextMenuRequested(QPoint)),
                 this,SLOT(showContextMenuForList(QPoint)));
        updateList(i);
        curStrNumChanged(i,0);
        connect(lists.last(),SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));
    }
    layoutMain->addLayout(layoutHeader);
    layoutMain->addLayout(layoutData);
    insBefore = new QAction(QIcon("://ins_16.ico"),"Добавить перед",this);
    insAfter = new QAction(QIcon("://ins_16.ico"),"Добавить после",this);
    delStr = new QAction(QIcon("://del_32.ico"),"Удалить",this);
    enableDisableStr = new QAction(QIcon("://act_32.ico"),"откл/вкл строку",this);
    copyStr = new QAction(QIcon("://copy_32.ico"),"копировать",this);
    pasteStr = new QAction(QIcon("://paste_32.ico"),"вставить",this);
    cutStr = new QAction(QIcon("://cut.ico"),"вырезать",this);
    actGroup = new QAction(QIcon("://on.ico"),"включить строки",this);
    deactGroup = new QAction(QIcon("://off.ico"),"отключить строки",this);
    connect(insBefore,SIGNAL(triggered()),this,SLOT(insertStringBefore()));
    connect(insAfter,SIGNAL(triggered()),this,SLOT(insertStringAfter()));
    connect(delStr,SIGNAL(triggered()),this,SLOT(deleteString()));
    connect(enableDisableStr,SIGNAL(triggered()),this,SLOT(activateDesactString()));
    connect(copyStr,SIGNAL(triggered()),this,SLOT(copyString()));
    connect(pasteStr,SIGNAL(triggered()),this,SLOT(pasteString()));
    connect(cutStr,SIGNAL(triggered()),this,SLOT(cutString()));
    connect(actGroup,SIGNAL(triggered()),this,SLOT(activateGroup()));
    connect(deactGroup,SIGNAL(triggered()),this,SLOT(desactivateGroup()));
}

StrListWidget::~StrListWidget()
{
    delete phont;
    foreach (QListWidget *ptr, lists) {
       delete ptr;
    }
}

void StrListWidget::updateList(int num)
{
    if((num>=0)&&(num<lists.count())) {
        if(num<displ.getStrCount()) {
            lists[num]->clear();
            int subStrNum = 0;
            for(int i=0;i<displ.getSubStrCount(num);i++) {
                DisplayStr str = displ.getString(num,i);
                QString strText;
                for(int j=0;j<str.getLength();j++) {
                    int unicodeValue = phont->getUnicodeValue(str.getSymbol(j));
                    strText += QChar((ushort)unicodeValue);
                }
                if(str.isActive()) {
                    strText = QString::number(subStrNum) + ") " + strText;
                    subStrNum++;
                    lists[num]->addItem(strText);
                    lists[num]->item(i)->setTextColor(Qt::darkBlue);
                }else {
                    lists[num]->addItem(strText);
                    lists[num]->item(i)->setTextColor(Qt::darkGray);
                }
            }
        }
    }
}

bool StrListWidget::testStrNum(int strNum, int subStrNum)
{
    if((strNum>=0)&&(strNum<displ.getStrCount())) {
        if((subStrNum>=0)&&(subStrNum<displ.getSubStrCount(strNum))) return true;
    }
    return false;
}

void StrListWidget::strChanged(int strNum, int subStrNum)
{
    //if(updFl) {
    if((strNum>=0)&&(strNum<lists.count())) {
        if((subStrNum>=0)&&(subStrNum<lists.at(strNum)->count())) {
            QListWidgetItem* item = lists[strNum]->item(subStrNum);
            DisplayStr str = displ.getString(strNum,subStrNum);
            QString strText;
            for(int j=0;j<str.getLength();j++) {
                int unicodeValue = phont->getUnicodeValue(str.getSymbol(j));
                strText += QChar((ushort)unicodeValue);
            }
            if(str.isActive()) {
                int num = 0;
                QRegExp numInList("^(\\d+)");
                if(numInList.indexIn(item->text(), 0) != -1) {
                    num = numInList.cap(1).toInt();
                }
                strText = QString::number(num) + ") " + strText;
            }
            item->setText(strText);
        }
    }//}
}

void StrListWidget::strListChanged(int strNum)
{
    updateList(strNum);
}

void StrListWidget::itemClicked(const QModelIndex &index)
{
    if(!index.isValid()) return;
    int row = index.row();
    QListWidget* lWidget = dynamic_cast<QListWidget*>(sender());
    if(lWidget!=nullptr) {
        for(int i=0;i<lists.count();i++) {
           if(lists.at(i)==lWidget) {
               if(row>=0) {
                   if(lWidget->selectedItems().count()<2) {
                        displ.goToStr(i,row);
                        emit updFocus();
                   }
               }
           }
        }
    }
}

void StrListWidget::curStrNumChanged(int strNum, int subStrNum)
{
    if((strNum>=0)&&(strNum<lists.count())) {
        if((subStrNum>=0)&&(subStrNum<lists.at(strNum)->count())) {
            QListWidget* w = lists[strNum];
            w->setCurrentRow(subStrNum);
        }
    }
}

void StrListWidget::showContextMenuForList(const QPoint &pos)
{
    QListWidget* w = dynamic_cast<QListWidget*>(sender());
    if(w!=nullptr) {
        for(int i=0;i<lists.count();i++) {
            if(lists.at(i)==w) {
                actData.strNum = i;
                actData.subStrNum = w->currentRow();
            }
        }
        QMenu contextMenu(tr("Context menu"), this);
        if(w->selectedItems().count()<2) {
            contextMenu.addAction(insBefore);
            contextMenu.addAction(insAfter);
            contextMenu.addAction(enableDisableStr);
            contextMenu.addSeparator();
        }

        contextMenu.addAction(cutStr);
        contextMenu.addAction(copyStr);

        if(w->selectedItems().count()<2) {
            contextMenu.addAction(pasteStr);
        }else {
            contextMenu.addAction(actGroup);
            contextMenu.addAction(deactGroup);
        }
        contextMenu.addSeparator();
        contextMenu.addAction(delStr);
        contextMenu.exec(w->mapToGlobal(pos));
    }

}

void StrListWidget::insertStringBefore()
{
    if(testStrNum(actData.strNum,actData.subStrNum)) {
        displ.addEmptyStrBefore(actData.strNum,actData.subStrNum);
    }
}

void StrListWidget::insertStringAfter()
{
    if(testStrNum(actData.strNum,actData.subStrNum)) {
        displ.addEmptyStrAfter(actData.strNum,actData.subStrNum);
    }
}

void StrListWidget::deleteString()
{
    if((actData.strNum<0)||(actData.strNum>=lists.count())) return;
    QListWidget *w = lists.at(actData.strNum);
    QList<QListWidgetItem*> selItems = w->selectedItems();
    if(selItems.count()<2) {
        if(testStrNum(actData.strNum,actData.subStrNum)) {
            displ.deleteStr(actData.strNum,actData.subStrNum);
        }
    }else {
        QVector<int> strNums;
        for(int i=0;i<selItems.count();++i) {
            strNums.append(w->row(selItems.at(i)));
        }
        int cnt = selItems.count();
        qSort(strNums);
        for(int i=0;i<cnt;++i) {
            displ.deleteStr(actData.strNum,strNums.at(i)-i);
        }
    }

}

void StrListWidget::activateDesactString()
{
    if(testStrNum(actData.strNum,actData.subStrNum)) {
        displ.toggleActive(actData.strNum,actData.subStrNum);
    }
}

void StrListWidget::copyString()
{
    if((actData.strNum<0)||(actData.strNum>=lists.count())) return;
    QListWidget *w = lists.at(actData.strNum);
    QList<QListWidgetItem*> selItems = w->selectedItems();
    if(selItems.count()<2) {
        if(testStrNum(actData.strNum,actData.subStrNum)) {
            displ.clearCopyStrList();
            displ.copyStrToBuffer(actData.strNum,actData.subStrNum);
            curStrNumChanged(actData.strNum,displ.getCurSubStrNum(actData.strNum));
            emit updFocus();
        }
    }else {
        QVector<int> strNums;
        for(int i=0;i<selItems.count();++i) {
            strNums.append(w->row(selItems.at(i)));
        }
        displ.copyStrListToBuffer(actData.strNum,strNums);
    }

}

void StrListWidget::pasteString()
{
    if((actData.strNum<0)||(actData.strNum>=lists.count())) return;
    if(displ.getCopyStrListCount()==0) {
        if(testStrNum(actData.strNum,actData.subStrNum)) {
            displ.addEmptyStrBefore(actData.strNum, actData.subStrNum);
            displ.pasteStrFromBuffer(actData.strNum, actData.subStrNum);
            emit updFocus();
        }
    }else {
        int subStrNum = actData.subStrNum;
        for(int i=0;i<displ.getCopyStrListCount();++i) {
            displ.addEmptyStrBefore(actData.strNum, subStrNum);
            displ.pasteStrFromCopyListBuffer(actData.strNum, subStrNum,i);
            subStrNum++;
        }
        emit updFocus();
    }

}

void StrListWidget::cutString()
{
    if((actData.strNum<0)||(actData.strNum>=lists.count())) return;
    QListWidget *w = lists.at(actData.strNum);
    QList<QListWidgetItem*> selItems = w->selectedItems();
    if(selItems.count()<2) {
        if(testStrNum(actData.strNum,actData.subStrNum)) {
            displ.clearCopyStrList();
            displ.copyStrToBuffer(actData.strNum,actData.subStrNum);
            displ.deleteStr(actData.strNum,actData.subStrNum);
            curStrNumChanged(actData.strNum,displ.getCurSubStrNum(actData.strNum));
            emit updFocus();
        }
    }else {
        QVector<int> strNums;
        for(int i=0;i<selItems.count();++i) {
            strNums.append(w->row(selItems.at(i)));
        }
        displ.copyStrListToBuffer(actData.strNum,strNums);
        int cnt = selItems.count();
        qSort(strNums);
        for(int i=0;i<cnt;++i) {
            displ.deleteStr(actData.strNum,strNums.at(i)-i);
        }
    }
}

void StrListWidget::activateGroup()
{
    if((actData.strNum<0)||(actData.strNum>=lists.count())) return;
    QListWidget *w = lists.at(actData.strNum);
    QList<QListWidgetItem*> selItems = w->selectedItems();
    if(selItems.count()>=2) {
        QVector<int> strNums;
        for(int i=0;i<selItems.count();++i) {
            strNums.append(w->row(selItems.at(i)));
        }
        for(int i=0;i<strNums.count();++i) {
            if(!displ.getString(actData.strNum,strNums.at(i)).isActive()) displ.toggleActive(actData.strNum,strNums.at(i));
        }
    }
}

void StrListWidget::desactivateGroup()
{
    if((actData.strNum<0)||(actData.strNum>=lists.count())) return;
    QListWidget *w = lists.at(actData.strNum);
    QList<QListWidgetItem*> selItems = w->selectedItems();
    if(selItems.count()>=2) {
        QVector<int> strNums;
        for(int i=0;i<selItems.count();++i) {
            strNums.append(w->row(selItems.at(i)));
        }
        for(int i=0;i<strNums.count();++i) {
            if(displ.getString(actData.strNum,strNums.at(i)).isActive()) displ.toggleActive(actData.strNum,strNums.at(i));
        }
    }
}

void StrListWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Z:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            displ.undo();
        }
        break;
    case Qt::Key_Y:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            displ.redo();
        }
        break;
    }
}

