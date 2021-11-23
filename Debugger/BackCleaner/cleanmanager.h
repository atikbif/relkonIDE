#ifndef CLEANMANAGER_H
#define CLEANMANAGER_H

#include <QObject>
#include <QThread>
#include "cleanprocess.h"

class CleanManager: public QObject
{
    Q_OBJECT
    QThread cleanThread;
    CleanProcess* cleaner;
public:
    explicit CleanManager(QObject *parent = 0);
    ~CleanManager();
    void startClean();
signals:
    void startProcess(void);
};

#endif // CLEANMANAGER_H
