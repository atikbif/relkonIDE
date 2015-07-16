#ifndef PLCSCANNER_H
#define PLCSCANNER_H

// опрос контроллеров в режиме отладчика

#include <QObject>

class PLCScanner : public QObject
{
    Q_OBJECT
public:
    explicit PLCScanner(QObject *parent = 0);
    ~PLCScanner();

signals:

public slots:
};

#endif // PLCSCANNER_H
