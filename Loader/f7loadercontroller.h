#ifndef F7LOADERCONTROLLER_H
#define F7LOADERCONTROLLER_H

#include <QObject>
#include <QMutex>
#include <QDialog>
#include <QProgressBar>
#include <QLabel>
#include <QThread>


class F7LoaderWorker : public QObject
{
    Q_OBJECT
    QString pName;
    int netAddr;
    bool stopFlag = false;
    bool rstFlag = true;
    QMutex mutex;
public:
    explicit F7LoaderWorker(const QString pName, int netAddr, bool rstFlag, QObject *parent = nullptr);
public slots:
    void writeFile(const QString &fName);
    void stopLoad();
signals:
    void writeComplete();
    void error();
    void info(QString message);
    void percentUpdate(double val);
};

class F7LoaderController : public QObject
{
    Q_OBJECT
    QDialog *dialog = nullptr;
    QProgressBar *bar = nullptr;
    QLabel *label = nullptr;
    QThread workerThread;
    F7LoaderWorker *worker = nullptr;
    bool rstFlag = true;
public:
    explicit F7LoaderController(const QString pName, int netAddr, const QString &fName, bool reset_flag, QObject *parent = nullptr);
    ~F7LoaderController();
private slots:
    void info(QString message);
    void percentUpdate(double val);
signals:
    void writeComplete();
    void error();
    void writeCmd(const QString &fName);
    void stopCmd();

signals:

};

#endif // F7LOADERCONTROLLER_H
