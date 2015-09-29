#include "vartomemconnector.h"
#include <QStringList>
#include "VarDef/compositevar.h"

VarToMemConnector::VarToMemConnector()
{

}

void VarToMemConnector::updateConnection(MemStorage &mem, IDStorage &id)
{
    QStringList ids = id.getIDs();
    CompositeVar var;
    mem.clearIDs();
    foreach (QString varID, ids) {
       if(id.getVarByID(varID,var)) {
           mem.connectCellToID(var.getMemType(),var.getMemAddress(),varID);
       }
    }
}

VarToMemConnector::~VarToMemConnector()
{

}

