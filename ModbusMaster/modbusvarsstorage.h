#ifndef MODBUSVARSSTORAGE_H
#define MODBUSVARSSTORAGE_H

#include <QVector>
#include <QSharedPointer>
#include "modbusvar.h"
#include <QStringList>

namespace modbusMaster {

class ModbusVarsStorage
{
    QVector<QSharedPointer<ModbusVar>> vars;
    const QString dinputsName="discreteInputs";
    const QString coilsName="Coils";
    const QString holdRegsName="HoldingRegisters";
    const QString inpregsName="InputRegisters";
public:
    ModbusVarsStorage();
    int getVarCnt() const {return vars.count();}
    bool addModbusVar(const ModbusVar &v);
    bool replaceModbusVar(const QString &vName, const ModbusVar &v);
    bool deleteModbusVar(const QString &vName);
    QSharedPointer<ModbusVar> getModbusVar(int index);
    QStringList getModbusVarsNames() const;
    QSharedPointer<ModbusVar> getModbusVarByName(const QString &vName);
    bool saveStorage(const QString &fullFileName);
    bool openStorage(const QString &fullFileName);
    void enableAll();
    void disableAll();
};

}

#endif // MODBUSVARSSTORAGE_H
