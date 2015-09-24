#ifndef LCDFORM_H
#define LCDFORM_H

#include <QWidget>
#include "displaywidget.h"
#include "display.h"

namespace Ui {
class LCDForm;
}

class LCDForm : public QWidget
{
    Q_OBJECT
    DisplayWidget* dW;
    Display& displ;
public:
    explicit LCDForm(Display& d,QWidget *parent = 0);
    ~LCDForm();

private:
    Ui::LCDForm *ui;
};

#endif // LCDFORM_H
