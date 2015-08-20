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
