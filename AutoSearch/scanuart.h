#ifndef SCANUART_H
#define SCANUART_H

#include <QObject>

class ScanUART : public QObject
{
    Q_OBJECT
public:
    explicit ScanUART(QObject *parent = 0);
    ~ScanUART();

signals:

public slots:
};

#endif // SCANUART_H
