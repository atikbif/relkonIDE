#include "flashread.h"
#include "ui_flashread.h"

FlashRead::FlashRead(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlashRead)
{
    ui->setupUi(this);
}

FlashRead::~FlashRead()
{
    delete ui;
}
