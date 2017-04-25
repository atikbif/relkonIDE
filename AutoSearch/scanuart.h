#ifndef SCANUART_H
#define SCANUART_H

// класс, выпоняющий поиск контроллера на заданном UART

#include <QObject>
#include <QString>
#include <QMutex>
#include <QVector>
#include "detectedcontroller.h"
#include <QSerialPort>
#include "searchcontroller.h"

class ScanUART : public QObject
{
    Q_OBJECT

    QString pName;
    QMutex mutex;
    bool stopCmd;
    bool startCmd;
    QVector<qint32> baudTable;
    unsigned char progAddr;

    bool scan(QSerialPort &port);
    bool testBootMode(QSerialPort &port);
    void sendAbortCmd(QSerialPort &port);

public:
    void setProgAddr(unsigned char value) {progAddr=value;}
    explicit ScanUART(QObject *parent = 0);
    ~ScanUART();

signals:
    void percentUpdate(float percValue);
    void scanIsFinished(const QString& message);
    void plcHasBeenFound(SearchController plc);
    void portIsBusy();
public slots:
    void startScan(const QString &pName);
    void stopScan(void);
};

#endif // SCANUART_H
