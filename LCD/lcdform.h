#ifndef LCDFORM_H
#define LCDFORM_H

#include <QWidget>
#include "displaywidget.h"
#include "display.h"
#include "VarDef/varscreator.h"

namespace Ui {
class LCDForm;
}

class LCDForm : public QWidget
{
    Q_OBJECT
    DisplayWidget* dW;
    Display& displ;
    VarsCreator& varOwner;

public:
    explicit LCDForm(Display& d,VarsCreator& vCr, QWidget *parent = 0);
    ~LCDForm();

private:
    Ui::LCDForm *ui;
signals:
    void newProject(void);
    void openProject(void);
    void saveProject(void);
public slots:
    void updFocus(void);
};

#endif // LCDFORM_H
