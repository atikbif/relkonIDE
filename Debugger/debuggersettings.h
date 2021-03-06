#ifndef DEBUGGERSETTINGS_H
#define DEBUGGERSETTINGS_H

// класс для хранения настроек отладчика

#include <QString>

enum canType{COM,UDP};

struct comData
{
    QString portName;
    long baudrate;
    QString protocol;
};

struct udpData
{
    QString ipAddress;
    int portNum;
};

class DebuggerSettings
{
    canType line;
    comData comSettings;
    udpData udpSettings;
    int netAddress;
    static const int defaultUDPPortNum = 12144;
    bool udpFlag;
public:
    DebuggerSettings();
    const comData getComSettings(void) const {return comSettings;}
    const udpData getUdpSettings(void) const {return udpSettings;}
    void setPortName(const QString &pName) {comSettings.portName = pName;}
    void setBaudrate(int value) {comSettings.baudrate = value;}
    void setProtocol(const QString &protocol) {comSettings.protocol = protocol;}
    void setIpAddress(const QString &addr);
    ~DebuggerSettings();
    int getNetAddress() const;
    void setNetAddress(int value);
    bool getUdpFlag() const;
    void setUdpFlag(bool value);
    static int getDefaultUDPPortNum();
};

#endif // DEBUGGERSETTINGS_H
