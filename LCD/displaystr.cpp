#include "displaystr.h"
#include <QRegExp>

bool DisplayStr::replaceMode = false;

bool DisplayStr::getReplaceMode()
{
    return replaceMode;
}

int DisplayStr::getSymbol(int pos) const
{
    QMutexLocker locker(&mutex);
    quint8 res = 0;
    if(checkPosition(pos)) res = data.at(pos);
    return res;
}

bool DisplayStr::insertSymbol(int pos,quint8 code)
{
    QMutexLocker locker(&mutex);
    bool result=false;
    if(!checkPosition(pos)) return false;
    if((isVarHere(pos))&&(!isThisABeginningOfVar(pos))) {
        if(!replaceMode) {
            // смещается курсор вправо без вставки символа
            pos++;
            return true;
        }
        return false; // в режиме замещения невозможно выполнить операцию
    }
    if(replaceMode) {
        if(isVarHere(pos)) return false;
        // заменить символ
        data.remove(pos,1);
        data.insert(pos,code);
        result = true;
    }else {
        // проверка свободного места для вставки символа со сдвигом строки
        if(data.at(length-1)==spaceCode) {
            data.insert(pos,code);
            // сдвиг всех переменных правее заданной позиции
            foreach (PultVarDefinition* v, vList) {
               if(v->getPosInStr() >= pos) v->setPosInStr(v->getPosInStr()+1);
            }
            result = true;
        }
    }
    data.resize(length);// отсечь лишние символы (сдвинутые)
    return result;
}

void DisplayStr::deleteSymbol(int pos)
{
    QMutexLocker locker(&mutex);
    if(!checkPosition(pos)) return;

    if(isVarHere(pos)) {
        PultVarDefinition* vp = nullptr;
        // поиск переменной
        foreach (PultVarDefinition* v, vList) {
           if((pos >= v->getPosInStr())&&(pos < v->getPosInStr() + v->getPattern().length())) vp = v;
        }
        if(vp!=nullptr) {
            // удаление шаблона переменной
            data.remove(vp->getPosInStr(),vp->getPattern().length());
            data.append(QByteArray(vp->getPattern().length(),spaceCode));
            // удаление переменной из списка
            vList.removeOne(vp);
            // сдвиг переменных правее заданной позиции влево
            foreach (PultVarDefinition* v, vList) {
               if(v->getPosInStr() >= vp->getPosInStr()) v->setPosInStr(v->getPosInStr()-vp->getPattern().length());
            }
            delete vp;  // очистка памяти
        }
        return;
    }
    // удалить один символ
    data.remove(pos,1);
    // сдвинуть переменные
    foreach (PultVarDefinition* v, vList) {
       if(v->getPosInStr()>pos) v->setPosInStr(v->getPosInStr()-1);
    }
    data.append(spaceCode);
}

void DisplayStr::setReplaceMode(bool value)
{
    replaceMode = value;
}

bool DisplayStr::addVar(const PultVarDefinition &vDef)
{
    QMutexLocker locker(&mutex);

    int pos = vDef.getPosInStr();
    int patternLength = vDef.getPattern().length();
    int endPos = pos + patternLength - 1;

    if(!checkPosition(pos)) return false;
    if(endPos>=length) return false;
    if(!replaceMode) {
        if(isVarHere(pos)) return false;
        // check free space
        int spaceCnt = getFreeSpace();
        if(spaceCnt<patternLength) return false;
        // сдвиг переменных, находящихся правее указанной позиции
        foreach (PultVarDefinition* vd, vList) {
           if(vd->getPosInStr() > pos) vd->setPosInStr(vd->getPosInStr()+patternLength);
        }
    }else {
        for(int i=pos;i<=endPos;i++) {
            if(isVarHere(i)) return false;
        }
        data.remove(pos,patternLength);
    }
    QString pat = vDef.getPattern();
    pat.replace(QRegExp("[\\-+]")," ");
    data.insert(pos,pat);
    data.resize(length);
    PultVarDefinition* varDef = new PultVarDefinition(vDef);
    varDef->setPosInStr(pos);
    vList += varDef;
    return true;
}

