#include "settingsform.h"
#include "ui_settingsform.h"
#include <QRegExp>
#include <QDateTime>
#include <QFile>
#include <QDataStream>
#include "AutoSearch/scangui.h"
#include "AutoSearch/detectedcontroller.h"
#include <QMessageBox>
#include "Loader/sysframreadwrite.h"
#include "RCompiler/rcompiler.h"
#include "pathstorage.h"
#include <QSerialPortInfo>
#include <QFileDialog>

void SettingsForm::printFactorySettings()
{
    unsigned char amountOfByte=1;
    if(ui->radioButtonOneByte->isChecked()) amountOfByte=1;
    if(ui->radioButtonTwoBytes->isChecked()) amountOfByte=2;
    if(ui->radioButtonFourBytes->isChecked()) amountOfByte=4;
    int num=0;
    for(int i=0;i<rowCount;i++) {
        for(int j=0;j<columnCount;j++) {
            if((num%amountOfByte==0)&&(num<factorySettingsAmount)) {
                unsigned long value = fSettings[num];
                if((amountOfByte>=2)&&(num+1<factorySettingsAmount)) {
                    value |= (unsigned long)fSettings[num+1] << 8;
                }
                if((amountOfByte>=4)&&(num+3<factorySettingsAmount)) {
                    value |= (unsigned long)fSettings[num+2] << 16;
                    value |= (unsigned long)fSettings[num+3] << 24;
                    //value = value + (unsigned long)fSettings[num+2]*256;
                    //value = value + (unsigned long)fSettings[num+3]*256;
                }
                ui->tableWidget->item(i,j)->setBackground(QColor(251,251,251));
                ui->tableWidget->item(i,j)->setToolTip(QString::number(num));
                ui->tableWidget->item(i,j)->setText(QString::number(value));
                ui->tableWidget->item(i,j)->setTextColor(Qt::black);
            }else {
                ui->tableWidget->item(i,j)->setBackground(Qt::gray);
                ui->tableWidget->item(i,j)->setToolTip("");
                ui->tableWidget->item(i,j)->setText("");
                ui->tableWidget->item(i,j)->setTextColor(Qt::gray);
            }
            num++;
        }
    }
}

void SettingsForm::guiToData()
{
    netAddress = ui->spinBoxNetAddr->value();
    progAddr = ui->spinBoxProgAddr->value();
    QStringList ipList = ui->lineEditIP->text().remove('_').split('.');
    if(ipList.count()>=4) {
        ipAddr[0]=ipList.at(0).toInt();
        ipAddr[1]=ipList.at(1).toInt();
        ipAddr[2]=ipList.at(2).toInt();
        ipAddr[3]=ipList.at(3).toInt();
    }
    QStringList macList = ui->lineEditMAC->text().remove('_').split(':');
    if(macList.count()>=6) {
        bool res;
        macAddr[0]=macList.at(0).toInt(&res,16);
        macAddr[1]=macList.at(1).toInt(&res,16);
        macAddr[2]=macList.at(2).toInt(&res,16);
        macAddr[3]=macList.at(3).toInt(&res,16);
        macAddr[4]=macList.at(4).toInt(&res,16);
        macAddr[5]=macList.at(5).toInt(&res,16);
    }
    QStringList gateList = ui->lineEditGATE->text().remove('_').split('.');
    if(gateList.count()>=4) {
        ipGate[0]=gateList.at(0).toInt();
        ipGate[1]=gateList.at(1).toInt();
        ipGate[2]=gateList.at(2).toInt();
        ipGate[3]=gateList.at(3).toInt();
    }
    QStringList maskList = ui->lineEditMASK->text().remove('_').split('.');
    if(maskList.count()>=4) {
        ipMask[0]=maskList.at(0).toInt();
        ipMask[1]=maskList.at(1).toInt();
        ipMask[2]=maskList.at(2).toInt();
        ipMask[3]=maskList.at(3).toInt();
    }
    prDef = ui->lineEditProjectDefenition->text();
    int speedValue = ui->comboBoxProgSpeed->currentText().toInt();
    protocolType protocol = BIN;
    switch(ui->comboBoxProgProtocol->currentIndex()) {
        case 0:protocol=BIN;break;
        case 1:protocol=ASCII;break;
    }
    prUart.protocol=protocol;
    prUart.speed=speedValue;

    speedValue = ui->comboBoxPcSpeed->currentText().toInt();
    protocol = BIN;
    switch(ui->comboBoxPcProtocol->currentIndex()) {
        case 0:protocol=BIN;break;
        case 1:protocol=ASCII;break;
    }
    pcUart.protocol=protocol;
    pcUart.speed=speedValue;

    if(ui->radioButtonNoEmulation->isChecked()) emulation = NoEmulation;
    if(ui->radioButtonInputEmulation->isChecked()) emulation = InputEmulation;
    if(ui->radioButtonInputOutputEmulation->isChecked()) emulation = InputOutputEmulation;

    if(ui->checkBoxDisplay->isChecked()) displayOn=true;else displayOn=false;
    if(ui->checkBoxSD->isChecked()) sdOn=true;else sdOn=false;
    setPLCType(ui->comboBoxPLCType->currentText());
    if(ui->checkBoxModbus->isChecked()) modbMasterEmuMode = true; else modbMasterEmuMode = false;
}

