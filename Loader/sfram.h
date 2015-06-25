#ifndef SFRAM_H
#define SFRAM_H

// класс работы с системной областью FRAM (чтение/запись настроек)

#include <QObject>
#include <QByteArray>
#include <QSerialPort>
#include <QMutex>

class sFram : public QObject
{
    Q_OBJECT
    QMutex mutex;
    bool stopCmd;
    static const int reqLength = 128;
    void controllerReset(QSerialPort &port);
    bool testControllerReady(void); // проверка готовности контроллера к чтению/записи настроек
public:
    explicit sFram(QObject *parent = 0);
    ~sFram();

signals:
    void writeFinished(void);
    void readFinished(QByteArray data);
    void error(QString message);
    void percentUpdate(float value);
public slots:
    void startWrite(QByteArray data);
    void startRead();
    void stopProcess(void);
};

#endif // SFRAM_H
