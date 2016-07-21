#include "dialogwordcolors.h"
#include "ui_dialogwordcolors.h"
#include <QColorDialog>
#include <QPalette>
#include <QBrush>

DialogWordColors::DialogWordColors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWordColors)
{
    ui->setupUi(this);

}

DialogWordColors::~DialogWordColors()
{
    delete ui;
}

void DialogWordColors::setColorList(ColorList &list)
{
    cList = list;
    ui->listWidget->clear();
    for(int i=0;i<cList.getCount();++i) {
        QSharedPointer<ColorForWord> c = cList.getColor(i);
        ui->listWidget->addItem(cList.getWordDefinition(c->getCodeWord()));

        QColor colorBackgr;
        if(c->isSystem()) {
            colorBackgr.setRgb(c->getSysRed(),c->getSysGreen(),c->getSysBlue());
        }
        else {
            colorBackgr.setRgb(c->getUserRed(),c->getUserGreen(),c->getUserBlue());
        }
        QColor colorText;
        if(c->getUserRed()>128) {colorText.setRgb(0,0,0);}
        else colorText.setRgb(255,255,255);

        QListWidgetItem *item = ui->listWidget->item(i);
        if(item) {
            item->setBackgroundColor(colorBackgr);
            item->setTextColor(colorText);
        }
    }
    if(ui->listWidget->count()) ui->listWidget->setCurrentRow(0);
}

void DialogWordColors::on_pushButton_clicked()
{
    if(ui->listWidget->count()) {
        QString word = ui->listWidget->currentItem()->text();
        word = cList.getCodeByDefinition(word);
        QSharedPointer<ColorForWord> c = cList.getColor(word);
        if(c->getCodeWord()!=c->getDefaultName()) {
            QColor color = QColorDialog::getColor(QColor(c->getUserRed(),c->getUserGreen(),c->getUserBlue()),this);
            if(color.isValid()) {
                c->setUserRed(color.red());
                c->setUserGreen(color.green());
                c->setUserBlue(color.blue());

                QColor colorBackgr;
                ui->checkBox->setChecked(true);
                colorBackgr.setRgb(c->getUserRed(),c->getUserGreen(),c->getUserBlue());

                QColor colorText;
                if(c->getUserRed()>128) {colorText.setRgb(0,0,0);}
                else colorText.setRgb(255,255,255);

                QListWidgetItem *item = ui->listWidget->currentItem();
                if(item) {
                    item->setBackgroundColor(colorBackgr);
                    item->setTextColor(colorText);
                }
            }
        }
    }
}

void DialogWordColors::on_checkBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1)
    bool checked = ui->checkBox->isChecked();
    if(ui->listWidget->count()) {
        QString word = ui->listWidget->currentItem()->text();
        word = cList.getCodeByDefinition(word);
        QSharedPointer<ColorForWord> c = cList.getColor(word);
        if(c->getCodeWord()!=c->getDefaultName()) {
            if(checked) {
                ui->pushButton->setEnabled(true);
                c->setSystem(false);

                QColor colorBackgr;
                ui->checkBox->setChecked(true);
                colorBackgr.setRgb(c->getUserRed(),c->getUserGreen(),c->getUserBlue());

                QColor colorText;
                if(c->getUserRed()>128) {colorText.setRgb(0,0,0);}
                else colorText.setRgb(255,255,255);

                QListWidgetItem *item = ui->listWidget->currentItem();
                if(item) {
                    item->setBackgroundColor(colorBackgr);
                    item->setTextColor(colorText);
                }

            } else {
                ui->pushButton->setEnabled(false);
                c->setSystem(true);

                QColor colorBackgr;
                ui->checkBox->setChecked(false);
                colorBackgr.setRgb(c->getSysRed(),c->getSysGreen(),c->getSysBlue());

                QColor colorText;
                if(c->getUserRed()>128) {colorText.setRgb(0,0,0);}
                else colorText.setRgb(255,255,255);

                QListWidgetItem *item = ui->listWidget->currentItem();
                if(item) {
                    item->setBackgroundColor(colorBackgr);
                    item->setTextColor(colorText);
                }
            }
        }
    }
}

void DialogWordColors::on_listWidget_currentRowChanged(int currentRow)
{
    if(ui->listWidget->count()) {
        QListWidgetItem *item = ui->listWidget->item(currentRow);
        QString word = ui->listWidget->currentItem()->text();
        word = cList.getCodeByDefinition(word);
        QSharedPointer<ColorForWord> c = cList.getColor(word);
        if(c->getCodeWord()!=c->getDefaultName()) {
            QColor colorBackgr;
            if(c->isSystem()) {
                ui->checkBox->setChecked(false);
                colorBackgr.setRgb(c->getSysRed(),c->getSysGreen(),c->getSysBlue());
            }
            else {
                ui->checkBox->setChecked(true);
                colorBackgr.setRgb(c->getUserRed(),c->getUserGreen(),c->getUserBlue());
            }
            QColor colorText;
            if(c->getUserRed()>128) {colorText.setRgb(0,0,0);}
            else colorText.setRgb(255,255,255);

            if(item) {
                item->setBackgroundColor(colorBackgr);
                item->setTextColor(colorText);
            }
        }
    }
}