void SettingsForm::updateData()
{
    ui->spinBoxNetAddr->setValue(netAddress);
    ui->spinBoxProgAddr->setValue(progAddr);

    QString ipStr;
    for(int i=0;i<4;i++) {
        QString num = QString::number(ipAddr[i]);
        while(num.size()<3) num = "0"+num;
        ipStr+=num;
        if(i!=3) ipStr+=".";
    }
    ui->lineEditIP->setText(ipStr);

    QString macStr;
    for(int i=0;i<6;i++) {
        QString num = QString::number(macAddr[i],16);
        while(num.size()<2) num = "0" + num;
        macStr+=num;
        if(i!=5) macStr+=":";
    }
    ui->lineEditMAC->setText(macStr);

    QString gateStr;
    for(int i=0;i<4;i++) {
        QString num = QString::number(ipGate[i]);
        while(num.size()<3) num = "0"+num;
        gateStr+=num;
        if(i!=3) gateStr+=".";
    }
    ui->lineEditGATE->setText(gateStr);

    QString maskStr;
    for(int i=0;i<4;i++) {
        QString num = QString::number(ipMask[i]);
        while(num.size()<3) num = "0"+num;
        maskStr+=num;
        if(i!=3) maskStr+=".";
    }
    ui->lineEditMASK->setText(maskStr);

    ui->lineEditProjectDefenition->setText(prDef);

    ui->comboBoxProgProtocol->setCurrentIndex(prUart.protocol);
    ui->comboBoxProgSpeed->setCurrentText(QString::number(prUart.speed));
    ui->comboBoxPcProtocol->setCurrentIndex(pcUart.protocol);
    ui->comboBoxPcSpeed->setCurrentText(QString::number(pcUart.speed));

    if(emulation==NoEmulation) {ui->radioButtonNoEmulation->setChecked(true);emit emuModeChanged(NoEmulation);}
    if(emulation==InputEmulation) {ui->radioButtonInputEmulation->setChecked(true);emit emuModeChanged(InputEmulation);}
    if(emulation==InputOutputEmulation) {ui->radioButtonInputOutputEmulation->setChecked(true);emit emuModeChanged(InputOutputEmulation);}

    if(displayOn) ui->checkBoxDisplay->setChecked(true);
    else ui->checkBoxDisplay->setChecked(false);
    if(sdOn) ui->checkBoxSD->setChecked(true);
    else ui->checkBoxSD->setChecked(false);
    ui->comboBoxPLCType->setCurrentText(getPLCType());

    ui->checkBoxModbus->setChecked(modbusMaster);
    ui->spinBoxEMemSize->setValue(eMemSize);
    ui->checkBoxModbus->setChecked(modbMasterEmuMode);

    printFactorySettings();
}

