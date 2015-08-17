#ifndef DIALOGWRITEVAR_H
#define DIALOGWRITEVAR_H

#include <QDialog>
#include "varitem.h"

namespace Ui {
class DialogWriteVar;
}

class DialogWriteVar : public QDialog
{
    Q_OBJECT

    VarItem var;
public:
    explicit DialogWriteVar(QString startValue,QWidget *parent = 0);
    QString getResult(void);
    bool checkResult(void);
    void setVar(VarItem inpVar) {var=inpVar;}
    ~DialogWriteVar();

private:
    Ui::DialogWriteVar *ui;
};

#endif // DIALOGWRITEVAR_H
