#include "settingsbase.h"

void SettingsBase::clearSettings()
{
    for(int i=0;i<factorySettingsAmount;i++) fSettings[i]=0;
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
}

SettingsBase::SettingsBase(QWidget *parent) : QWidget(parent)
{
    clearSettings();
}

SettingsBase::~SettingsBase()
{

}

