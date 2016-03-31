#ifndef DIALOGSPESSYMB_H
#define DIALOGSPESSYMB_H

// виртуальная клавиатура для вставки спец символов

#include <QDialog>

namespace Ui {
class DialogSpesSymb;
}

class DialogSpesSymb : public QDialog
{
    Q_OBJECT
    int code;
public:
    explicit DialogSpesSymb(QWidget *parent = 0);
    ~DialogSpesSymb();
    int getCode() const {return code;}

private slots:
    void button_clicked();

private:
    Ui::DialogSpesSymb *ui;
};

#endif // DIALOGSPESSYMB_H
