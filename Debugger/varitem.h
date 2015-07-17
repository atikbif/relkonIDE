#ifndef VARITEM_H
#define VARITEM_H

// параметры переменной для отладчика
// все данные представляются в виде дерева переменных

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QStringList>

class VarItem
{
    QString dataType;   // int, char, struct, array, ...
    QString memType;        // RAM, FRAM, CLOCK, USER, ...
    int priority;       // приоритет при опросе контроллера - влияет на частоту опроса
    volatile int memAddress;
    QString name;
    QString value;      // в текстовом виде т.к. могут быть как целые значения так и с плавающей точкой
    QDateTime timeLabel;    // метка времени переменной
    int quality;        // качество связи
    volatile int bitNum;         // номер бита
    QString id;

    static const QStringList dataTypes;
    enum {BIT,CHAR,SHORT,INT,LONG,LONG_LONG,FLOAT,DOUBLE};

    QByteArray getBytesForIntegral(int varSize);
    void updateByte(int offsetValue, quint8 dataValue, QByteArray &varBytes);
    void updateID(void);
public:
    VarItem();
    const QString& getName() const {return name;}
    void setName(const QString &varName) {name=varName;updateID();}
    const QString& getDataType() const {return dataType;}
    void setDataType(const QString &value) {dataType=value;updateID();}
    int getMemAddress() const {return memAddress;}
    void setMemAddress(int value) {memAddress = value;updateID();}
    const QString& getMemType(void) const {return memType;}
    void setMemType(const QString &value) {memType=value;updateID();}
    int getBitNum(void) const {return bitNum;}
    void setBitNum(int value) {if((value>=0)&&(value<8)) bitNum=value;else bitNum=-1;updateID();}
    const QString& getID(void) const {return id;}
    const QString& getValue() {return value;}
    void setValue(const QString &newValue) {value = newValue;}
    void setPriority(int value) {priority = value;}
    int getPriority(void) const {return priority;}
    virtual ~VarItem();
};

#endif // VARITEM_H
