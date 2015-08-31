#include "displaystr.h"

bool DisplayStr::replaceMode = false;

bool DisplayStr::getReplaceMode()
{
    return replaceMode;
}

int DisplayStr::getSymbol(int pos) const
{
    QMutexLocker locker(&mutex);
    int res = 0;
    if((pos>=0)&&(pos<length)) res = data.at(pos);
    return res;
}

bool DisplayStr::insertSymbol(int pos,quint8 code)
{
    QMutexLocker locker(&mutex);
    bool result=false;
    if((pos<0)||(pos>=length)) return false;

    if(replaceMode) {
        data.remove(pos,1);
        data.insert(pos,code);
        result = true;
    }else {
        if(data.at(length-1)==0x20) {
            data.insert(pos,code);
            result = true;
        }
    }
    data.resize(length);
    return result;
}

void DisplayStr::deleteSymbol(int pos)
{
    QMutexLocker locker(&mutex);
    if((pos<0)||(pos>=length)) return;
    data.remove(pos,1);
    data.append(spaceCode);
}

void DisplayStr::setReplaceMode(bool value)
{
    replaceMode = value;
}

bool DisplayStr::addVar(const VarPattern &vP, int pos)
{
    QMutexLocker locker(&mutex);
    int endPos = pos + vP.getLength() - 1;
    if((pos<0)||(pos>=length)) return false;
    if(endPos>=length) return false;
    if(!replaceMode) {
        // check free space
        int i = length - 1;
        int spaceCnt = 0;
        while(i>=0) {if(data.at(i)==0x20) spaceCnt++;else break;}
        if(spaceCnt<vP.getLength()) return false;
    }else {
        data.remove(pos,vP.getLength());
    }
    for(int i=0;i<vP.getLength();i++) {
        data.insert(pos,spaceCode);
    }
    data.resize(length);
    vPatt* var = new vPatt(pos,vP);
    vList += var;
    return true;
}

DisplayStr::DisplayStr():active(true)
{
    data.append(" ",length);
}

DisplayStr::DisplayStr(const DisplayStr &s)
{
    foreach (vPatt* ptr, vList) {delete ptr;}
    vList.clear();
    foreach (vPatt* ptr, s.getVars()) {
       vPatt* copyPattern = new vPatt(*ptr);
       vList += copyPattern;
    }
    data = s.getString();
}

DisplayStr &DisplayStr::operator=(const DisplayStr &s)
{
    if (this != &s) {
        foreach (vPatt* ptr, vList) {delete ptr;}
        vList.clear();
        foreach (vPatt* ptr, s.getVars()) {
           vPatt* copyPattern = new vPatt(*ptr);
           vList += copyPattern;
        }
        data = s.getString();
    }
    return *this;
}

DisplayStr::~DisplayStr()
{
    foreach (vPatt* ptr, vList) {
       delete ptr;
    }
}

