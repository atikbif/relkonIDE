#ifndef DETECTEDCONTROLLER_H
#define DETECTEDCONTROLLER_H

// паттерн синглтон для хранения параметров последнего успешного поиска контроллера

#include <QObject>
#include <QMutex>

class DetectedController
{
    qint32 baudrate;
    qint8 netAddress;
    QString uartName;
    bool asciiMode;
    bool bootMode;
    QMutex mutex;
public:
    static DetectedController& Instance()
    {
        static DetectedController singleton;
        return singleton;
    }
    qint32 getBaudrate();
    void setBaudrate(const qint32 &value);

    qint8 getNetAddress();
    void setNetAddress(const qint8 &value);

    QString getUartName();
    void setUartName(const QString &value);

    bool getAsciiMode();
    void setAsciiMode(bool value);

    bool getBootMode();
    void setBootMode(bool value);

private:
    DetectedController();                                          // Private constructor
    ~DetectedController();
    DetectedController(const DetectedController&);                 // Prevent copy-construction
    DetectedController& operator=(const DetectedController&);      // Prevent assignment
};

#endif // DETECTEDCONTROLLER_H
