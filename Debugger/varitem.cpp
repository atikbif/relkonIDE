#include "varitem.h"
#include "idgenerator.h"

const QStringList VarItem::dataTypes = {"bit","char", "short", "int", "long", "long long", "float", "double"};


bool VarItem::getReadOnly() const
{
    return readOnly;
}

void VarItem::setReadOnly(bool value)
{
    readOnly = value;
}
QByteArray VarItem::getBytesForIntegral(int varSize)
{
    qint64 tmp = value.toLongLong();
    QByteArray varBytes;
    for(int i=0;i<varSize;i++) {varBytes+=tmp&0xFF; tmp=tmp>>8;}
    return varBytes;
}

void VarItem::updateByte(int offsetValue, quint8 dataValue, QByteArray &varBytes)
{
    if((offsetValue>=0)&&(offsetValue<varBytes.count())){
        varBytes[offsetValue]=dataValue;
    }
}

void VarItem::updateID()
{
    QString str = name+memType+dataType+QString::number(memAddress)+QString::number(bitNum);
    id = IdGenerator::getID(str);
}

VarItem::VarItem()
{
    bitNum = -1;
    readOnly = false;
}

VarItem::~VarItem()
{

}

/*void VarItem::dataUpdate(const MemCell &cell)
{
    int varSize = 0;
    int typeNum=-1;
    for(int i=0;i<dataTypes.count();i++) {
       if(dataType==dataTypes.at(i).toLower()){
           typeNum = i;
           break;
       }
    }

    QByteArray varBytes;
    int cellOffset = cell.getAddress()-memAddress;

    switch(typeNum) {
    case BIT:
        varBytes = getBytesForIntegral(1);
        updateByte(cellOffset,cell.getValue(),varBytes);
        if(varBytes.at(0)&(1<<bitNum)) value="1";else value="0";
        break;
    case CHAR:{
        varBytes = getBytesForIntegral(1);
        updateByte(cellOffset,cell.getValue(),varBytes);
        long long result = *(reinterpret_cast<quint8*>(varBytes.data()));
        if(!dataType.toLower().contains("unsigned")) result = (qint8)result;
        value = QString::number(result);}
        break;
    case SHORT:{
        varBytes = getBytesForIntegral(2);
        updateByte(cellOffset,cell.getValue(),varBytes);
        long long result = *(reinterpret_cast<quint16*>(varBytes.data()));
        if(!dataType.toLower().contains("unsigned")) result = (qint16)result;
        value = QString::number(result);}
        break;
    case INT:{
        varBytes = getBytesForIntegral(4);
        updateByte(cellOffset,cell.getValue(),varBytes);
        long long result = *(reinterpret_cast<quint32*>(varBytes.data()));
        if(!dataType.toLower().contains("unsigned")) result = (qint32)result;
        value = QString::number(result);}
        break;
    case LONG:{
        varBytes = getBytesForIntegral(4);
        updateByte(cellOffset,cell.getValue(),varBytes);
        long long result = *(reinterpret_cast<quint32*>(varBytes.data()));
        if(!dataType.toLower().contains("unsigned")) result = (qint32)result;
        value = QString::number(result);}
        break;
    case LONG_LONG:{
        varBytes = getBytesForIntegral(8);
        updateByte(cellOffset,cell.getValue(),varBytes);
        long long result = *(reinterpret_cast<quint64*>(varBytes.data()));
        if(!dataType.toLower().contains("unsigned")) result = (qint64)result;
        value = QString::number(result);}
        break;
    case FLOAT:{
        varSize=4;
        float tmp;
        tmp = value.toFloat();
        varBytes.append(reinterpret_cast<const char*>(&tmp), varSize);
        updateByte(cellOffset,cell.getValue(),varBytes);
        tmp = *(reinterpret_cast<float*>(varBytes.data()));
        value = QString::number(tmp);}
        break;
    case DOUBLE:{
        varSize=8;
        double tmp;
        tmp = value.toDouble();
        varBytes.append(reinterpret_cast<const char*>(&tmp), varSize);
        updateByte(cellOffset,cell.getValue(),varBytes);
        tmp = *(reinterpret_cast<double*>(varBytes.data()));
        value = QString::number(tmp);}
        break;
    }
    timeLabel = cell.getCellTime();
    quality = cell.getQuality();
}*/

