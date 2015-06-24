#include "scangui.h"
#include "ui_scangui.h"
#include <QSerialPortInfo>

ScanGUI::ScanGUI(int progAddr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScanGUI)
{
    ui->setupUi(this);
    QStringList portNames;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            portNames << info.portName();
    }

    if(portNames.count()==0) {
        message.setStyleSheet("QLabel { font: bold; color : darkred; }");
        message.setText("COM порты не обнаружены");
    }else {
        foreach(QString pName, portNames) {
            ScanController* port = new ScanController(pName,progAddr);
            ports+= port;
            connect(port,SIGNAL(updated(float,QString)),this,SLOT(percentUpdate(float,QString)));
            connect(port,SIGNAL(found(DetectedController*,QString)),this,SLOT(plcHasBeenFound(DetectedController*,QString)));
            QProgressBar* bar = new QProgressBar();
            bar->setFormat(pName);bar->setValue(0);
            ui->verticalLayout->addWidget(bar);
            prBar+= bar;
        }
        message.setText("");
    }
    ui->verticalLayout->addWidget(&message);
}

ScanGUI::~ScanGUI()
{
    for(int i=0;i<ports.count();i++) {
        delete ports[i];
    }
    delete ui;
}

void ScanGUI::percentUpdate(float percValue, const QString &pName)
{
    bool finishFlag = true;
    foreach(QProgressBar* bar, prBar){
        if(bar->format()==pName) bar->setValue(percValue);
        if(bar->value()<99) finishFlag = false;
    }
    if(finishFlag) {
        message.setStyleSheet("QLabel { font: bold; color : darkred; }");
        message.setText("Контроллер не найден");
        DetectedController::Instance().setUartName("");
    }
}

void ScanGUI::plcHasBeenFound(DetectedController *plc, const QString &pName)
{
    QString plcMessage = pName;
    if(plc->getBootMode()) plcMessage += " BOOTLOADER";
    else {
        plcMessage += " " + QString::number(plc->getBaudrate());
        if(plc->getAsciiMode()) plcMessage += " ASCII"; else plcMessage += " BIN";
        plcMessage += " ADDRESS:" + QString::number(plc->getNetAddress());
    }
    message.setStyleSheet("QLabel { font: bold; color : darkgreen; }");
    message.setText(plcMessage);
    repaint();
    thread()->msleep(500);
    accept();
}
