#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QWidget>
#include <QByteArray>

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

    virtual void updateData(void)=0;    // обновление GUI
    virtual void writeToBin(QByteArray &outData)=0; // запись настроек в бинарный массив


public:
    explicit SettingsBase(QWidget *parent = 0);
    ~SettingsBase();
    unsigned char getProgAddr(void) const {return progAddr;}
    virtual void clearSettings(void);
    void setKonFileName(const QString &fName) {konFileName=fName;}
    virtual void saveSettings(void)=0;  // сохранение настроек в файл
    virtual void openSettings(void)=0;  // чтение настроек из файла
    void updateOnyByte(int addr,quint8 value);
    virtual void updateTable(void);

signals:
    void writeToPLC(QByteArray binData);    // запрос записи данных в ПЛК
    void readFromPLC(void); // запрос чтения данных их ПЛК (результат ожидается в слоте readFromBin)
public slots:
    virtual void readFromBin(const QByteArray inpData)=0;   // чтение настрое из бинарного массива
    virtual void writeSysFram(void) {}
    virtual void readSysFram(void) {}
};

#endif // SETTINGSBASE_H
