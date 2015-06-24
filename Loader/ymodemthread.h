#ifndef YMODEMTHREAD_H
#define YMODEMTHREAD_H

// класс GUI и управления потоком Ymodem

#include <QDialog>
#include "ymodem.h"
#include <QThread>
#include <QIODevice>
#include <QFile>
#include <QLabel>
#include <QProgressBar>

namespace Ui {
class YmodemThread;
}

class YmodemThread : public QDialog
{
    Q_OBJECT
    QThread bootThread;
    Ymodem* loader;
    QProgressBar* bar;
    QLabel* label;
public:
    explicit YmodemThread(const QString &pName=0, QWidget *parent = 0);
    ~YmodemThread();
signals:
    void startProcess(const QString &pName, const QString &filePath);
public slots:
    void finished(void);
    void percentUpdate(float value);
    void bootError(const QString& message);
private:
    Ui::YmodemThread *ui;
};

#endif // YMODEMTHREAD_H
