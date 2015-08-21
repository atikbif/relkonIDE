#ifndef PLCSCANNER_H
#define PLCSCANNER_H

//----------Класс, выполняющий опрос контроллера в режиме отладчика
//----------работает в отдельном потоке

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
    bool stopCmd;       // команда на приостановку опроса
    bool startCmd;      // команда на запуск опроса
    bool finishCmd;     // команда на завершение работы потока
    RequestScheduler* scheduler;        // планировщик запросов
    DebuggerSettings settings;          // настройки канала связи отладчика (UDP,COM)
    int cntCorrect,cntError;            // счётчики успешных и ошибочных запросов
    QString reqToHexStr(Request &req);  // преобразование запроса и ответа в текст для отображения в логе
    void startReq(QSerialPort &port);   // системные запросы, не зависящие от планировщика (время ПЛК)
    static const int sysReqPeriod = 10; // периодичность включения системных запросов
public:
    explicit PLCScanner(QObject *parent = 0);
    ~PLCScanner();
    void startScanCmd(void);
    void stopScanCmd(void);
    void finishProcess(void);
    void setScheduler(RequestScheduler* ptr);
    void updSettings(const DebuggerSettings &newSettings) {settings=newSettings;}
    bool isWorking(void) {return startCmd;}
signals:
    updateBlock(QString memType, int addr, QByteArray data);    // обновление блока памяти
    updateCorrectRequestCnt(int cnt);
    updateErrorRequestCnt(int cnt);
    addMessage(QString message);    // добавить сообщение в лог
    updateTimeStr(QString timeStr); // обновить текущее время ПЛК
public slots:
    void scanProcess(void); // рабочий процесс

};

#endif // PLCSCANNER_H
