#ifndef DIALOGADDEDITMODBUSVAR_H
#define DIALOGADDEDITMODBUSVAR_H

#include <QDialog>
#include "modbusvar.h"

using namespace modbusMaster;

namespace Ui {
class DialogAddEditModbusVar;
}

class DialogAddEditModbusVar : public QDialog
{
    Q_OBJECT

public:
    enum DialogMode {ADD, EDIT};
    explicit DialogAddEditModbusVar(QWidget *parent = 0);
    ~DialogAddEditModbusVar();
    void setVar(const ModbusVar &v);
    ModbusVar getVar() const {return var;}
    void setMode(DialogMode m);
private slots:
    void on_comboBoxMemType_currentIndexChanged(int index);

    void on_radioButtonRead_clicked();

    void on_radioButtonWrite_clicked();

    void on_spinBoxNetAddress_valueChanged(int arg1);

    void on_spinBoxMemAddr_valueChanged(int arg1);

    void on_checkBoxEnable_clicked();

    void on_lineEditVarName_textChanged(const QString &arg1);

    void on_lineEditComment_textChanged(const QString &arg1);

private:
    Ui::DialogAddEditModbusVar *ui;
    DialogMode currentMode;
    ModbusVar var;

    void readWriteClicked();
};

#endif // DIALOGADDEDITMODBUSVAR_H
