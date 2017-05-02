#ifndef DIALOGGOTOSTRING_H
#define DIALOGGOTOSTRING_H

#include <QDialog>

namespace Ui {
class DialogGoToString;
}

class DialogGoToString : public QDialog
{
    Q_OBJECT
    int strNum = 1;
public:
    explicit DialogGoToString(QWidget *parent = 0);
    ~DialogGoToString();
    int getStrNum(void) {return strNum;}

private slots:
    void on_spinBoxStrNum_valueChanged(int arg1);

private:
    Ui::DialogGoToString *ui;
};

#endif // DIALOGGOTOSTRING_H
