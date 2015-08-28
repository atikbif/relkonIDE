#ifndef DISPLAYSTR_H
#define DISPLAYSTR_H

// класс строки дисплея

#include <QByteArray>

class DisplayStr
{
    static const int length=20; // длина строки
    QByteArray data;
public:
    DisplayStr();
    static int getLength(void) {return length;}
    ~DisplayStr();
};

#endif // DISPLAYSTR_H
