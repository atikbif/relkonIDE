#include "dialogwritevar.h"
#include "ui_dialogwritevar.h"

DialogWriteVar::DialogWriteVar(QString startValue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWriteVar)
{
    ui->setupUi(this);
    ui->lineEdit->setText(startValue);
    ui->lineEdit->selectAll();
}

QString DialogWriteVar::getResult()
{
    return ui->lineEdit->text();
}

bool DialogWriteVar::checkResult()
{
    bool longRes = false;
    bool doubleRes = false;
    long long lValue = getResult().toLongLong(&longRes);
    double dValue = getResult().toDouble(&doubleRes);
    // проверка корректности введённого текста
    if(longRes==true) {
        if(var.getDataType()==VarItem::charType) {
            qint8 res = (qint8)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()==VarItem::ucharType) {
            if(lValue<0) return false;
            quint8 res = (qint8)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()==VarItem::shortType) {
            qint16 res = (qint16)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()==VarItem::ushortType) {
            if(lValue<0) return false;
            quint16 res = (qint16)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()==VarItem::intType) {
            qint32 res = (qint32)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()==VarItem::uintType) {
            if(lValue<0) return false;
            quint32 res = (qint32)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()==VarItem::longType) {
            qint32 res = (qint32)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()==VarItem::ulongType) {
            if(lValue<0) return false;
            quint32 res = (qint32)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()==VarItem::longLongType) {
            return true;
        }
    }
    if(doubleRes==true) {
        if(var.getDataType()==VarItem::floatType) {
            float res = (float)dValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        return true;
    }
    return false;
}

DialogWriteVar::~DialogWriteVar()
{
    delete ui;
}
