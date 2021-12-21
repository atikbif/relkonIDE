#include "settingsbase.h"
#include "pathstorage.h"
#include <QDomDocument>
#include <QFile>
#include "plcutils.h"

void SettingsBase::clearSettings()
{
    for(int i=0;i<factorySettingsAmount;i++) fSettings[i]=0xFF;
    netAddress=0x01;
    progAddr=0x00;
    ipAddr[0]=192;ipAddr[1]=168;ipAddr[2]=0;ipAddr[3]=31;
    ipGate[0]=192;ipGate[1]=168;ipGate[2]=0;ipGate[3]=1;
    ipMask[0]=255;ipMask[1]=255;ipMask[2]=255;ipMask[3]=0;
    prDef = "новый проект";
    macAddr[0]=0x86;macAddr[1]=0x50;macAddr[2]=0xB2;
    macAddr[3]=0xDB;macAddr[4]=0xD7;macAddr[5]=0x5F;
    prUart.protocol = BIN; prUart.speed = 115200;
    pcUart.protocol = BIN; pcUart.speed = 115200;
    emulation = NoEmulation;
    displayOn = false;
    sdOn = false;
    plcType = PLCUtils::defaultPLCName;
    modbusMaster = false;
    readPLCTypes();
    eMemSize = 10;
    modbMasterEmuMode = false;
    emit emuModeChanged(NoEmulation);
}

void SettingsBase::updateOnyByte(int addr, quint8 value)
{
    if((addr>=0)&&(addr<factorySettingsAmount)) fSettings[addr] = value;
}

void SettingsBase::updateTable()
{

}

QString SettingsBase::getBuildName()
{
    return plcBuilds.value(plcType);
}

QString SettingsBase::getIP() const
{
    return QString::number(ipAddr[0])+"."+QString::number(ipAddr[1])+"."+QString::number(ipAddr[2])+"."+QString::number(ipAddr[3]);
}

void SettingsBase::readPLCTypes()
{
    QDomDocument doc("plc");
    QString fName = PathStorage::getPLCListFileFullName();
    QFile file(fName);
    if (!file.open(QIODevice::ReadOnly)) return;
    if (!doc.setContent(&file)) {
        return;
    }

    QDomNodeList controllers = doc.elementsByTagName("plc");
    for(int i=0;i<controllers.count();i++) {
        QDomNode n = controllers.item(i);
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            QString plcName = e.attribute("name");
            QString plcBuild = e.attribute("build");
            plcBuilds.insert(plcName,plcBuild);
        }
    }

}

SettingsBase::SettingsBase(QWidget *parent) : QWidget(parent),eMemSize(10)
{
    clearSettings();
}

SettingsBase::~SettingsBase()
{

}

