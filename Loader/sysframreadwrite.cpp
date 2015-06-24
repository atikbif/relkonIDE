#include "sysframreadwrite.h"
#include "ui_sysframreadwrite.h"

SysFramReadWrite::SysFramReadWrite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysFramReadWrite)
{
    ui->setupUi(this);
}

SysFramReadWrite::~SysFramReadWrite()
{
    delete ui;
}
