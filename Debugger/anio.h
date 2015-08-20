#ifndef ANIO_H
#define ANIO_H

#include <QString>
#include <QLCDNumber>
#include <QLineEdit>
#include <QSlider>

class AnIO
{
    QString name;
    int address;
    //QLCDNumber *lcdNum;
    QLineEdit *lcdNum;
    QLineEdit *comment;
    QSlider *slider;
    int value;

public:
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
    int getValue() const;
    void setValue(int value);
};

#endif // ANIO_H
