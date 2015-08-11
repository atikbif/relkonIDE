#ifndef SCANMANAGER_H
#define SCANMANAGER_H

// обеспечивает размещение сканера контроллеров в отдельном потоке

#include <QObject>
#include <QThread>
#include "plcscanner.h"
#include "Debugger/memstorage.h"
#include "Debugger/requestscheduler.h"

class ScanManager : public QObject
{
    Q_OBJECT
    QThread scanThread;
    PLCScanner* scanner;

public:
    explicit ScanManager(MemStorage* memStor, QObject *parent = 0);
    void setScheduler(RequestScheduler* scheduler);
    ~ScanManager();

signals:
    startProcess(void);
    void updateAnswerCnt(int cnt, bool correctAnswer);
private slots:
    void updCorrAnswerCnt(int cnt);
    void updErrAnswerCnt(int cnt);
public slots:
    void startDebugger();
    void stopDebugger();
};

#endif // SCANMANAGER_H
