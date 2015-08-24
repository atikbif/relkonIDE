#ifndef BITIO_H
#define BITIO_H

#include <QPushButton>
#include <QLineEdit>

class BitIO
{
    QPushButton *button;
    QLineEdit *comment;
    int bitNum;
    QString name;
    int address;
    bool state;
public:
    static const int inputStartAddress = 0x00;
    static const int outputStartAddress = 0x06;
    static const int mmbInputStartAddress = 0x24;
    static const int mmbOutputStartAddress = 0x44;
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