void SettingsForm::writeToBin(QByteArray &outData)
{
    guiToData();
    outData.fill(0,settingsSize);
    for(int i=0;i<1024;i++) {
        if(i<factorySettingsAmount) outData[i]=fSettings[i];
    }
    outData[1024]=netAddress;
    int speedValue=0;
    int protocol=0;
    switch(pcUart.protocol) {
        case BIN:protocol=0;break;
        case ASCII:protocol=1;break;
    }
    switch(pcUart.speed) {
        case 4800: speedValue=0;break;
        case 9600: speedValue=1;break;
        case 19200:speedValue=2;break;
        case 38400:speedValue=3;break;
        case 57600:speedValue=4;break;
        case 115200:speedValue=5;break;
    }
    outData[1025]=speedValue;
    outData[1026]=protocol;

    switch(prUart.protocol) {
        case BIN:protocol=0;break;
        case ASCII:protocol=1;break;
    }
    switch(prUart.speed) {
        case 4800: speedValue=0;break;
        case 9600: speedValue=1;break;
        case 19200:speedValue=2;break;
        case 38400:speedValue=3;break;
        case 57600:speedValue=4;break;
        case 115200:speedValue=5;break;
    }
    outData[1027]=speedValue;
    outData[1028]=protocol;

    int emulationCode=0;
    switch(emulation) {
        case NoEmulation:emulationCode=0;break;
        case InputEmulation:emulationCode=1;break;
        case InputOutputEmulation:emulationCode=2;break;
    }
    outData[1029]=emulationCode;

    QByteArray prDefBin = prDef.toUtf8();
    prDefBin.resize(64);
    for(int i=0;i<64;i++) outData[1036+i] = prDefBin.at(i);

    outData[1100]=ipAddr[0];
    outData[1101]=ipAddr[1];
    outData[1102]=ipAddr[2];
    outData[1103]=ipAddr[3];

    outData[1104]=macAddr[0];
    outData[1105]=macAddr[1];
    outData[1106]=macAddr[2];
    outData[1107]=macAddr[3];
    outData[1108]=macAddr[4];
    outData[1109]=macAddr[5];

    int curYear = QDate::currentDate().year()%100;
    outData[1110]=curYear;

    if(displayOn) outData[1111]='\0';
    else outData[1111]=0x31;

    if(sdOn) outData[1113]=0x31;
    else outData[1113]='\0';

    outData[1114]=ipGate[0];
    outData[1115]=ipGate[1];
    outData[1116]=ipGate[2];
    outData[1117]=ipGate[3];

    outData[1118] = modbMasterEmuMode;

    outData[1119]=ipMask[0];
    outData[1120]=ipMask[1];
    outData[1121]=ipMask[2];
    outData[1122]=ipMask[3];

    outData.replace(1269,10,"Relkon 7.0");
}

