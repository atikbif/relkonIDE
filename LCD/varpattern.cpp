#include "varpattern.h"
#include <QRegExp>
#include "VarDef/varitem.h"

VarPattern::VarPattern()
{

}

bool VarPattern::checkPattern(const QString &pattern, const QString& dataType)
{
    const int maxLength = 7;
    if(pattern.isEmpty()) return false;
    if(pattern.contains(" ")) return false;
    QRegExp rExp("^[-+]?\\d+[\\.,]?\\d*$");
    if(rExp.indexIn(pattern,0)!=-1) {
        QString edPattern = pattern;
        edPattern.replace(',','.');
        bool dConvRes = false;
        edPattern.toDouble(&dConvRes);
        edPattern.remove(QRegExp("[\\.+]"));
        if(edPattern.length()>maxLength) return false;
        bool lConvRes = false;
        qlonglong lValue = edPattern.toLongLong(&lConvRes);
        if(dataType==VarItem::ucharType) {
            if(!lConvRes) return false;
            if((lValue>=-128)&&(lValue<=255)) return true;
        }else if(dataType==VarItem::charType) {
            if(!lConvRes) return false;
            if((lValue>=-128)&&(lValue<=127)) return true;
        }else if(dataType==VarItem::ushortType) {
            if(!lConvRes) return false;
            if((lValue>=-32768)&&(lValue<=65535)) return true;
        }else if(dataType==VarItem::shortType) {
            if(!lConvRes) return false;
            if((lValue>=-32768)&&(lValue<=32767)) return true;
        }else if(dataType==VarItem::uintType) {
            if(!lConvRes) return false;
            if((lValue>=-2147483648l)&&(lValue<=4294967295ul)) return true;
        }else if(dataType==VarItem::intType) {
            if(!lConvRes) return false;
            if((lValue>=-2147483648l)&&(lValue<=2147483647l)) return true;
        }else if(dataType==VarItem::ulongType) {
            if(!lConvRes) return false;
            if((lValue>=-2147483648l)&&(lValue<=4294967295ul)) return true;
        }else if(dataType==VarItem::longType) {
            if(!lConvRes) return false;
            if((lValue>=-2147483648l)&&(lValue<=2147483647l)) return true;
        }else if(dataType==VarItem::longLongType) {
            if(!lConvRes) return false;
            return true;
        }else if(dataType==VarItem::floatType) {
            if(dConvRes) return true;
        }else if(dataType==VarItem::doubleType) {
            if(dConvRes) return true;
        }
    }
    return false;
}

VarPattern::~VarPattern()
{

}

