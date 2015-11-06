#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QDateTime>
#include <QPalette>
#include <QSerialPort>
#include <QByteArray>

void MainWindow::listUpdate(int modAddr)
{
    if(!testAddress(modAddr)) return;

    ui->comboBoxMod->setEnabled(true);
    ui->pushButtonWrite->setEnabled(true);

    ui->comboBoxMod->clear();
    if((modAddr>=1)&&(modAddr<65)) {
        for(int i=0;i<64;i++) {
            ui->comboBoxMod->addItem("IN"+QString::number(i+4));
        }
        ui->comboBoxCom->setCurrentText("IN"+QString::number(modAddr-1+4));
    }else if((modAddr>=65)&&(modAddr<129)) {
        for(int i=0;i<64;i++) {
            ui->comboBoxMod->addItem("OUT"+QString::number(i+4));
        }
        ui->comboBoxMod->setCurrentText("OUT" + QString::number(modAddr-65+4));
    }else if((modAddr>=129)&&(modAddr<161)) {
        for(int i=0;i<64;i++) {
            ui->comboBoxMod->addItem("ADC"+QString::number(9+i*4)+"..ADC"+QString::number(12+i*4));
        }
        ui->comboBoxMod->setCurrentText("ADC"+QString::number(9+(modAddr-129)*4)+"..ADC"+QString::number(12+(modAddr-129)*4));
    }else if((modAddr>=161)&&(modAddr<224)) {
        for(int i=0;i<64;i++) {
            ui->comboBoxMod->addItem("DAC"+QString::number(5+i*2)+"-DAC"+QString::number(6+i*2));
        }
        ui->comboBoxMod->setCurrentText("DAC"+QString::number(5+(modAddr-161)*2)+"-DAC"+QString::number(6+(modAddr-161)*2));
    }else {
        ui->statusBar->showMessage("Неизвестный модуль",3000);
        ui->comboBoxMod->setEnabled(false);
        ui->pushButtonWrite->setEnabled(false);
    }
}

bool MainWindow::testAddress(int addr) const
{
    const int minAddr = 1;
    const int maxAddr = 224;
    if((addr<minAddr)||(addr>maxAddr)) return false;
    return true;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),modAddr(-1),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_pushButtonComUpd_clicked();

    QPalette palette;
    palette.setColor( QPalette::WindowText, Qt::darkRed );
    ui->statusBar->setPalette( palette );
    ui->pushButtonWrite->setEnabled(false);
    ui->comboBoxMod->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonComUpd_clicked()
{
    ui->comboBoxCom->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBoxCom->addItem(info.portName());
    }
    ui->statusBar->showMessage("список портов обновлён",3000);
}

void MainWindow::on_pushButtonSearch_clicked()
{
    ui->comboBoxMod->setEnabled(false);
    ui->pushButtonWrite->setEnabled(false);
    QSerialPort *port = new QSerialPort(ui->comboBoxCom->currentText());
    port->setBaudRate(QSerialPort::Baud115200);
    port->setStopBits(QSerialPort::TwoStop);
    if(port->open(QSerialPort::ReadWrite)) {
        QByteArray txBuf;
        txBuf.append('\0');txBuf.append('\0');txBuf.append('\0');
        txBuf.append(0xFF);txBuf.append(0xFF);txBuf.append(0xFF);
        txBuf.append(0x55);txBuf.append(0x55);txBuf.append(0x55);
        txBuf.append(0xAA);txBuf.append(0xAA);txBuf.append(0xAA);
        port->readAll();
        port->write(txBuf);
        port->waitForBytesWritten(150);
        port->waitForReadyRead(100);
        QByteArray answer;
        answer = port->readAll();
        while(port->waitForReadyRead(20)) {
            answer+=port->readAll();
        }
        if(answer.count()) {
            bool checkAnswer = false;
            if(answer.count()==2) {
                if(answer.at(0)==answer.at(1)) {
                    checkAnswer = true;
                    modAddr = (unsigned char)answer.at(0);
                    if(testAddress(modAddr)) listUpdate(modAddr);
                    else ui->statusBar->showMessage("Неизвестный модуль",3000);
                }
            }
            if(checkAnswer) ui->statusBar->showMessage("Модуль обнаружен",3000);
            else ui->statusBar->showMessage("Некорректный ответ",3000);
        }else ui->statusBar->showMessage("Нет ответа",3000);
        port->close();
    }else ui->statusBar->showMessage("Ошибка открытия порта",3000);
}

void MainWindow::on_pushButtonWrite_clicked()
{
    QString modName = ui->comboBoxMod->currentText();
    int addr = -1;
    QRegExp inExp("^IN(\\d+)");
    QRegExp outExp("^OUT(\\d+)");
    QRegExp adcExp("^ADC(\\d+)");
    QRegExp dacExp("^DAC(\\d+)");
    if(inExp.indexIn(modName)!=-1) {
        int num = inExp.cap(1).toInt();
        addr = num-3;
    }else if(outExp.indexIn(modName)!=-1) {
        int num = outExp.cap(1).toInt();
        addr = num+61;
    }else if(adcExp.indexIn(modName)!=-1) {
        int num = adcExp.cap(1).toInt();
        addr = (num-9)/4+129;
    }else if(dacExp.indexIn(modName)!=-1) {
        int num = dacExp.cap(1).toInt();
        addr = (num-5)/2+161;
    }else {
        ui->statusBar->showMessage("Невозможно выполнить команду",3000);
        return;
    }
    if(testAddress(addr)) {
        QSerialPort *port = new QSerialPort(ui->comboBoxCom->currentText());
        port->setBaudRate(QSerialPort::Baud115200);
        port->setStopBits(QSerialPort::TwoStop);
        if(port->open(QSerialPort::ReadWrite)) {
            QByteArray txBuf;
            txBuf.append('\0');
            txBuf.append(0xE1);
            txBuf.append(modAddr);
            txBuf.append(addr);
            port->readAll();
            port->write(txBuf);
            port->waitForBytesWritten(150);
            port->waitForReadyRead(100);
            QByteArray answer;
            answer = port->readAll();
            while(port->waitForReadyRead(20)) {
                answer+=port->readAll();
            }
            bool checkAnswer = false;
            if(answer.count()==2) {
                if(answer.at(0)==answer.at(1)) {
                    if((unsigned char)answer.at(0)==addr) checkAnswer = true;
                }
            }else checkAnswer=false;
            if(checkAnswer) {
                ui->statusBar->showMessage("Запись выполнена успешно",3000);
            }else {
                ui->statusBar->showMessage("Ошибка записи",3000);
                ui->comboBoxMod->setEnabled(false);
                ui->pushButtonWrite->setEnabled(false);
            }
            port->close();
        }
    }else ui->statusBar->showMessage("Невозможно выполнить команду",3000);
}
