#ifndef BOOTMODESETTER_H
#define BOOTMODESETTER_H

// класс перевода контроллера в режим загрузчика
// работает в основном потоке (процесс непродолжительный,
// поэтому в отдельный поток не выносится)

#include<QObject>

class BootModeSetter: public QObject
{
    Q_OBJECT
    static const qint16 codeWordAddress = 0x7FF5;
    static const qint8 codeWordSize = 6;
public:
    explicit BootModeSetter(QObject *parent = 0);
    bool setBootMode(void);
    ~BootModeSetter();
};

#endif // BOOTMODESETTER_H
