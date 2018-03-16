#include "modbusconfdialog.h"
#include "ui_modbusconfdialog.h"
#include "dialogaddeditmodbusvar.h"
#include <QMessageBox>
#include "modbusrequestlist.h"
#include "pathstorage.h"

ModbusConfDialog::ModbusConfDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModbusConfDialog), var(ModbusVar("mvar_0"))
{
    ui->setupUi(this);
    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vars.openStorage(PathStorage::getBuildDir()+"/mvar.xml");
    ui->spinBoxMaxLength->setValue(vars.getMaxLength());
    ui->spinBoxMaxBreak->setValue(vars.getMaxSpaceLength());
    ui->spinBoxDelay->setValue(vars.getDelay());
    for(int i=0;i<vars.getVarCnt();++i) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        updateRow(row,*(vars.getModbusVar(i)));
    }
    ui->tableWidget->sortByColumn(0, Qt::AscendingOrder);
}

ModbusConfDialog::~ModbusConfDialog()
{
    vars.setMaxLength(ui->spinBoxMaxLength->value());
    vars.setMaxSpaceLength(ui->spinBoxMaxBreak->value());
    vars.setDelay(ui->spinBoxDelay->value());
    vars.saveStorage(PathStorage::getBuildDir()+"/mvar.xml");

    /*ModbusRequestList rList("MB", vars);
    rList.setMaxLength(vars.getMaxLength());
    rList.setMaxSpaceLength(vars.getMaxSpaceLength());
    QStringList reqBody = rList.getResult();
    Q_UNUSED(reqBody)*/
    delete ui;
}

void ModbusConfDialog::on_pushButtonAddVar_clicked()
{
    DialogAddEditModbusVar *dialog = new DialogAddEditModbusVar();
    if(vars.getVarCnt()==0) var.setMemAddr(-1);
    dialog->setVar(var);
    int ret = dialog->exec();
    if(ret==QDialog::Accepted) {
        var = dialog->getVar();
        if(!vars.addModbusVar(var)) {
            QMessageBox::warning(this, "Неккоректные данные", "Переменная с таким именем уже существует!");
        }else {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            updateRow(row,var);
        }
    }
    delete dialog;
}

void ModbusConfDialog::on_pushButtonEdit_clicked()
{
    if(ui->tableWidget->rowCount()) {
        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
        if(items.count()==0) {
            ui->tableWidget->selectRow(0);
            items = ui->tableWidget->selectedItems();
        }
        QString varName;
        int varRow=0;
        for(QTableWidgetItem *i:items) {
            if(i->column()==0) {
                varName=i->text();
                varRow=i->row();
            }
        }
        if(!varName.isEmpty()) {
            QSharedPointer<ModbusVar> selVar = vars.getModbusVarByName(varName);
            DialogAddEditModbusVar *dialog = new DialogAddEditModbusVar();
            dialog->setMode(DialogAddEditModbusVar::EDIT);
            dialog->setVar(*selVar);
            int ret = dialog->exec();
            if(ret==QDialog::Accepted) {
                var = dialog->getVar();
                vars.replaceModbusVar(varName,var);
                updateRow(varRow,var);
            }
            delete dialog;
        }
    }else {
        QMessageBox::warning(this, "Невозможно выполнить операцию", "Отсутствуют переменные для редактирования!");
    }
}

void ModbusConfDialog::on_pushButtonDel_clicked()
{
    if(ui->tableWidget->rowCount()) {
        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
        if(items.count()==0) {
            ui->tableWidget->selectRow(0);
            items = ui->tableWidget->selectedItems();
        }
        QString varName;
        int varRow=0;
        for(QTableWidgetItem *i:items) {
            if(i->column()==0) {
                varName=i->text();
                varRow=i->row();
            }
        }
        if(!varName.isEmpty()) {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Подтверждение операции",
                                                                      "Удалить переменную " + varName + "?",
                                        QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                vars.deleteModbusVar(varName);
                ui->tableWidget->removeRow(varRow);
            }
        }
    }else {
        QMessageBox::warning(this, "Невозможно выполнить операцию", "Отсутствуют переменные для удаления!");
    }
}

void ModbusConfDialog::updateRow(int row, const ModbusVar &v)
{
    ModbusVar::canType cType = v.getCanType();
    if(cType==ModbusVar::CAN_MB) ui->tableWidget->setItem(row,1,new QTableWidgetItem("MB"));
    else if(cType==ModbusVar::CAN_PC) ui->tableWidget->setItem(row,1,new QTableWidgetItem("PC"));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(v.getNetAddr())));
    ModbusVar::memType mType = v.getMemType();
    if(mType==ModbusVar::INPUTS) ui->tableWidget->setItem(row,3,new QTableWidgetItem("DISCRETE INPUTS"));
    else if(mType==ModbusVar::COILS) ui->tableWidget->setItem(row,3,new QTableWidgetItem("COILS"));
    else if(mType==ModbusVar::HOLD_REG) ui->tableWidget->setItem(row,3,new QTableWidgetItem("HOLDING REGISTERS"));
    else if(mType==ModbusVar::INP_REG) ui->tableWidget->setItem(row,3,new QTableWidgetItem("INPUT REGISTERS"));
    ui->tableWidget->setItem(row,4,new QTableWidgetItem(v.getWriteFlag()?"запись":"чтение"));
    ui->tableWidget->setItem(row,5,new QTableWidgetItem(QString::number(v.getMemAddr())));
    ui->tableWidget->setItem(row,6,new QTableWidgetItem(v.getActiv()?"вкл":"откл"));
    ui->tableWidget->setItem(row,7,new QTableWidgetItem(v.getComment()));
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(v.getVarName()));
}

void ModbusConfDialog::on_pushButtonEnableAll_clicked()
{
    vars.enableAll();
    for(int i=0;i<ui->tableWidget->rowCount();++i) {
        ui->tableWidget->setItem(i,6,new QTableWidgetItem("вкл"));
    }
}

void ModbusConfDialog::on_pushButtonDisableAll_clicked()
{
    vars.disableAll();
    for(int i=0;i<ui->tableWidget->rowCount();++i) {
        ui->tableWidget->setItem(i,6,new QTableWidgetItem("откл"));
    }
}
