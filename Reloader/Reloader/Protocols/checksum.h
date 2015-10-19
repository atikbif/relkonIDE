#ifndef CHECKSUM_H
#define CHECKSUM_H

// класс для расчёта контрольной суммы

#include <QByteArray>

class CheckSum
{
private:
    static const quint16 wCRCTable[];
    CheckSum();
    ~CheckSum();
public:
    static int getCRC16(const QByteArray &inpData);
    static int getCRCXModem(const QByteArray &inpData);
};

#endif // CHECKSUM_H
