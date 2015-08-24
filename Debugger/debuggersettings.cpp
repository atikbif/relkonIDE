#include "debuggersettings.h"


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

DebuggerSettings::DebuggerSettings():line(COM),netAddress(1)
{
    udpSettings.portNum = defaultUDPPortNum;
    comSettings.baudrate = 115200;
    comSettings.portName = "COM1";
    comSettings.protocol = "BIN";
}

DebuggerSettings::~DebuggerSettings()
{

}

