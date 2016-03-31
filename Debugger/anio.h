#ifndef ANIO_H
#define ANIO_H

// класс описания аналогового входа/выхода

#include <QString>
#include <QLineEdit>
#include <QSlider>

class AnIO
{
    QString name;   // имя входа
    int address;    // адрес в памяти
    QLineEdit *lcdNum;  // указатель на виджет с отображаемым значением
    QLineEdit *comment; // указатель на виджет с комментарием
    QSlider *slider;    // указатель на виджет для изменения значения

public:
    // расположение в памяти (стартовые адреса)
    static const int inputStartAddress = 0x0C;  // ADC1..ADC8
    static const int i2cInputStartAddress = 0x1E4;  // ADC201..ADC208
    static const int outputStartAddress = 0x1C; // DAC1..DAC4
    static const int mmbInputStartAddress = 0x64;   // ADC9...
    static const int mmbOutputStartAddress = 0x164; // DAC5...
    AnIO();
    ~AnIO();
    QString getName() const;
    void setName(const QString &value);
    int getAddress() const;
    void setAddress(int value);
    QLineEdit *getLcdNum() const;
    void setLcdNum(QLineEdit *value);
    QLineEdit *getComment() const;
    void setComment(QLineEdit *value);
    QSlider *getSlider() const;
    void setSlider(QSlider *value);
};

#endif // ANIO_H
