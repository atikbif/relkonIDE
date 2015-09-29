#ifndef DIALOGWRITEVAR_H
#define DIALOGWRITEVAR_H

// Диалог для ввода значения переменной при записи

#include <QDialog>
#include "VarDef/varitem.h"

namespace Ui {
class DialogWriteVar;
}

class DialogWriteVar : public QDialog
{
    Q_OBJECT
    VarItem var;    // для определения типа редактируемой переменной
public:
    explicit DialogWriteVar(QString startValue,QWidget *parent = 0);
    QString getResult(void);    // введённое значение
    bool checkResult(void);     // проверка введённого значения на корректность
    void setVar(const VarItem &inpVar) {var=inpVar;}    // задать тип переменной
    ~DialogWriteVar();

private:
    Ui::DialogWriteVar *ui;
};

#endif // DIALOGWRITEVAR_H
