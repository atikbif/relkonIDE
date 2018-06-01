#ifndef SYSFRAMREADWRITE_H
#define SYSFRAMREADWRITE_H

// GUI работы с FRAM памятью в отдельном потоке

#include <QDialog>
#include <QThread>
#include "sfram.h"

namespace Ui {
class SysFramReadWrite;
}

class SysFramReadWrite : public QDialog
{
    Q_OBJECT
    QThread sFramThread;
    sFram* loader;
public:
    explicit SysFramReadWrite(bool userFramflag = false, QWidget *parent = 0);
    ~SysFramReadWrite();
signals:
    void startWrite(QByteArray data);
    void startRead();

    void readOK(const QByteArray inpData);
public slots:
    void startWriteProcess(QByteArray data);
    void startReadProcess();
private slots:
    void writeFinished(void);
    void readFinished(QByteArray data);
    void error(QString message);
    void percentUpdate(float value);

private:
    Ui::SysFramReadWrite *ui;
};

#endif // SYSFRAMREADWRITE_H
