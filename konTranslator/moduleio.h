#ifndef MODULEIO_H
#define MODULEIO_H

// класс модуля ввода/вывода Matchbox

#include <QString>

class ModuleIO
{
public:
    enum speedPriority {HIGH_PRIORITY,NORMAL_PRIORITY,LOW_PRIORITY}; // скорость опроса
    enum dataType {MDI,MDO,MAI,MAO}; // тип модуля
    explicit ModuleIO(dataType type=MDI);
    void setSpeed(speedPriority speed);
    speedPriority getSpeed(void) const;
    void setNetAddress(int value);
    void setNetAddress(const QString &modName); // установка адреса по названию модуля
    int getNetAddress(void) const;
    static int getInStart(void) {return 1;}    // the first net address in input matchbox group
    static int getInEnd(void) {return 64;}     // the last
    static int getOutStart(void) {return 65;}
    static int getOutEnd(void) {return 128;}
    static int getAdcStart(void) {return 129;}
    static int getAdcEnd(void) {return 160;}
    static int getDacStart(void) {return 161;}
private:
    speedPriority speed;
    dataType type;
    int netAddress; // сетевой адрес модуля
};

#endif // MODULEIO_H
