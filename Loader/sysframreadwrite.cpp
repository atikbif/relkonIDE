#include "sysframreadwrite.h"
#include "ui_sysframreadwrite.h"

SysFramReadWrite::SysFramReadWrite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SysFramReadWrite)
{
    ui->setupUi(this);
    ui->label->setVisible(false);
    ui->progressBar->setValue(0);

    loader = new sFram();
    loader->moveToThread(&sFramThread);
    connect(&sFramThread,SIGNAL(finished()),loader,SLOT(deleteLater()));
    connect(loader,SIGNAL(percentUpdate(float)),this,SLOT(percentUpdate(float)));
    connect(loader,SIGNAL(writeFinished()),this,SLOT(writeFinished()));
    connect(loader,SIGNAL(readFinished(QByteArray)),this,SLOT(readFinished(QByteArray)));
    connect(loader,SIGNAL(error(QString)),this,SLOT(error(QString)));
    connect(this,SIGNAL(startWrite(QByteArray)),loader,SLOT(startWrite(QByteArray)));
    connect(this,SIGNAL(startRead()),loader,SLOT(startRead()));
    sFramThread.start();
}

SysFramReadWrite::~SysFramReadWrite()
{
    loader->stopProcess();
    sFramThread.quit();
    sFramThread.wait();
    delete ui;
}

void SysFramReadWrite::startWriteProcess(QByteArray data)
{
    emit startWrite(data);
}

void SysFramReadWrite::startReadProcess()
{
    emit startRead();
}

void SysFramReadWrite::writeFinished()
{
    accept();
}

void SysFramReadWrite::readFinished(QByteArray data)
{
    emit readOK(data);
    accept();
}

void SysFramReadWrite::error(QString message)
{
    ui->label->setVisible(true);
    ui->label->setText(message);
    repaint();
}

void SysFramReadWrite::percentUpdate(float value)
{
    ui->progressBar->setValue(value);
}
