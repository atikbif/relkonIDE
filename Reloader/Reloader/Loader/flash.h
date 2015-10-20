#ifndef FLASH_H
#define FLASH_H

#include <QObject>
#include <QMutex>
#include <QByteArray>

class Flash : public QObject
{
    Q_OBJECT
    QMutex mutex;
    bool stopCmd;
    static const int reqLength = 128;
    bool testControllerReady(void);
public:
    explicit Flash(QObject *parent = 0);
    ~Flash();
signals:
    void readFinished(QByteArray data);
    void error(QString message);
    void percentUpdate(float value);
public slots:
    void startRead();
    void stopProcess(void);
};

#endif // FLASH_H
