#ifndef YMODEM_H
#define YMODEM_H

// реализация протокола YMODEM

#include <QObject>
#include <QMutex>
#include <QFile>
#include <QSerialPort>

class Ymodem : public QObject
{
    Q_OBJECT
    QMutex mutex;
    bool stopCmd;
    QSerialPort* port;
    QFile* file;
    bool sendHeader();   // отправка заголовка файла
    bool sendStartYmodem();     // запуск ymodem из меню контроллера (1 - ymodem, 2 - старт программы, 3 - версия загрузчика)
    bool sendData(int reqNum);      // очередная порция данных
    bool sendEOT();             // end of transfer
    bool sendLastReq();         // последняя нулевая посылка после eot
public:
    explicit Ymodem(QObject *parent = 0);
    ~Ymodem();

signals:
    void finished(void);
    void percentUpdate(float value);
    void bootError(const QString& message);
public slots:
    void stopProcess(void);
    void startProcess(const QString &pName, const QString &filePath);
};

#endif // YMODEM_H
