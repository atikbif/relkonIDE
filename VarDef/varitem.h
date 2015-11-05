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
    QString comment;
    QString value;      // в текстовом виде т.к. могут быть как целые значения так и с плавающей точкой
    volatile int bitNum;         // номер бита (-1 если переменная не битовая)
    QString id;     // идентификатор переменной
    bool isEdit;  // доступна для редактирования
    bool forceSign; // принудительная знаковость
    void updateID(void);

public:
    // названия типов
    static const QString charType;
    static const QString ucharType;
    static const QString shortType;
    static const QString ushortType;
    static const QString intType;
    static const QString uintType;
    static const QString longType;
    static const QString ulongType;
    static const QString longLongType;
    static const QString floatType;
    static const QString doubleType;
    static const QString timeType;

    static QString getNameFromID(const QString &id);
    static QString getMemTypeFromID(const QString &id);
    static QString getVarTypeFromID(const QString &id);
    static int getMemAddressFromID(const QString &id);
    static int getBitNumFromID(const QString &id);

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
    const QString& getValue() const {return value;}
    void setValue(const QString &newValue) {value = newValue;}
    void setPriority(int value) {priority = value;}
    int getPriority(void) const {return priority;}
    virtual ~VarItem();
    bool isEditable() const;
    void setEditable(bool value);
    void setComment(const QString& value) {comment = value;}
    QString getComment(void) const {return comment;}
    bool isSigned(void) const {return forceSign;}
    void setSigned(bool value) {forceSign = value;}
    int getByteCount(void) const;
};

#endif // VARITEM_H
