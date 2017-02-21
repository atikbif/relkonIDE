#include "dialogaddeditmodbusvar.h"
#include "ui_dialogaddeditmodbusvar.h"
#include <QRegExp>

DialogAddEditModbusVar::DialogAddEditModbusVar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddEditModbusVar), currentMode(DialogMode::ADD),var(ModbusVar("v1"))
{
    ui->setupUi(this);
    if(currentMode==DialogMode::ADD) {setWindowTitle("Добавить переменную");}
    else {setWindowTitle("Редактировать переменную");}
    ui->radioButtonRead->setChecked(true);
    ui->lineEditVarName->setText(var.getVarName());
    ui->comboBoxCanalType->setCurrentText("CAN_MB");
    ui->pushButtonOK->setFocus();
}

DialogAddEditModbusVar::~DialogAddEditModbusVar()
{
    delete ui;
}

void DialogAddEditModbusVar::setVar(const ModbusVar &v)
{
    var = v;
    if(currentMode==DialogMode::ADD) {
        // автоматический инкремент цифрового окончания в имени переменной и адреса в памяти
        QString vName = v.getVarName();
        QRegExp e("_(\\d+)$");
        if(e.indexIn(vName)!=-1) {
            int vNum = e.cap(1).toInt();
            vName.remove(e);
            vName+="_" + QString::number(vNum+1);
        }
        else {
            vName+="_2";
        }
        ui->lineEditVarName->setText(vName);
        var.setVarName(vName);

        int memAddr = var.getMemAddr();
        memAddr++;
        ui->spinBoxMemAddr->setValue(memAddr);
        var.setMemAddr(memAddr);
    }else {
        ui->lineEditVarName->setText(v.getVarName());
        ui->spinBoxMemAddr->setValue(v.getMemAddr());
    }

    ui->comboBoxCanalType->setCurrentText("CAN_MB");
    if(var.getMemType()==ModbusVar::INPUTS) ui->comboBoxMemType->setCurrentIndex(0);
    else if(var.getMemType()==ModbusVar::COILS) ui->comboBoxMemType->setCurrentIndex(1);
    else if(var.getMemType()==ModbusVar::HOLD_REG) ui->comboBoxMemType->setCurrentIndex(2);
    else if(var.getMemType()==ModbusVar::INP_REG) ui->comboBoxMemType->setCurrentIndex(3);
    var.setWriteFlag(v.getWriteFlag());
    ui->spinBoxNetAddress->setValue(var.getNetAddr());
    if(var.getWriteFlag()) ui->radioButtonWrite->setChecked(true);
    else ui->radioButtonRead->setChecked(true);
    ui->checkBoxEnable->setChecked(var.getActiv());
    ui->lineEditComment->setText(var.getComment());
}

void DialogAddEditModbusVar::setMode(DialogAddEditModbusVar::DialogMode m)
{
    currentMode = m;
    if(currentMode==DialogMode::ADD) {setWindowTitle("Добавить переменную");}
    else {setWindowTitle("Редактировать переменную");}
}


void DialogAddEditModbusVar::on_comboBoxMemType_currentIndexChanged(int index)
{
    switch(index) {
        case 0: // Discrete Inputs
            ui->radioButtonRead->setChecked(true);
            readWriteClicked();
            var.setMemType(ModbusVar::INPUTS);
            break;
        case 1: // Coils
            ui->radioButtonWrite->setChecked(true);
            readWriteClicked();
            var.setMemType(ModbusVar::COILS);
            break;
        case 2: // Holding Registers
            ui->radioButtonWrite->setChecked(true);
            readWriteClicked();
            var.setMemType(ModbusVar::HOLD_REG);
            break;
        case 3: // Input registers
            ui->radioButtonRead->setChecked(true);
            readWriteClicked();
            var.setMemType(ModbusVar::INP_REG);
            break;
    }
}

void DialogAddEditModbusVar::on_radioButtonRead_clicked()
{
    readWriteClicked();
}

void DialogAddEditModbusVar::on_radioButtonWrite_clicked()
{
    readWriteClicked();
}

void DialogAddEditModbusVar::readWriteClicked()
{
    int index = ui->comboBoxMemType->currentIndex();
    switch(index) {
        case 0: ui->radioButtonRead->setChecked(true);break;
        case 1: break;
        case 2: break;
        case 3: ui->radioButtonRead->setChecked(true);break;
    }
    var.setWriteFlag(ui->radioButtonWrite->isChecked());
}

void DialogAddEditModbusVar::on_spinBoxNetAddress_valueChanged(int arg1)
{
    var.setNetAddr(arg1);
}

void DialogAddEditModbusVar::on_spinBoxMemAddr_valueChanged(int arg1)
{
    var.setMemAddr(arg1);
}

void DialogAddEditModbusVar::on_checkBoxEnable_clicked()
{
    var.setActiv(ui->checkBoxEnable->isChecked());
}

void DialogAddEditModbusVar::on_lineEditVarName_textChanged(const QString &arg1)
{
    var.setVarName(arg1);
}

void DialogAddEditModbusVar::on_lineEditComment_textChanged(const QString &arg1)
{
    var.setComment(arg1);
}
