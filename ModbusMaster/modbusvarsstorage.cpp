#include "modbusvarsstorage.h"
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QFile>

namespace modbusMaster {

ModbusVarsStorage::ModbusVarsStorage():
    maxSpaceLength(4),maxLength(16),delay(100)
{

}

bool ModbusVarsStorage::addModbusVar(const ModbusVar &v)
{
    QStringList vNames = getModbusVarsNames();
    if((!vNames.contains(v.getVarName()))&&(!v.getVarName().isEmpty())) {
        QSharedPointer<ModbusVar> var(new ModbusVar(v));
        vars.append(var);
        return true;
    }
    return false;
}

bool ModbusVarsStorage::replaceModbusVar(const QString &vName, const ModbusVar &v)
{
    for(QSharedPointer<ModbusVar> &var:vars) {
        if(var->getVarName()==vName) {
            *var = v;
            return true;
        }
    }
    return false;
}

bool ModbusVarsStorage::deleteModbusVar(const QString &vName)
{
    bool findFlag = false;
    int varNum = 0;
    for(int i=0;i<vars.count();++i) {
        if(vars.at(i)->getVarName()==vName) {
            findFlag = true;
            varNum = i;
            break;
        }
    }
    if(findFlag) {
        vars.removeAt(varNum);
        return true;
    }
    return false;
}

QSharedPointer<ModbusVar> ModbusVarsStorage::getModbusVar(int index)
{
    if((index>=0)&&(index<getVarCnt())) {
        return vars[index];
    }
    return QSharedPointer<ModbusVar>(new ModbusVar(""));
}

QStringList ModbusVarsStorage::getModbusVarsNames() const
{
    QStringList vNames;
    for(QSharedPointer<ModbusVar> var:vars) {
        vNames+=var->getVarName();
    }
    return vNames;
}

QSharedPointer<ModbusVar> ModbusVarsStorage::getModbusVarByName(const QString &vName)
{
    for(QSharedPointer<ModbusVar> var:vars) {
        if(var->getVarName()==vName) return var;
    }
    return QSharedPointer<ModbusVar>(new ModbusVar(""));
}

bool ModbusVarsStorage::saveStorage(const QString &fullFileName)
{
    QFile file(fullFileName);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&file);

    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    stream.writeStartElement("modbusVariables");
    stream.writeAttribute("version", "1.0");
    stream.writeAttribute("maxLength",QString::number(maxLength));
    stream.writeAttribute("maxSpaceLength",QString::number(maxSpaceLength));
    stream.writeAttribute("delay",QString::number(delay));
    for(QSharedPointer<ModbusVar> var:vars) {
        stream.writeStartElement("variable");
        stream.writeTextElement("name",var->getVarName());
        if(var->getCanType()==ModbusVar::CAN_MB) stream.writeTextElement("canal","MB");
        else if(var->getCanType()==ModbusVar::CAN_PC) stream.writeTextElement("canal","PC");
        stream.writeTextElement("netAddress",QString::number(var->getNetAddr()));
        if(var->getMemType()==ModbusVar::INPUTS) stream.writeTextElement("memType",dinputsName);
        else if(var->getMemType()==ModbusVar::COILS) stream.writeTextElement("memType",coilsName);
        else if(var->getMemType()==ModbusVar::HOLD_REG) stream.writeTextElement("memType",holdRegsName);
        else if(var->getMemType()==ModbusVar::INP_REG) stream.writeTextElement("memType",inpregsName);
        stream.writeTextElement("memAddress",QString::number(var->getMemAddr()));
        stream.writeTextElement("mode",var->getWriteFlag()?"write":"read");
        stream.writeTextElement("permission",var->getActiv()?"enable":"disable");
        stream.writeTextElement("comment",var->getComment());
        stream.writeEndElement();
    }
    stream.writeEndElement(); // modbus variables

    stream.writeEndDocument();
    return false;
}

bool ModbusVarsStorage::openStorage(const QString &fullFileName)
{
    QDomDocument doc("modbusVariables");
    QFile file(fullFileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!doc.setContent(&file)) {
        file.close();
        return false;
    }
    file.close();

    QDomElement documentElement = doc.documentElement();
    maxLength = documentElement.attribute("maxLength").toInt();
    maxSpaceLength = documentElement.attribute("maxSpaceLength").toInt();
    delay = documentElement.attribute("delay").toInt();
    QDomNodeList elements = documentElement.elementsByTagName( "variable" );
    for(int i=0;i<elements.count();++i) {
        QDomNode n = elements.at(i).firstChild();
        ModbusVar var("");
        while(!n.isNull()) {
            if(n.isElement()) {
                QDomElement e = n.toElement();
                QString name = e.tagName();
                QString value = e.firstChild().toText().data();

                if(name=="name") var.setVarName(value);
                if(name=="canal") {
                    QString cType = value;
                    if(cType=="MB") var.setCanType(ModbusVar::CAN_MB);
                    else if(cType=="PC") var.setCanType(ModbusVar::CAN_PC);
                }
                if(name=="netAddress") var.setNetAddr(value.toInt());
                if(name=="memType") {
                    QString mType = value;
                    if(mType==dinputsName) var.setMemType(ModbusVar::INPUTS);
                    else if(mType==coilsName) var.setMemType(ModbusVar::COILS);
                    else if(mType==holdRegsName) var.setMemType(ModbusVar::HOLD_REG);
                    else if(mType==inpregsName) var.setMemType(ModbusVar::INP_REG);
                }
                if(name=="memAddress") var.setMemAddr(value.toInt());
                if(name=="mode") var.setWriteFlag(value=="write");
                if(name=="permission") var.setActiv(value=="enable");
                if(name=="comment") var.setComment(value);
            }
            n = n.nextSibling();
        }
        if(!var.getVarName().isEmpty()) addModbusVar(var);
    }
    return false;
}

void ModbusVarsStorage::enableAll()
{
    for(auto &var:vars) {
        var->setActiv(true);
    }
}

void ModbusVarsStorage::disableAll()
{
    for(auto &var:vars) {
        var->setActiv(false);
    }
}

void ModbusVarsStorage::setMaxSpaceLength(int value)
{
    maxSpaceLength = value;
}

void ModbusVarsStorage::setMaxLength(int value)
{
    maxLength = value;
}

}
