#ifndef PLCSCANNER_H
#define PLCSCANNER_H

// опрос контроллеров в режиме отладчика

#include <QObject>
#include <QMutex>

class PLCScanner : public QObject
{
    Q_OBJECT
    QMutex mutex;
    bool stopCmd;
    bool startCmd;
    bool finishCmd;
public:
    explicit PLCScanner(QObject *parent = 0);
    ~PLCScanner();
    void startScanCmd(void);
    void stopScanCmd(void);
    void finishProcess(void);
signals:
    updateBlock(QString memType, int addr, QByteArray data);
public slots:
    void scanProcess(void);

};

#endif // PLCSCANNER_H
