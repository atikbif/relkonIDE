#ifndef VARWATCHERMANAGER_H
#define VARWATCHERMANAGER_H

#include <QWidget>
#include <QThread>
#include "varwatcher.h"
#include <QTableWidget>
#include <QStringList>

class VarWatcherManager : public QWidget
{
    Q_OBJECT

    QThread watchThread;
    VarWatcher* watcher;
    QTableWidget* table;

public:
    explicit VarWatcherManager(QWidget *parent = 0);
    ~VarWatcherManager();
    void setActive(bool value);
signals:
    startProcess();
    quickInfoRequest();
private slots:
    void quickInfo(QStringList names, QStringList values);
};

#endif // VARWATCHERMANAGER_H
