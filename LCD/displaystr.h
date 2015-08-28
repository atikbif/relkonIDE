#ifndef DISPLAYSTR_H
#define DISPLAYSTR_H

// класс строки дисплея

#include <QByteArray>
#include "varpattern.h"
#include <QVector>
#include <QMutexLocker>

class DisplayStr
{
    struct vPatt{
        int pos;
        VarPattern variable;
        vPatt(int vPos, const VarPattern &v):pos(vPos),variable(v)
        {

        }
    };
    QVector<vPatt*> vList;  // список переменных
    static const int length=20; // длина строки
    static const quint8 spaceCode = 0x20;
    QByteArray data;
    bool replaceMode;
    mutable QMutex mutex;   // для поддержки работы в многопоточном приложении
public:
    DisplayStr();
    static int getLength(void) {return length;}
    ~DisplayStr();
    bool getReplaceMode() const;
    int getSymbol(int pos) const;
    const QByteArray getString(void) const {QMutexLocker locker(&mutex);return data;}
    bool insertSymbol(int pos, quint8 code);
    void deleteSymbol(int pos);
    void setReplaceMode(bool value);
    bool addVar(const VarPattern& vP, int pos);
};

#endif // DISPLAYSTR_H
