#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

#include <QObject>
#include <QMutex>

class SearchController
{
    qint32 baudrate;
    qint8 netAddress;
    QString uartName;
    bool asciiMode;
    bool bootMode;
    QString canName;
    QString mcuType;
public:
    SearchController();

    qint32 getBaudrate() const;
    void setBaudrate(const qint32 &value);
    qint8 getNetAddress() const;
    void setNetAddress(const qint8 &value);
    QString getUartName() const;
    void setUartName(const QString &value);
    bool getAsciiMode() const;
    void setAsciiMode(bool value);
    bool getBootMode() const;
    void setBootMode(bool value);
    QString getCanName() const;
    void setCanName(const QString &value);
    const QString &getMcuType() const;
    void setMcuType(const QString &newMcuType);
};

#endif // SEARCHCONTROLLER_H
