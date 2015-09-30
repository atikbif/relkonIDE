#include "strlistwidget.h"

#include <QHBoxLayout>
#include <QString>
#include <QRegExp>
#include <QMenu>

StrListWidget::StrListWidget(Display &d, QWidget *parent) : QWidget(parent),
    displ(d)
{
    const QString phontFileName = "lcd_phont.rph";
    phont = new LCDPhont(phontFileName);
    QHBoxLayout* layout = new QHBoxLayout(this);
    for(int i=0;i<displ.getStrCount();i++) {
        lists += new QListWidget();
        layout->addWidget(lists.last());
        lists.last()->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(lists.last(),SIGNAL(customContextMenuRequested(QPoint)),
                 this,SLOT(showContextMenuForList(QPoint)));
        updateList(i);
        curStrNumChanged(i,0);
        connect(lists.last(),SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));
    }
    insBefore = new QAction(QIcon("://ins_16.ico"),"Добавить перед",this);
    insAfter = new QAction(QIcon("://ins_16.ico"),"Добавить после",this);
    delStr = new QAction(QIcon("://del_32.ico"),"Удалить",this);
    enableDisableStr = new QAction(QIcon("://act_32.ico"),"откл/вкл строку",this);
    copyStr = new QAction(QIcon("://copy_32.ico"),"копировать",this);
    pasteStr = new QAction(QIcon("://paste_32.ico"),"вставить",this);
    connect(insBefore,SIGNAL(triggered()),this,SLOT(insertStringBefore()));
    connect(insAfter,SIGNAL(triggered()),this,SLOT(insertStringAfter()));
    connect(delStr,SIGNAL(triggered()),this,SLOT(deleteString()));
    connect(enableDisableStr,SIGNAL(triggered()),this,SLOT(activateDesactString()));
    connect(copyStr,SIGNAL(triggered()),this,SLOT(copyString()));
    connect(pasteStr,SIGNAL(triggered()),this,SLOT(pasteString()));
}

StrListWidget::~StrListWidget()
{

}

void StrListWidget::updateList(int num)
{
    if((num>=0)&&(num<lists.count())) {
        if(num<displ.getStrCount()) {
            lists[num]->clear();
            int subStrNum = 1;
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
                    lists[num]->item(i)->setTextColor(Qt::blue);
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
    }
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
                   displ.goToStr(i,row);
                   emit updFocus();
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
        contextMenu.addAction(insBefore);
        contextMenu.addAction(insAfter);
        contextMenu.addAction(enableDisableStr);
        contextMenu.addSeparator();
        contextMenu.addAction(copyStr);
        contextMenu.addAction(pasteStr);
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
    if(testStrNum(actData.strNum,actData.subStrNum)) {
        displ.deleteStr(actData.strNum,actData.subStrNum);
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
    if(testStrNum(actData.strNum,actData.subStrNum)) {
        displ.copyStrToBuffer(actData.strNum,actData.subStrNum);
    }
}

void StrListWidget::pasteString()
{
    if(testStrNum(actData.strNum,actData.subStrNum)) {
        displ.pasteStrFromBuffer(actData.strNum,actData.subStrNum);
    }
}

