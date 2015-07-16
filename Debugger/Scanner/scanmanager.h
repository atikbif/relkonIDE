#ifndef SCANMANAGER_H
#define SCANMANAGER_H

// обеспечивает размещение сканера контроллеров в отдельном потоке

#include <QObject>

class ScanManager : public QObject
{
    Q_OBJECT
public:
    explicit ScanManager(QObject *parent = 0);
    ~ScanManager();

signals:

public slots:
};

#endif // SCANMANAGER_H
