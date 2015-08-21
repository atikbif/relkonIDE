#include "debuggersettings.h"


int DebuggerSettings::getNetAddress() const
{
    return netAddress;
}

void DebuggerSettings::setNetAddress(int value)
{
    netAddress = value;
}
DebuggerSettings::DebuggerSettings()
{
    udpSettings.portNum = defaultUDPPortNum;
}

DebuggerSettings::~DebuggerSettings()
{

}

