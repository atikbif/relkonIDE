#include "situation.h"

Situation::Situation(int num) : TextBlock()
{
    sitNum = num;
}

void Situation::setPeriod(int value)
{
    period = value;
}

int Situation::getPeriod() const
{
    return period;
}

void Situation::setPocessNum(int value)
{
    processNum = value;
}

int Situation::getProcessNum() const
{
    return processNum;
}
