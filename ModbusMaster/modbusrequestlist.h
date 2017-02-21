#ifndef MODBUSREQUESTLIST_H
#define MODBUSREQUESTLIST_H

#include <QString>
#include "modbusvarsstorage.h"
#include <QVector>

namespace modbusMaster {

class ModbusRequestList
{
    QString can;
    QVector<QSharedPointer<ModbusVar>> vars;
    struct VarReq {
        int byteOffset;
        int bitOffset;
        QString varName;
    };

    int maxSpaceLength;
    int maxLength;

    enum ModbusCMD {READ_DI, READ_COILS, WRITE_COILS, READ_HOLD_REG, WRITE_HOLD_REG, READ_INP_REG};

    struct Request {
        int netAddress;
        ModbusCMD cmd;
        int memAddress;
        int cnt;
        QVector<VarReq> reqVars;
    };
    QVector<Request> reqs;

    static const unsigned char crc16H[256];
    static const unsigned char crc16L[256];

    int delay;

public:
    ModbusRequestList(const QString &canName, ModbusVarsStorage &mVars);
    QStringList getResult();
    QStringList getPlugResult();
    void setMaxSpaceLength(int value);
    void setMaxLength(int value);
    void setDelay(int value) {delay = value;}
    int getDelay() const {return delay;}
    QStringList getVarNames();
    QStringList getPlugVarNames();

private:
    void createRequests();
    QByteArray getRequestBody(const Request &r);
    int getAnswerLength(const Request &r);
    bool isWriteReq(const Request &r);
    void addCRC16(QByteArray &reqData);
    void sortVarsByMemAddress();
    void addRequestToList(const Request &r);
    QStringList getHeader();
    QStringList getReqText();
};

}

#endif // MODBUSREQUESTLIST_H
