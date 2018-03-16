#include "dialoggotostring.h"
#include "ui_dialoggotostring.h"

DialogGoToString::DialogGoToString(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGoToString)
{
    ui->setupUi(this);
    ui->spinBoxStrNum->setFocus();
}

DialogGoToString::~DialogGoToString()
{
    delete ui;
}

void DialogGoToString::on_spinBoxStrNum_valueChanged(int arg1)
{
    strNum = arg1;
}
