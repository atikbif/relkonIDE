#ifndef FLASHREAD_H
#define FLASHREAD_H

#include <QDialog>
#include <QThread>
#include "flash.h"


namespace Ui {
class FlashRead;
}

class FlashRead : public QDialog
{
    Q_OBJECT
    QThread flashThread;
    Flash* loader;
public:
    explicit FlashRead(QWidget *parent = 0);
    ~FlashRead();

signals:
    void startRead();
    void readOK(const QByteArray inpData);
public slots:
    void startReadProcess();
private slots:
    void error(QString message);
    void percentUpdate(float value);
    void readFinished(QByteArray data);
private:
    Ui::FlashRead *ui;
};

#endif // FLASHREAD_H
