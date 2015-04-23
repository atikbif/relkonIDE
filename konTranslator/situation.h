#ifndef SITUATION_H
#define SITUATION_H

// класс, описывающий процесс в теле kon файла

#include "textblock.h"

class Situation: public TextBlock
{
    int processNum=1;
    int period=100;
    int sitNum=1;
public:
    explicit Situation(int num=1);
    void setPeriod(int value);  // установить гарантированное время выполнения в мс
    int getPeriod(void) const;
    void setPocessNum(int value);   // установить номер процесса-владельца ситуации
    int getProcessNum(void) const;
    int getSitNum(void) const {return sitNum;}
};

#endif // SITUATION_H
