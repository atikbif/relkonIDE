#ifndef SFRAM_H
#define SFRAM_H

// класс работы с системной областью FRAM (чтение/запись настроек)

#include <QObject>

class sFram : public QObject
{
    Q_OBJECT
public:
    explicit sFram(QObject *parent = 0);
    ~sFram();

signals:

public slots:
};

#endif // SFRAM_H
