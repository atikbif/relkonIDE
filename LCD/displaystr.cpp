#include "displaystr.h"

bool DisplayStr::replaceMode = false;

bool DisplayStr::getReplaceMode()
{
    return replaceMode;
}

int DisplayStr::getSymbol(int pos) const
{
    QMutexLocker locker(&mutex);
    quint8 res = 0;
    if((pos>=0)&&(pos<length)) res = data.at(pos);
    return res;
}

bool DisplayStr::insertSymbol(int pos,quint8 code)
{
    QMutexLocker locker(&mutex);
    bool result=false;
    if((pos<0)||(pos>=length)) return false;
    if((isVarHere(pos))&&(!isThisABeginningOfVar(pos))) {
        if(!replaceMode) {
            pos++;
            return true;
        }
        return false;
    }
    if(replaceMode) {
        if(isVarHere(pos)) return false;
        data.remove(pos,1);
        data.insert(pos,code);
        result = true;
    }else {
        if(data.at(length-1)==0x20) {
            data.insert(pos,code);
            foreach (vPatt* v, vList) {
               if(v->pos >= pos) v->pos++;
            }
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

    if(isVarHere(pos)) {
        vPatt* vp = nullptr;
        foreach (vPatt* v, vList) {
           if((pos >= v->pos)&&(pos < v->pos + v->variable.getLength())) vp = v;
        }
        if(vp!=nullptr) {
            data.remove(vp->pos,vp->variable.getLength());
            data.append(QByteArray(vp->variable.getLength(),spaceCode));
            vList.removeOne(vp);
            foreach (vPatt* v, vList) {
               if(v->pos >= vp->pos) v->pos-=vp->variable.getLength();
            }
        }
        return;
    }

    data.remove(pos,1);
    foreach (vPatt* v, vList) {
       if(v->pos>pos) v->pos--;
    }
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
        if(isVarHere(pos)) return false;
        // check free space
        int i = length - 1;
        int spaceCnt = 0;
        while(i>=0) {if(data.at(i)==0x20) spaceCnt++;else break;i--;}
        if(spaceCnt<vP.getLength()) return false;
        foreach (vPatt* v, vList) {
           if(v->pos>pos) v->pos+=vP.getLength();
        }
    }else {
        for(int i=pos;i<=endPos;i++) {
            if(isVarHere(i)) return false;
        }
        data.remove(pos,vP.getLength());
    }
    data.insert(pos,vP.getPattern());
    data.resize(length);
    vPatt* var = new vPatt(pos,vP);
    vList += var;
    return true;
}

bool DisplayStr::updVar(const VarPattern &vP, int pos)
{
    QMutexLocker locker(&mutex);
    vPatt* curPattern = nullptr;
    foreach (vPatt* v, vList) {
        if((pos>=v->pos)&&(pos < v->pos + v->variable.getLength())) {
            curPattern = v;
            break;
        }
    }
    if(curPattern==nullptr) return false;
    if(vP.getLength()>curPattern->variable.getLength()) {
        // check free space
        int i = length - 1;
        int spaceCnt = 0;
        while(i>=0) {if(data.at(i)==0x20) spaceCnt++;else break;i--;}
        if(spaceCnt<vP.getLength()-curPattern->variable.getLength()) return false;
    }
    int offset = vP.getLength() - curPattern->variable.getLength();
    foreach (vPatt* v, vList) {
       if(v->pos>curPattern->pos) v->pos+=offset;
    }
    vList.removeOne(curPattern);
    data.remove(curPattern->pos,curPattern->variable.getLength());
    data.insert(curPattern->pos,vP.getPattern());
    if(data.count()>length) data.resize(length);
    else while(data.count()<length) data.append(spaceCode);
    curPattern = new vPatt(curPattern->pos,vP);
    vList += curPattern;
    return true;
}

bool DisplayStr::getVar(int num, vPatt &v) const
{
    if((num<0)||(num>=getVarsCount())) return false;
    v.pos = vList.at(num)->pos;
    v.variable = vList.at(num)->variable;
    return true;
}

QString DisplayStr::getVarID(int pos) const
{
    foreach (vPatt* v, vList) {
       if((pos >= v->pos)&&(pos < v->pos+ v->variable.getLength()))
           return v->variable.getVarID();
    }
    return QString();
}

QString DisplayStr::getVarPatern(int pos) const
{
    foreach (vPatt* v, vList) {
       if((pos >= v->pos)&&(pos < v->pos+ v->variable.getLength()))
           return v->variable.getPattern();
    }
    return QString();
}

bool DisplayStr::isVarHere(int pos) const
{
    foreach (vPatt* v, vList) {
       if((pos >= v->pos)&&(pos < v->pos+ v->variable.getLength())) return true;
    }
    return false;
}

bool DisplayStr::isThisABeginningOfVar(int pos) const
{
    foreach (vPatt* v, vList) {
       if(pos == v->pos) return true;
    }
    return false;
}

DisplayStr::DisplayStr():active(true)
{
    data.fill(spaceCode,length);
}

DisplayStr::DisplayStr(const DisplayStr &s)
{
    foreach (vPatt* ptr, vList) {delete ptr;}
    vList.clear();
    for(int i=0;i<s.getVarsCount();i++) {
        vPatt v;
        s.getVar(i,v);
        vPatt* copyPattern = new vPatt(v);
        vList += copyPattern;
    }
    data = s.getString();
    active = s.isActive();
}

DisplayStr &DisplayStr::operator=(const DisplayStr &s)
{
    if (this != &s) {
        foreach (vPatt* ptr, vList) {delete ptr;}
        vList.clear();
        for(int i=0;i<s.getVarsCount();i++) {
            vPatt v;
            s.getVar(i,v);
            vPatt* copyPattern = new vPatt(v);
            vList += copyPattern;
        }
        data = s.getString();
        active = s.isActive();
    }
    return *this;
}

DisplayStr::~DisplayStr()
{
    foreach (vPatt* ptr, vList) {
       delete ptr;
    }
}

