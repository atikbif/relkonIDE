#include "flashread.h"
#include "ui_flashread.h"

FlashRead::FlashRead(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlashRead)
{
    ui->setupUi(this);
    ui->label->setVisible(false);
    ui->progressBar->setValue(0);

    loader = new Flash();
    loader->moveToThread(&flashThread);
    connect(&flashThread,SIGNAL(finished()),loader,SLOT(deleteLater()));
    connect(loader,SIGNAL(percentUpdate(float)),this,SLOT(percentUpdate(float)));
    connect(loader,SIGNAL(readFinished(QByteArray)),this,SLOT(readFinished(QByteArray)));
    connect(loader,SIGNAL(error(QString)),this,SLOT(error(QString)));
    connect(this,SIGNAL(startRead()),loader,SLOT(startRead()));
    flashThread.start();
}

FlashRead::~FlashRead()
{
    loader->stopProcess();
    flashThread.quit();
    flashThread.wait();
    delete ui;
}

void FlashRead::startReadProcess() {
    emit startRead();
}

void FlashRead::error(QString message) {
    ui->label->setVisible(true);
    ui->label->setText(message);
    repaint();
}

void FlashRead::percentUpdate(float value) {
    ui->progressBar->setValue(value);
}

void FlashRead::readFinished(QByteArray data)
{
    emit readOK(data);
    accept();
}
