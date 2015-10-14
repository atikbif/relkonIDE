#ifndef CCODECREATOR_H
#define CCODECREATOR_H

// генерирует текст, отвечающий за вывод содержимого пульта
// для файла fc_u.c (включая переменные)

#include "display.h"
#include <QStringList>
#include "pultvardefinition.h"

class CCodeCreator
{
    static void printData(const Display &d, QStringList &code); // формирование текстового содержимого пульта
    static quint8 getVarType(const QString &vType); // вернуть цифровой код типа данных переменной
    static void correctVarPos(const Display &d, QString &pattern, int &pos); // учёт влияния знакоместа в шаблоне на позицию переменной
    static int getFractionLength(const QString &pattern);   // вернуть длину дробной части
    static void removeComma(QString &pattern);  // удалить запятую из шаблона
    static QString printFloatVar(const QString &name,int str, int pos, int length, int frLength);  // вывод переменной float
    static QString printEditEEVar(int eePosInTable, int str, int pos, int length, int frLength, int vType); // вывод редактируемой уставки
    static QString printTimeVar(const QString &name, int str, int pos); // переменная для вывода времени или даты
    static QString printPlainEditVar(const QString &name, int str, int pos, int length, int frLength, int vType);   // обычная переменная с возможностью редактирования
    static QString printLongVar(const QString &name, int str, int pos, int length, int frLength);   // переменная типа long
    static QString printVar(const Display &d, const PultVarDefinition &vDef, int str); // вернуть строку с кодом вывода переменной
public:
    CCodeCreator();
    static QStringList getText(const Display& d); // вернуть результирующий код
    ~CCodeCreator();
};

#endif // CCODECREATOR_H
