#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AutoSearch/scangui.h"
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QFileDialog>
#include "Loader/bootmodesetter.h"
#include "Loader/ymodemthread.h"
#include "Loader/sysframreadwrite.h"
#include <QDataStream>
#include <QByteArray>


void MainWindow::createCOMPortList()
{
    ui->comboBoxComPorts->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBoxComPorts->addItem(info.portName());
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    progrPath("/"),sframPath("/"),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createCOMPortList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSearch_clicked()
{
    ScanGUI gui(ui->spinBoxNetAddr->value(),"",this);
    int ret = gui.exec();
    if(ret==QDialog::Accepted) {
        DetectedController* plc = &DetectedController::Instance();
        if(plc->getBootMode()) {
            QMessageBox::warning(this,"системные настройки контроллера","Контроллер ожидает загрузки программы.\n");
        }
        else {
            ui->comboBoxComPorts->setCurrentText(plc->getUartName());
            ui->lineEditSpeed->setText(QString::number(plc->getBaudrate()));
            QString protocol = "BIN";
            if(plc->getAsciiMode()) protocol = "ASCII";
            ui->lineEditProt->setText(protocol);
            ui->lineEditCan->setText(plc->getCanName());
            ui->spinBoxNetAddr->setValue(plc->getNetAddress());
        }
    }
}

void MainWindow::on_pushButtonUpd_clicked()
{
    createCOMPortList();
}

void MainWindow::on_pushButtonLoadProgr_clicked()
{
    QString fName = QFileDialog::getOpenFileName(this, tr("Загрузка кода программы"),
                                                    progrPath,
                                                    tr("(*.bin )"));
    if(!fName.isEmpty()) {
        QFile file(fName);
        progrPath = QFileInfo(file).absolutePath();
        ScanGUI gui(ui->spinBoxNetAddr->value(),ui->comboBoxComPorts->currentText(),this);
        int ret = gui.exec();
        if(ret==QDialog::Accepted) {
            BootModeSetter bootSetter(this);
            if(bootSetter.setBootMode()) {
                DetectedController* plc = &DetectedController::Instance();
                YmodemThread loader(plc->getUartName(),fName,this);
                loader.exec();
            }
        }
    }
}

void MainWindow::on_pushButtonLoadSFRAM_clicked()
{
    QString fName = QFileDialog::getOpenFileName(this, tr("Загрузка системных настроек"),
                                                    sframPath,
                                                    tr("(*.sfr )"));
    if(!fName.isEmpty()) {
        QFile file(fName);
        QByteArray data;
        if(file.open(QIODevice::ReadOnly)) {
            unsigned int codeWordValue;
            unsigned int versValue;
            QDataStream stream(&file);
            stream.setVersion(QDataStream::Qt_5_4);
            stream >> codeWordValue;
            stream >> versValue;
            if(codeWordValue == codeWord) {
                if(versValue == 0x01) {
                    unsigned char progAddr;
                    stream >> progAddr;
                    stream >> data;
                }
            }
            file.close();
        }

        sframPath = QFileInfo(file).absolutePath();
        ScanGUI gui(ui->spinBoxNetAddr->value(),ui->comboBoxComPorts->currentText(),this);
        int ret = gui.exec();
        if(ret==QDialog::Accepted) {
            DetectedController* plc = &DetectedController::Instance();
            if(plc->getBootMode()) QMessageBox::warning(this,"системные настройки контроллера","Контроллер ожидает загрузки программы.\nЧтение/запись настроек невозможны.");
            else{
                SysFramReadWrite loader(this);
                connect(this,SIGNAL(writeToPLC(QByteArray)),&loader,SLOT(startWriteProcess(QByteArray)));
                emit writeToPLC(data);
                loader.exec();
                disconnect(this,SIGNAL(writeToPLC(QByteArray)),&loader,SLOT(startWriteProcess(QByteArray)));
            }
        }
    }
}

void MainWindow::on_pushButtonReadProgr_clicked()
{
    ScanGUI gui(ui->spinBoxNetAddr->value(),ui->comboBoxComPorts->currentText(),this);
    int ret = gui.exec();
    if(ret==QDialog::Accepted) {
        DetectedController* plc = &DetectedController::Instance();
        if(plc->getBootMode()) QMessageBox::warning(this,"Чтение кода программы","Контроллер ожидает загрузки программы.\nЧтение невозможно.");
        else{

        }
    }
}

void MainWindow::on_pushButtonReadSFRAM_clicked()
{
    ScanGUI gui(ui->spinBoxNetAddr->value(),ui->comboBoxComPorts->currentText(),this);
    int ret = gui.exec();
    if(ret==QDialog::Accepted) {
        DetectedController* plc = &DetectedController::Instance();
        if(plc->getBootMode()) QMessageBox::warning(this,"системные настройки контроллера","Контроллер ожидает загрузки программы.\nЧтение/запись настроек невозможны.");
        else{
            SysFramReadWrite loader(this);
            connect(this,SIGNAL(readFromPLC()),&loader,SLOT(startReadProcess()));
            connect(&loader,SIGNAL(readOK(QByteArray)),this,SLOT(readFromBin(QByteArray)));
            emit readFromPLC();
            loader.exec();
        }
    }
}

void MainWindow::readFromBin(const QByteArray inpData)
{
    QString fName = QFileDialog::getSaveFileName(this, tr("Сохранение системных настроек"),
                                                    sframPath,
                                                    tr("(*.sfr )"));
    if(fName.isEmpty()) return;
    QFile* sFile = new QFile(fName);
    if(sFile->open(QIODevice::WriteOnly)) {
        unsigned int vers = 0x01;
        QDataStream stream(sFile);
        stream.setVersion(QDataStream::Qt_5_4);
        stream << codeWord;
        stream << vers;
        unsigned char progAddr = ui->spinBoxNetAddr->value();
        stream << progAddr;
        stream << inpData;
        sFile->close();
    }
    delete sFile;
}

