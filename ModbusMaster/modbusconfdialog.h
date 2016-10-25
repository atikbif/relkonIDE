#ifndef MODBUSCONFDIALOG_H
#define MODBUSCONFDIALOG_H

#include <QDialog>
#include "modbusvar.h"
#include "modbusvarsstorage.h"

namespace Ui {
class ModbusConfDialog;
}

using namespace modbusMaster;

class ModbusConfDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModbusConfDialog(QWidget *parent = 0);
    ~ModbusConfDialog();
private slots:
    void on_pushButtonAddVar_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDel_clicked();

    void on_pushButtonEnableAll_clicked();

    void on_pushButtonDisableAll_clicked();

private:
    Ui::ModbusConfDialog *ui;
    ModbusVar var;
    ModbusVarsStorage vars;
    void updateRow(int row, const ModbusVar &v);
};

#endif // MODBUSCONFDIALOG_H
