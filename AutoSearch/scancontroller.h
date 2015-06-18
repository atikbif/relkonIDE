#ifndef SCANCONTROLLER_H
#define SCANCONTROLLER_H

#include <QObject>

class ScanController : public QObject
{
    Q_OBJECT
public:
    explicit ScanController(QObject *parent = 0);
    ~ScanController();

signals:

public slots:
};

#endif // SCANCONTROLLER_H
