#ifndef PLCSCANNER_H
#define PLCSCANNER_H

// опрос контроллеров в режиме отладчика

#include <QObject>
#include <QMutex>
#include "Debugger/requestscheduler.h"

class PLCScanner : public QObject
{
    Q_OBJECT
    QMutex mutex;
    bool stopCmd;
    bool startCmd;
    bool finishCmd;
    RequestScheduler* scheduler;
public:
    explicit PLCScanner(QObject *parent = 0);
    ~PLCScanner();
    void startScanCmd(void);
    void stopScanCmd(void);
    void finishProcess(void);
    void setScheduler(RequestScheduler* ptr);
signals:
    updateBlock(QString memType, int addr, QByteArray data);
public slots:
    void scanProcess(void);

};

#endif // PLCSCANNER_H