bool DisplayStr::updVar(const PultVarDefinition &vDef)
{
    QMutexLocker locker(&mutex);
    int pos = vDef.getPosInStr();
    int patternLength = vDef.getPattern().length();
    PultVarDefinition* curVarDef = nullptr;
    foreach (PultVarDefinition* vd, vList) {
        if((pos>=vd->getPosInStr())&&(pos < vd->getPosInStr() + vd->getPattern().length())) {
            curVarDef = vd;
            break;
        }
    }
    if(curVarDef==nullptr) return false;
    if(patternLength>curVarDef->getPattern().length()) {
        // check free space
        int spaceCnt = getFreeSpace();
        if(spaceCnt<patternLength-curVarDef->getPattern().length()) return false;
    }
    int offset = patternLength - curVarDef->getPattern().length();
    // смещение переменных справа при изменении длины шаблона
    if(offset!=0) foreach (PultVarDefinition* vd, vList) {
       if(vd->getPosInStr()>curVarDef->getPosInStr()) vd->setPosInStr(vd->getPosInStr()+offset);
    }
    vList.removeOne(curVarDef);
    data.remove(curVarDef->getPosInStr(),curVarDef->getPattern().length());
    QString pat=vDef.getPattern();
    pat.replace(QRegExp("[\\-+]")," ");
    data.insert(curVarDef->getPosInStr(),pat);
    if(data.count()>length) data.resize(length);
    else while(data.count()<length) data.append(spaceCode);
    pos = curVarDef->getPosInStr();
    delete curVarDef;
    curVarDef = new PultVarDefinition(vDef);
    curVarDef->setPosInStr(pos);
    vList += curVarDef;
    return true;
}

bool DisplayStr::getVar(int num, PultVarDefinition &vd) const
{
    if((num<0)||(num>=getVarsCount())) return false;
    vd = *vList.at(num);
    return true;
}

void DisplayStr::updVarDefinition(int num, PultVarDefinition &vd)
{
    if((num<0)||(num>=getVarsCount())) return;
    PultVarDefinition* ptr = vList.at(num);
    delete ptr;
    ptr = new PultVarDefinition(vd);
    vList[num] = ptr;
}

bool DisplayStr::getVarInPos(int pos, PultVarDefinition &vd) const
{
    foreach (PultVarDefinition* v, vList) {
       if((pos >= v->getPosInStr())&&(pos < v->getPosInStr()+ v->getPattern().length())) {
           vd = *v;
           return true;
       }
    }
    return false;
}

QString DisplayStr::getVarID(int pos) const
{
    foreach (PultVarDefinition* v, vList) {
       if((pos >= v->getPosInStr())&&(pos < v->getPosInStr()+ v->getPattern().length()))
           return v->getId();
    }
    return QString();
}

QString DisplayStr::getVarPatern(int pos) const
{
    foreach (PultVarDefinition* v, vList) {
       if((pos >= v->getPosInStr())&&(pos < v->getPosInStr()+ v->getPattern().length()))
           return v->getPattern();
    }
    return QString();
}

bool DisplayStr::isVarHere(int pos) const
{
    foreach (PultVarDefinition* v, vList) {
       if((pos >= v->getPosInStr())&&(pos < v->getPosInStr()+ v->getPattern().length())) return true;
    }
    return false;
}

bool DisplayStr::isThisABeginningOfVar(int pos) const
{
    foreach (PultVarDefinition* v, vList) {
       if(pos == v->getPosInStr()) return true;
    }
    return false;
}

bool DisplayStr::checkPosition(int pos)
{
    if((pos<0)||(pos>=length)) return false;
    return true;
}

int DisplayStr::getFreeSpace() const
{
    int spaceCnt = 0;
    int i = length - 1;
    while(i>=0) {if(data.at(i)==spaceCode) spaceCnt++;else break;i--;}
    return spaceCnt;
}

DisplayStr::DisplayStr():active(true)
{
    data.fill(spaceCode,length);
}

DisplayStr::DisplayStr(const DisplayStr &s)
{
    mutex.lock();
    foreach (PultVarDefinition* ptr, vList) {delete ptr;}
    vList.clear();
    for(int i=0;i<s.getVarsCount();i++) {
        PultVarDefinition v;
        s.getVar(i,v);
        PultVarDefinition* copyPattern = new PultVarDefinition(v);
        vList += copyPattern;
    }
    data = s.getString();
    active = s.isActive();
    mutex.unlock();
}

DisplayStr &DisplayStr::operator=(const DisplayStr &s)
{
    mutex.lock();
    if (this != &s) {
        foreach (PultVarDefinition* ptr, vList) {delete ptr;}
        vList.clear();
        for(int i=0;i<s.getVarsCount();i++) {
            PultVarDefinition v;
            s.getVar(i,v);
            PultVarDefinition* copyPattern = new PultVarDefinition(v);
            vList += copyPattern;
        }
        data = s.getString();
        active = s.isActive();
    }
    mutex.unlock();
    return *this;
}

DisplayStr::~DisplayStr()
{
    foreach (PultVarDefinition* ptr, vList) {
       delete ptr;
    }
}