SettingsForm::SettingsForm(SettingsBase *parent) :
    SettingsBase(parent),
    ui(new Ui::SettingsForm)
{

    ui->setupUi(this);
    ui->tableWidget->setColumnCount(columnCount);
    QStringList columnNames;
    for(int i=0;i<ui->tableWidget->columnCount();i++) {
        columnNames << QString::number(i);
    }
    ui->tableWidget->setHorizontalHeaderLabels(columnNames);
    ui->tableWidget->setRowCount(rowCount);
    QStringList rowNames;
    for(int i=0;i<rowCount;i++) {
        rowNames << QString::number(i*10);
    }
    ui->tableWidget->setVerticalHeaderLabels(rowNames);

    for(int i=0;i<columnCount;i++) {
        for(int j=0;j<rowCount;j++) {
            QTableWidgetItem *newItem = new QTableWidgetItem("8888888888");
            ui->tableWidget->setItem(j, i, newItem);
            newItem->setBackgroundColor(QColor(251,251,251));
            newItem->setTextAlignment(Qt::AlignCenter);
            newItem->setToolTip(QString::number(i+j*10));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
    for(int i=0;i<columnCount;i++) {
        for(int j=0;j<rowCount;j++) {
            if(j*10+i<factorySettingsAmount) ui->tableWidget->item(j, i)->setText("0");
            else {
                ui->tableWidget->item(j,i)->setText("");
                ui->tableWidget->item(j,i)->setTextColor(QColor(251,251,251));
            }
        }
    }
    QStringList plcNames = getPLCNames();
    plcNames.sort();

    foreach (QString plcName, plcNames) {
        ui->comboBoxPLCType->addItem(plcName);
    }
    ui->comboBoxPLCType->setCurrentText(getPLCType());
    ui->spinBoxEMemSize->setValue(eMemSize);

    on_pushButtonPortListUpdate_clicked();

    connect(ui->radioButtonOneByte,SIGNAL(toggled(bool)),this,SLOT(radioButtonBytes_toggled()));
    connect(ui->radioButtonTwoBytes,SIGNAL(toggled(bool)),this,SLOT(radioButtonBytes_toggled()));
    connect(ui->radioButtonFourBytes,SIGNAL(toggled(bool)),this,SLOT(radioButtonBytes_toggled()));

    emit newPLCType(ui->comboBoxPLCType->currentText());

    updateData();
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::clearSettings()
{
    SettingsBase::clearSettings();
    ui->comboBoxPrPort->setCurrentText("AUTO");
    updateData();
    ui->radioButtonOneByte->setChecked(true);
}

void SettingsForm::saveSettings()
{
    QByteArray data;
    writeToBin(data);
    QString fName = PathStorage::getKonFileFullName();
    if(fName.isEmpty()) return;
    fName.remove(QRegExp("\\.kon"));
    fName += ".sfr";
    QFile* sFile = new QFile(fName);
    if(sFile->open(QIODevice::WriteOnly)) {
        unsigned int vers = 0x04;
        QDataStream stream(sFile);
        stream.setVersion(QDataStream::Qt_5_4);
        stream << codeWord;
        stream << vers;
        stream << progAddr;
        stream << data;
        stream << getPLCType();
        stream << getPortName();
        stream << ui->checkBoxModbus->isChecked();
        stream << ui->spinBoxEMemSize->value();
        sFile->close();
    }
    delete sFile;
}

void SettingsForm::openSettings()
{
    QByteArray data;
    QString fName = PathStorage::getKonFileFullName();
    QString plc;
    QString port;
    if(fName.isEmpty()) return;
    fName.remove(QRegExp("\\.kon"));
    fName += ".sfr";
    QFile file(fName);
    if(file.open(QIODevice::ReadOnly)) {
        unsigned int codeWordValue;
        unsigned int versValue;
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_4);
        stream >> codeWordValue;
        stream >> versValue;
        if(codeWordValue == codeWord) {
            if(versValue == 0x01) {
                stream >> progAddr;
                stream >> data;
                stream >> plc;
                setPLCType(plc);
                eMemSize = 10;
                //ui->comboBoxPrPort->setCurrentText(port);
                if(stream.status()==QDataStream::Ok) {
                    readFromBin(data);
                    updateData();
                }
            }else if(versValue == 0x02) {
                stream >> progAddr;
                stream >> data;
                stream >> plc;
                stream >> port;
                setPLCType(plc);
                ui->comboBoxPrPort->setCurrentText(port);
                eMemSize = 10;
                if(stream.status()==QDataStream::Ok) {
                    readFromBin(data);
                    updateData();
                }
            }else if(versValue == 0x03) {
                stream >> progAddr;
                stream >> data;
                stream >> plc;
                stream >> port;
                stream >> modbusMaster;
                setPLCType(plc);
                ui->comboBoxPrPort->setCurrentText(port);
                eMemSize = 10;
                if(stream.status()==QDataStream::Ok) {
                    readFromBin(data);
                    updateData();
                }
            }else if(versValue == 0x04) {
                stream >> progAddr;
                stream >> data;
                stream >> plc;
                stream >> port;
                stream >> modbusMaster;
                stream >> eMemSize;
                setPLCType(plc);
                ui->comboBoxPrPort->setCurrentText(port);
                if(stream.status()==QDataStream::Ok) {
                    readFromBin(data);
                    updateData();
                }
            }
        }
        file.close();
        ui->radioButtonOneByte->setChecked(true);
        updateData();
    }
}

void SettingsForm::updateTable()
{
    printFactorySettings();
}

void SettingsForm::setEmuMode(SettingsBase::emuType value)
{
    if(value==emuType::NoEmulation) {
        ui->radioButtonNoEmulation->setChecked(true);
        emit emuModeChanged(NoEmulation);
    }else if(value==emuType::InputEmulation) {
        ui->radioButtonInputEmulation->setChecked(true);
        emit emuModeChanged(InputEmulation);
    }else if(value==emuType::InputOutputEmulation) {
        ui->radioButtonInputOutputEmulation->setChecked(true);
        emit emuModeChanged(InputOutputEmulation);
    }
}

QString SettingsForm::getPortName() const
{
    return ui->comboBoxPrPort->currentText();
}

void SettingsForm::readFromBin(const QByteArray inpData)
{
    if(inpData.count()>=settingsSize) {
        for(int i=0;i<1024;i++) {
            if(i<factorySettingsAmount) fSettings[i] = inpData.at(i);
        }
        netAddress = inpData.at(1024);
        int speedValue = inpData.at(1025);
        switch(speedValue)
        {
            case 0:pcUart.speed = 4800;break;
            case 1:pcUart.speed = 9600;break;
            case 2:pcUart.speed = 19200;break;
            case 3:pcUart.speed = 38400;break;
            case 4:pcUart.speed = 57600;break;
            case 5:pcUart.speed = 115200;break;
            default:pcUart.speed = 115200;break;
        }
        int protocol=inpData.at(1026);
        switch(protocol)
        {
            case 0:pcUart.protocol = BIN;break;
            case 1:pcUart.protocol = ASCII;break;
            default:pcUart.protocol = BIN;break;
        }
        speedValue = inpData.at(1027);
        switch(speedValue)
        {
            case 0:prUart.speed = 4800;break;
            case 1:prUart.speed = 9600;break;
            case 2:prUart.speed = 19200;break;
            case 3:prUart.speed = 38400;break;
            case 4:prUart.speed = 57600;break;
            case 5:prUart.speed = 115200;break;
            default:prUart.speed = 115200;break;
        }
        protocol=inpData.at(1028);
        switch(protocol)
        {
            case 0:prUart.protocol = BIN;break;
            case 1:prUart.protocol = ASCII;break;
            default:prUart.protocol = BIN;break;
        }
        int emulationcode = inpData.at(1029);
        switch(emulationcode) {
            case 0:emulation = NoEmulation;break;
            case 1:emulation = InputEmulation;break;
            case 2:emulation = InputOutputEmulation;break;
            default:emulation = NoEmulation;break;
        }

        ipAddr[0] = inpData.at(1100);
        ipAddr[1] = inpData.at(1101);
        ipAddr[2] = inpData.at(1102);
        ipAddr[3] = inpData.at(1103);

        macAddr[0] = inpData.at(1104);
        macAddr[1] = inpData.at(1105);
        macAddr[2] = inpData.at(1106);
        macAddr[3] = inpData.at(1107);
        macAddr[4] = inpData.at(1108);
        macAddr[5] = inpData.at(1109);

        ipGate[0] = inpData.at(1114);
        ipGate[1] = inpData.at(1115);
        ipGate[2] = inpData.at(1116);
        ipGate[3] = inpData.at(1117);

        if((ipGate[0]==0)&&(ipGate[1]==0)&&(ipGate[2]==0)&&(ipGate[3]==0)) {
            if((ipAddr[0])||(ipAddr[1])||(ipAddr[2])||(ipAddr[3])) {
                ipGate[0] = ipAddr[0];
                ipGate[1] = ipAddr[1];
                ipGate[2] = ipAddr[2];
                ipGate[3] = 1;
            }
        }

        if(inpData.at(1118)) modbMasterEmuMode=true;else modbMasterEmuMode=false;

        ipMask[0] = inpData.at(1119);
        ipMask[1] = inpData.at(1120);
        ipMask[2] = inpData.at(1121);
        ipMask[3] = inpData.at(1122);

        if((ipMask[0]==0)&&(ipMask[1]==0)&&(ipMask[2]==0)&&(ipMask[3]==0)) {
            if((ipAddr[0])||(ipAddr[1])||(ipAddr[2])||(ipAddr[3])) {
                ipMask[0] = 255;
                ipMask[1] = 255;
                ipMask[2] = 255;
                ipMask[3] = 0;
            }
        }

        if(inpData.at(1111)==0x31) displayOn=false;
        else displayOn=true;

        if(inpData.at(1113)==0x31) sdOn=true;
        else sdOn=false;

        QByteArray prDefBin;
        for(int i=0;i<64;i++) prDefBin.append(inpData[1036+i]);
        prDef = QString::fromUtf8(prDefBin);

        updateData();
    }
}

void SettingsForm::readUserFromBin(const QByteArray inpData)
{
    QString  konFileName = PathStorage::getKonFileFullName();
    QString path = QFileInfo(konFileName).absoluteDir().absolutePath();
    QString fName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"),path,tr("FRAM (*.ufr)"));
    if(!fName.isEmpty()) {
        QFile file(fName);
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);
            stream.setVersion(QDataStream::Qt_5_4);
            stream << inpData;
            file.close();
        }else QMessageBox::warning(this,"Предупреждение","Не удалось сохранить файл");
    }
}

