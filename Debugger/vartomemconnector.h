#ifndef VARTOMEMCONNECTOR_H
#define VARTOMEMCONNECTOR_H

#include "idstorage.h"
#include "varitem.h"
#include "memstorage.h"

class VarToMemConnector
{
public:
    VarToMemConnector();
    static void updateConnection(MemStorage &mem, IDStorage &id);
    ~VarToMemConnector();
};

#endif // VARTOMEMCONNECTOR_H
