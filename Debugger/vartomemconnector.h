#ifndef VARTOMEMCONNECTOR_H
#define VARTOMEMCONNECTOR_H

// установить/обновить связь ячеек памяти и идентификаторов переменных

#include "VarDef/idstorage.h"
#include "VarDef/varitem.h"
#include "memstorage.h"

class VarToMemConnector
{
public:
    VarToMemConnector();
    static void updateConnection(MemStorage &mem, IDStorage &id);
    ~VarToMemConnector();
};

#endif // VARTOMEMCONNECTOR_H
