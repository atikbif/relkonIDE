#ifndef VARPATTERN_H
#define VARPATTERN_H

// класс с информацией о шаблоне вывода переменной на дисплей

#include <QString>

class VarPattern
{
public:
    VarPattern();
    static bool checkPattern(const QString& pattern, const QString& dataType);    // проверяет корректность шаблона
    ~VarPattern();
};

#endif // VARPATTERN_H
