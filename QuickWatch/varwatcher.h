#ifndef VARWATCHER_H
#define VARWATCHER_H

#include <QObject>

class VarWatcher : public QObject
{
    Q_OBJECT

    bool finishFlag;
public:
    explicit VarWatcher(QObject *parent = 0);
    void finishProcess();
signals:
    quickInfoRequest();
public slots:
    void updateProcess(void); // обновление данных    
};

#endif // VARWATCHER_H
