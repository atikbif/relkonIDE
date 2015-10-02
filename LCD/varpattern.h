#ifndef VARPATTERN_H
#define VARPATTERN_H

// класс с информацией о шаблоне вывода переменной на дисплей

#include <QString>

class VarPattern
{
    QString varId;  // идентификатор переменной
    QString pattern;    // шаблон отображения
public:
    explicit VarPattern(const QString &vID, const QString &vPattern);
    bool checkPattern(const QString& dataType) const;    // проверяет корректность шаблона
    int getLength(void) const {return pattern.length();}    // возвращает длину шаблона
    QString getVarID(void) const {return varId;}
    QString getPattern(void) const {return pattern;}
    ~VarPattern();
};

#endif // VARPATTERN_H
