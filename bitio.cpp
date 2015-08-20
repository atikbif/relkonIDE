#include "bitio.h"


QPushButton *BitIO::getButton() const
{
    return button;
}

void BitIO::setButton(QPushButton *value)
{
    button = value;
}

QLineEdit *BitIO::getComment() const
{
    return comment;
}

void BitIO::setComment(QLineEdit *value)
{
    comment = value;
}

int BitIO::getBitNum() const
{
    return bitNum;
}

void BitIO::setBitNum(int value)
{
    bitNum = value;
}

QString BitIO::getName() const
{
    return name;
}

void BitIO::setName(const QString &value)
{
    name = value;
}

int BitIO::getAddress() const
{
    return address;
}

void BitIO::setAddress(int value)
{
    address = value;
}

bool BitIO::getState() const
{
    return state;
}

void BitIO::setState(bool value)
{
    state = value;
}
BitIO::BitIO()
{
    
}

BitIO::~BitIO()
{
    
}

