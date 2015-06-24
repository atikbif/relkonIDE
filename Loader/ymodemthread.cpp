#include "ymodemthread.h"
#include "ui_ymodemthread.h"
#include "RCompiler/rcompiler.h"
#include <QProgressBar>

YmodemThread::YmodemThread(const QString& pName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YmodemThread)
{
    ui->setupUi(this);
    bar = new QProgressBar();
    bar->setMaximum(100);
    bar->setMinimum(0);
    bar->setValue(0);
    label = new QLabel();
    ui->verticalLayout->addWidget(label);
    label->setVisible(false);
    ui->verticalLayout->addWidget(bar);

    loader = new Ymodem();
    loader->moveToThread(&bootThread);
    connect(&bootThread,SIGNAL(finished()),loader,SLOT(deleteLater()));
    connect(loader,SIGNAL(percentUpdate(float)),this,SLOT(percentUpdate(float)));
    connect(loader,SIGNAL(finished()),this,SLOT(finished()));
    connect(loader,SIGNAL(bootError(QString)),this,SLOT(bootError(QString)));
    connect(this,SIGNAL(startProcess(QString,QString)),loader,SLOT(startProcess(QString,QString)));
    bootThread.start();
    if(QFile::exists(RCompiler::getBinFileName())) {
        emit startProcess(pName,RCompiler::getBinFileName());
    }else {
        label->setVisible(true);
        label->setText("Ошибка открытия файла");
        repaint();
    }
}

YmodemThread::~YmodemThread()
{
    loader->stopProcess();
    bootThread.quit();
    bootThread.wait();
    delete ui;
}

void YmodemThread::finished()
{
    accept();
}

void YmodemThread::percentUpdate(float value)
{
    bar->setValue(value);
    repaint();
}

void YmodemThread::bootError(const QString &message)
{
    label->setVisible(true);
    label->setText(message);
}