void SettingsForm::writeSysFram()
{
    on_pushButtonToPLC_clicked();
}

void SettingsForm::readSysFram()
{
    on_pushButtonFromPLC_clicked();
}

void SettingsForm::readUserFram()
{
    ScanGUI gui(progAddr,false,getPortName(),this);
    int ret = gui.exec();
    if(ret==QDialog::Accepted) {
        DetectedController* plc = &DetectedController::Instance();
        if(plc->getBootMode()) QMessageBox::warning(this,"системные настройки контроллера","Контроллер ожидает загрузки программы.\nЧтение/запись настроек невозможны.");
        else{
            SysFramReadWrite loader(true,this);
            connect(this,SIGNAL(readFromPLC()),&loader,SLOT(startReadProcess()));
            connect(&loader,SIGNAL(readOK(QByteArray)),this,SLOT(readUserFromBin(QByteArray)));
            emit readFromPLC();
            loader.exec();
            disconnect(this,SIGNAL(writeToPLC(QByteArray)),&loader,SLOT(startWriteProcess(QByteArray)));
        }
    }
}

void SettingsForm::writeUserFram()
{

    QString  konFileName = PathStorage::getKonFileFullName();
    QString path = QFileInfo(konFileName).absoluteDir().absolutePath();
    QString fName = QFileDialog::getOpenFileName(this, tr("Загрузить файл"),path,tr("FRAM (*.ufr)"));
    if(!fName.isEmpty()) {
        QFile file(fName);
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&file);
            stream.setVersion(QDataStream::Qt_5_4);
            QByteArray inpData;
            stream >> inpData;
            file.close();

            ScanGUI gui(progAddr,false,getPortName(),this);
            int ret = gui.exec();
            if(ret==QDialog::Accepted) {
                DetectedController* plc = &DetectedController::Instance();
                if(plc->getBootMode()) QMessageBox::warning(this,"системные настройки контроллера","Контроллер ожидает загрузки программы.\nЧтение/запись настроек невозможны.");
                else{
                    SysFramReadWrite loader(true,this);
                    connect(this,SIGNAL(writeToPLC(QByteArray)),&loader,SLOT(startWriteProcess(QByteArray)));
                    emit writeToPLC(inpData);
                    loader.exec();
                    disconnect(this,SIGNAL(writeToPLC(QByteArray)),&loader,SLOT(startWriteProcess(QByteArray)));
                }
            }

        }else QMessageBox::warning(this,"Предупреждение","Не удалось открыть файл");
    }
}

