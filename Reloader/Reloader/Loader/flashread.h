#ifndef FLASHREAD_H
#define FLASHREAD_H

#include <QDialog>

namespace Ui {
class FlashRead;
}

class FlashRead : public QDialog
{
    Q_OBJECT

public:
    explicit FlashRead(QWidget *parent = 0);
    ~FlashRead();

private:
    Ui::FlashRead *ui;
};

#endif // FLASHREAD_H
