#ifndef CLEANPROCESS_H
#define CLEANPROCESS_H

#include <QObject>
#include <QMutex>
#include <QHash>

class CleanProcess: public QObject
{
    Q_OBJECT

    QHash<QString,qint64> fKonList;
    QHash<QString,qint64> fLcdList;
    QMutex mutex;
    bool startCmd;
    bool finishCmd;
public:
    explicit CleanProcess(QObject *parent = 0);
public:
    void startClean(void);
    void finishProcess(void);
public slots:
    void startProcess(void); // рабочий процесс
};

#endif // CLEANPROCESS_H
