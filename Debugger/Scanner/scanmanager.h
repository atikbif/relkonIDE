#ifndef SCANMANAGER_H
#define SCANMANAGER_H

// обеспечивает размещение сканера контроллеров в отдельном потоке

#include <QObject>
#include <QThread>
#include "plcscanner.h"
#include "Debugger/memstorage.h"
#include "Debugger/requestscheduler.h"
#include "Debugger/debuggersettings.h"

class ScanManager : public QObject
{
    Q_OBJECT
    QThread scanThread;
    PLCScanner* scanner;

public:
    explicit ScanManager(MemStorage* memStor, QObject *parent = 0);
    void setScheduler(RequestScheduler* scheduler);
    void setDebSettings(const DebuggerSettings &newSettings);

    ~ScanManager();

signals:
    startProcess(void);
    void updateAnswerCnt(int cnt, bool correctAnswer);
    void addMessage(QString message);
private slots:
    void updCorrAnswerCnt(int cnt);
    void updErrAnswerCnt(int cnt);
    void getMessage(QString message);
public slots:
    void startDebugger();
    void stopDebugger();
};

#endif // SCANMANAGER_H
