#ifndef MODBUSVAR_H
#define MODBUSVAR_H

#include <QString>

namespace modbusMaster {

    class ModbusVar
    {
    public:
        enum canType {CAN_PC, CAN_MB};
        enum memType {HOLD_REG, INP_REG, COILS, INPUTS};
    private:
        canType can;
        memType mem;
        int netAddr;
        QString varName;
        bool writeFlag;
        int memAddr;
        bool activ;
        QString comment;
    public:
        explicit ModbusVar(const QString &vName);

        canType getCanType() const;
        void setCanType(const canType &value);
        memType getMemType() const;
        void setMemType(const memType &value);
        int getNetAddr() const;
        void setNetAddr(int value);
        QString getVarName() const;
        void setVarName(const QString &value);
        bool getWriteFlag() const;
        void setWriteFlag(bool value);
        int getMemAddr() const;
        void setMemAddr(int value);
        bool getActiv() const;
        void setActiv(bool value);
        QString getComment() const;
        void setComment(const QString &value);
    };

}



#endif // MODBUSVAR_H
