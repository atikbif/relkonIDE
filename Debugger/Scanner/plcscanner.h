#ifndef PLCSCANNER_H
#define PLCSCANNER_H

// опрос контроллеров в режиме отладчика

#include <QObject>
#include <QMutex>
#include "Debugger/requestscheduler.h"
#include "Debugger/debuggersettings.h"
#include <QString>
#include "Protocols/request.h"
#include <QSerialPort>

class PLCScanner : public QObject
{
    Q_OBJECT
    QMutex mutex;
    bool stopCmd;
    bool startCmd;
    bool finishCmd;
    RequestScheduler* scheduler;
    DebuggerSettings settings;
    int cntCorrect,cntError;
    QString reqToHexStr(Request &req);
    void startReq(QSerialPort &port);
public:
    explicit PLCScanner(QObject *parent = 0);
    ~PLCScanner();
    void startScanCmd(void);
    void stopScanCmd(void);
    void finishProcess(void);
    void setScheduler(RequestScheduler* ptr);
    void updSettings(const DebuggerSettings &newSettings) {settings=newSettings;}
signals:
    updateBlock(QString memType, int addr, QByteArray data);
    updateCorrectRequestCnt(int cnt);
    updateErrorRequestCnt(int cnt);
    addMessage(QString message);
public slots:
    void scanProcess(void);

};

#endif // PLCSCANNER_H
