#include "anio.h"


QString AnIO::getName() const
{
    return name;
}

void AnIO::setName(const QString &value)
{
    name = value;
}

int AnIO::getAddress() const
{
    return address;
}

void AnIO::setAddress(int value)
{
    address = value;
}

QLineEdit *AnIO::getLcdNum() const
{
    return lcdNum;
}

void AnIO::setLcdNum(QLineEdit *value)
{
    lcdNum = value;
}

QLineEdit *AnIO::getComment() const
{
    return comment;
}

void AnIO::setComment(QLineEdit *value)
{
    comment = value;
}

QSlider *AnIO::getSlider() const
{
    return slider;
}

void AnIO::setSlider(QSlider *value)
{
    slider = value;
}

AnIO::AnIO():name(""),address(0),lcdNum(nullptr),comment(nullptr),slider(nullptr)
{

}

AnIO::~AnIO()
{

}

