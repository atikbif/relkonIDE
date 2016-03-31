#ifndef BITIO_H
#define BITIO_H

// класс описания дискретного значения

#include <QPushButton>
#include <QLineEdit>

class BitIO
{
    QPushButton *button;    // кнопка, привязанная к элементу
    QLineEdit *comment;
    int bitNum;     // номер бита
    QString name;
    int address;    // адрес байта
    bool state;     // состояние (вкл/выкл)
public:
    // расположение в памяти (стартовые адреса)
    static const int inputStartAddress = 0x00;  // IN0..IN3,DIN4,DIN5
    static const int outputStartAddress = 0x06; // OUT0..OUT3,DOUT4,DOUT5
    static const int mmbInputStartAddress = 0x24;   // IN4...
    static const int mmbOutputStartAddress = 0x44;  // OUT4...
    BitIO();
    ~BitIO();
    QPushButton *getButton() const;
    void setButton(QPushButton *value);
    QLineEdit *getComment() const;
    void setComment(QLineEdit *value);
    int getBitNum() const;
    void setBitNum(int value);
    QString getName() const;
    void setName(const QString &value);
    int getAddress() const;
    void setAddress(int value);
    bool getState() const;
    void setState(bool value);
};

#endif // BITIO_H
