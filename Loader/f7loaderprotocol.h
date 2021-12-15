#ifndef F7LOADERPROTOCOL_H
#define F7LOADERPROTOCOL_H

#include <QSerialPort>

class F7LoaderProtocol
{
    static const unsigned char crc16H[256];
    static const unsigned char crc16L[256];
    static void addCRC16(QByteArray &reqData);
    static quint16 id;
public:
    F7LoaderProtocol() = default;
    static bool setBootMode(QSerialPort &port, int &netAddr, int waitTime);
    static bool checkBootMode(QSerialPort &port, int netAddr, int waitTime);
    static bool eraseSector(QSerialPort &port, int netAddr, int waitTime, int sectNum);
    static bool writeFlash(QSerialPort &port, int &netAddr, int waitTime, quint32 addr, quint16 cnt, QByteArray::ConstIterator it);
    static bool jumptoProg(QSerialPort &port, int &netAddr, int waitTime);
};

#endif // F7LOADERPROTOCOL_H
