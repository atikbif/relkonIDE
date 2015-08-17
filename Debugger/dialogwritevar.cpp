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
        if(var.getDataType()=="char") {
            qint8 res = (qint8)longRes;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()=="unsigned char") {
            if(lValue<0) return false;
            quint8 res = (qint8)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()=="short") {
            qint16 res = (qint16)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()=="unsigned short") {
            if(lValue<0) return false;
            quint16 res = (qint16)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()=="int") {
            qint32 res = (qint32)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()=="unsigned int") {
            if(lValue<0) return false;
            quint32 res = (qint32)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()=="long") {
            qint32 res = (qint32)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()=="unsigned long") {
            if(lValue<0) return false;
            quint32 res = (qint32)lValue;
            ui->lineEdit->setText(QString::number(res));
            return true;
        }
        if(var.getDataType()=="long long") {
            return true;
        }
    }
    if(doubleRes==true) {
        if(var.getDataType()=="float") {
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