void SettingsForm::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(item->backgroundColor()==Qt::gray) item->setText("-");
    else {
        QString itemText = item->text();
        itemText.remove(QRegExp("[^\\d]"));
        if(itemText.isEmpty()) itemText="0";
        bool numFl=false;
        int num = item->toolTip().toInt(&numFl);
        if(num>=factorySettingsAmount) numFl=false;
        if(numFl==true) {
            unsigned long value = itemText.toULong(&numFl);
            if(numFl) {
                if(ui->radioButtonOneByte->isChecked()) {
                    if(value>0xFF) value=0;
                    fSettings[num]=(unsigned char)value;
                }else if(ui->radioButtonTwoBytes->isChecked()) {
                    if(value>0xFFFF) value=0;
                    if(num+1<factorySettingsAmount) {
                        fSettings[num+1] = (value >> 8) & 0xFF;
                        fSettings[num] = value & 0xFF;
                    }
                }else if(ui->radioButtonFourBytes->isChecked()) {
                    if(value>0xFFFFFFFF) value=0;
                    if(num+3<factorySettingsAmount) {
                        fSettings[num+3] = (value>>24)&0xFF;
                        fSettings[num+2] = (value>>16)&0xFF;
                        fSettings[num+1] = (value>>8)&0xFF;
                        fSettings[num] = value & 0xFF;
                    }
                }
                item->setText(QString::number(value));
            }
        }
    }
}

