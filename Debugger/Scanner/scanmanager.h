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
    bool isWorking(void) {return scanner->isWorking();}

    ~ScanManager();

signals:
    startProcess(void); // промежуточный сигнал для запуска сканера
    // ретранслированные сигналы от сканера
    void updateAnswerCnt(int cnt, bool correctAnswer);
    void addMessage(QString message);
    void updateTimeStr(QString timeStr);
private slots:
    // слоты для принятия сигналов от сканера
    void updCorrAnswerCnt(int cnt);
    void updErrAnswerCnt(int cnt);
public slots:
    void startDebugger();
    void stopDebugger();
};

#endif // SCANMANAGER_H
