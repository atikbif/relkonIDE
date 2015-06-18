#ifndef SCANCONTROLLER_H
#define SCANCONTROLLER_H

// отвечает за размещение процесса поиска контроллера (класс ScanUART) в отдельном потоке

#include <QObject>
#include <QThread>
#include <QString>
#include "scanuart.h"

class ScanController : public QObject
{
    Q_OBJECT
    QThread scanThread;
    QString pName;
    ScanUART* scanWorker;
public:
    explicit ScanController(const QString &pName, QObject *parent = 0);
    ~ScanController();

signals:
    void updated(float percValue,const QString &pName);
    void finished(const QString& message);
    void found(DetectedController* plc,const QString &pName);
    void startScan(const QString &pName);
private slots:
    void percentUpdate(float percValue);
    void scanIsFinished(const QString& message);
    void plcHasBeenFound(DetectedController* plc);
};

#endif // SCANCONTROLLER_H