void SettingsForm::radioButtonBytes_toggled()
{
    printFactorySettings();
}

void SettingsForm::on_pushButtonFromPLC_clicked()
{
    ScanGUI gui(progAddr,false,getPortName(),this);
    int ret = gui.exec();
    if(ret==QDialog::Accepted) {
        DetectedController* plc = &DetectedController::Instance();
        if(plc->getBootMode()) QMessageBox::warning(this,"системные настройки контроллера","Контроллер ожидает загрузки программы.\nЧтение/запись настроек невозможны.");
        else{
            SysFramReadWrite loader(false,this);
            connect(this,SIGNAL(readFromPLC()),&loader,SLOT(startReadProcess()));
            connect(&loader,SIGNAL(readOK(QByteArray)),this,SLOT(readFromBin(QByteArray)));
            emit readFromPLC();
            loader.exec();
            disconnect(this,SIGNAL(writeToPLC(QByteArray)),&loader,SLOT(startWriteProcess(QByteArray)));
        }
    }
}

void SettingsForm::on_pushButtonToPLC_clicked()
{
    QByteArray data;
    writeToBin(data);
    ScanGUI gui(progAddr,false,getPortName(),this);
    int ret = gui.exec();
    if(ret==QDialog::Accepted) {
        DetectedController* plc = &DetectedController::Instance();
        if(plc->getBootMode()) QMessageBox::warning(this,"системные настройки контроллера","Контроллер ожидает загрузки программы.\nЧтение/запись настроек невозможны.");
        else{
            SysFramReadWrite loader(false,this);
            connect(this,SIGNAL(writeToPLC(QByteArray)),&loader,SLOT(startWriteProcess(QByteArray)));
            emit writeToPLC(data);
            loader.exec();
            disconnect(this,SIGNAL(writeToPLC(QByteArray)),&loader,SLOT(startWriteProcess(QByteArray)));
        }
    }
}

void SettingsForm::on_spinBoxProgAddr_valueChanged(int arg1)
{
    progAddr = arg1;
}

void SettingsForm::on_comboBoxPLCType_currentTextChanged(const QString &arg1)
{
    setPLCType(arg1);
    PathStorage::setBuildName(getBuildName());
    emit newPLCType(arg1);
}

void SettingsForm::on_radioButtonNoEmulation_clicked()
{
    emit emuModeChanged(emuType::NoEmulation);
}

void SettingsForm::on_radioButtonInputEmulation_clicked()
{
    emit emuModeChanged(emuType::InputEmulation);
}

void SettingsForm::on_radioButtonInputOutputEmulation_clicked()
{
    emit emuModeChanged(emuType::InputOutputEmulation);
}


void SettingsForm::on_pushButtonPortListUpdate_clicked()
{
    QStringList portNames;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            portNames << info.portName();
    }
    ui->comboBoxPrPort->clear();
    if(portNames.count()) {
        foreach (QString pName, portNames) {
           ui->comboBoxPrPort->addItem(pName);
        }
    }
    ui->comboBoxPrPort->addItem("AUTO");
    ui->comboBoxPrPort->setCurrentText("AUTO");
}

void SettingsForm::on_spinBoxEMemSize_valueChanged(int arg1)
{
    eMemSize = arg1;
}

void SettingsForm::on_checkBoxModbus_clicked(bool checked)
{
    modbMasterEmuMode = checked;
}
