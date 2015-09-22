#ifndef LCDFORM_H
#define LCDFORM_H

#include <QWidget>

namespace Ui {
class LCDForm;
}

class LCDForm : public QWidget
{
    Q_OBJECT

public:
    explicit LCDForm(QWidget *parent = 0);
    ~LCDForm();

private:
    Ui::LCDForm *ui;
};

#endif // LCDFORM_H
