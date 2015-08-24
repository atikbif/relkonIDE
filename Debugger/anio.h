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
    QSlider *slider;    // указатель на виджет для изменения знчения

public:
    static const int inputStartAddress = 0x0C;
    static const int outputStartAddress = 0x1C;
    static const int mmbInputStartAddress = 0x64;
    static const int mmbOutputStartAddress = 0x164;
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
