#include "settingsbase.h"
#include "pathstorage.h"
#include <QDomDocument>
#include <QFile>

void SettingsBase::clearSettings()
{
    for(int i=0;i<factorySettingsAmount;i++) fSettings[i]=0xFF;
    netAddress=0x01;
    progAddr=0x00;
    ipAddr[0]=192;ipAddr[1]=168;ipAddr[2]=0;ipAddr[3]=31;
    macAddr[0]=0x86;macAddr[1]=0x50;macAddr[2]=0xB2;
    macAddr[3]=0xDB;macAddr[4]=0xD7;macAddr[5]=0x5F;
    prUart.protocol = BIN; prUart.speed = 115200;
    pcUart.protocol = BIN; pcUart.speed = 115200;
    emulation = NoEmulation;
    displayOn = false;
    sdOn = false;
    plcType = "PC365C";
    readPLCTypes();
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

SettingsBase::SettingsBase(QWidget *parent) : QWidget(parent)
{
    clearSettings();
}

SettingsBase::~SettingsBase()
{

}

