#ifndef REQUESTSCHEDULER_H
#define REQUESTSCHEDULER_H

#include <QObject>
#include "Protocols/rkcommand.h"
#include "Protocols/request.h"
#include <Qvector>
#include <QMutex>
#include "varitem.h"

struct CmdData{
    CommandInterface* cmd;
    Request* req;
};

class RequestScheduler : public QObject
{
    QMutex mutex;
    QVector<CmdData*> cmdQueue;
    int i;  // текущий индекс
    Q_OBJECT
public:
    explicit RequestScheduler(QObject *parent = 0);
    CommandInterface* getCmd(void);  // возвращает команду для выполнения
    Request getReq(void);   // данные запроса для команды
    void moveToNext();  // переместиться к следующей команде в цикле
    void addReadOperation(VarItem v);   // добавить операцию чтения переменной
    void removeReadOperation(VarItem v);    // удалить чтение области памяти переменной
    void addWriteOperation(VarItem v);  // запрос на запись переменной
    void clearQueue(void);  // очистить очередь запросов
    void schedule();    // сформировать очередь запросов
    ~RequestScheduler();

signals:

public slots:

};

#endif // REQUESTSCHEDULER_H
