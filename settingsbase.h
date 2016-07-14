#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QWidget>
#include <QByteArray>
#include <QHash>

class SettingsBase : public QWidget
{
    Q_OBJECT

public:

    enum protocolType{BIN,ASCII};
    enum emuType{NoEmulation,InputEmulation,InputOutputEmulation};

    struct uartInfo {
        unsigned long speed;
        protocolType protocol;
    };

protected:

    const unsigned long speedTable[6] = {4800,9600,19200,38400,57600,115200};
    static const int factorySettingsAmount = 1024;


    unsigned char fSettings[factorySettingsAmount]; // заводские установки
    unsigned char netAddress;   // сетевой адрес контроллера
    unsigned char progAddr;     // адрес при поиске и программировании
    unsigned char ipAddr[4];
    unsigned char macAddr[6];
    uartInfo prUart,pcUart;
    emuType emulation;
    bool displayOn;
    bool sdOn;
    QString konFileName;
    QString plcType;
    QHash<QString,QString> plcBuilds;

    virtual void updateData(void)=0;    // обновление GUI
    virtual void writeToBin(QByteArray &outData)=0; // запись настроек в бинарный массив

    void readPLCTypes();

public:
    explicit SettingsBase(QWidget *parent = 0);
    ~SettingsBase();
    unsigned char getProgAddr(void) const {return progAddr;}
    unsigned char getNetAddr(void) const {return netAddress;}
    virtual void clearSettings(void);
    void setKonFileName(const QString &fName) {konFileName=fName;}
    virtual void saveSettings(void)=0;  // сохранение настроек в файл
    virtual void openSettings(void)=0;  // чтение настроек из файла
    quint8 getOneByte(int addr) const {if((addr>=0)&&(addr<factorySettingsAmount)) return fSettings[addr]; return 0;}
    void updateOnyByte(int addr,quint8 value);
    virtual void updateTable(void);
    static int getCount(void) {return factorySettingsAmount;}
    QString getPLCType() const {return plcType;}
    void setPLCType(const QString &value) {plcType = value;}
    QStringList getPLCNames() const {return plcBuilds.keys();}
    QString getBuildName();
    virtual void setEmuMode(emuType value)=0;
    virtual QString getPortName() const=0;

signals:
    writeToPLC(QByteArray binData);    // запрос записи данных в ПЛК
    readFromPLC(void); // запрос чтения данных их ПЛК (результат ожидается в слоте readFromBin)
    emuModeChanged(SettingsBase::emuType value);
    newPLCType(const QString &plcType);
public slots:
    virtual void readFromBin(const QByteArray inpData)=0;   // чтение настрое из бинарного массива
    virtual void writeSysFram(void) {}
    virtual void readSysFram(void) {}
};

#endif // SETTINGSBASE_H
