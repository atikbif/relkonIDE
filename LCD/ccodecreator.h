#ifndef CCODECREATOR_H
#define CCODECREATOR_H

#include "display.h"
#include <QStringList>
#include "VarDef/varitem.h"

class CCodeCreator
{
public:
    CCodeCreator();
    static QStringList getText(const Display& d);
    ~CCodeCreator();
};

#endif // CCODECREATOR_H
