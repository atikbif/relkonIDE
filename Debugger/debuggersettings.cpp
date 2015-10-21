#include "debuggersettings.h"
#include <QRegExp>


int DebuggerSettings::getNetAddress() const
{
    return netAddress;
}

void DebuggerSettings::setNetAddress(int value)
{
    netAddress = value;
}

canType line;
comData comSettings;
udpData udpSettings;
int netAddress;


bool DebuggerSettings::getUdpFlag() const
{
    return udpFlag;
}

void DebuggerSettings::setUdpFlag(bool value)
{
    udpFlag = value;
}

int DebuggerSettings::getDefaultUDPPortNum()
{
    return defaultUDPPortNum;
}
DebuggerSettings::DebuggerSettings():line(COM),netAddress(1),udpFlag(false)
{
    udpSettings.portNum = defaultUDPPortNum;
    comSettings.baudrate = 115200;
    comSettings.portName = "COM1";
    comSettings.protocol = "BIN";
}

void DebuggerSettings::setIpAddress(const QString &addr)
{
    QRegExp exp("^(\\d{1,3})\\.(\\d{1,3}).(\\d{1,3}).(\\d{1,3})");
    if(exp.indexIn(addr)!=-1) {
        QString ip = QString::number(exp.cap(1).toInt()) +
                "." + QString::number(exp.cap(2).toInt()) +
                "." + QString::number(exp.cap(3).toInt()) +
                "." + QString::number(exp.cap(4).toInt());
        udpSettings.ipAddress = ip;
    }
}

DebuggerSettings::~DebuggerSettings()
{

}

