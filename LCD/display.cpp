#include "display.h"

bool Display::checkStrNum(int strNum, int subStrNum)
{
    if(subStrNum<0) return false;
    if((strNum>=0)&&(strNum<strCount)) {
        if(subStrNum<data.value(strNum).count()) return true;
    }
    return false;
}

Display::Display(QObject *parent):QObject(parent),copyStrBuf(nullptr),x(0),y(0)
{
    for(int i=0;i<strCount;i++) {
        QVector<DisplayStr*> v;
        DisplayStr* s = new DisplayStr();
        v += s;
        data.insert(i,v);
        curStr.insert(i,0);
    }
}

bool Display::setCursor(int xPos, int yPos)
{
    if((yPos<0)||(yPos>=strCount)) return false;
    if((xPos<0)||(xPos>=DisplayStr::getLength())) return false;
    x = xPos;
    y = yPos;
    emit cursorPosChanged(xPos,yPos);
    return true;
}

int Display::getSubStrCount(int strNum) const
{
    if((strNum<0)||(strNum>=strCount)) return -1;
    return data.value(strNum).count();
}

void Display::moveCursorRight()
{
    if(x<DisplayStr::getLength()-1) x++;
    emit cursorPosChanged(x,y);
}

void Display::moveCursorLeft()
{
    if(x>0) x--;
    emit cursorPosChanged(x,y);
}

void Display::moveCursorUp()
{
    if(y>0) y--;
    emit cursorPosChanged(x,y);
}

void Display::moveCursorDown()
{
    if(y<strCount-1) y++;
    emit cursorPosChanged(x,y);
}

void Display::moveCursorToBegin()
{
    x=0;
    emit cursorPosChanged(x,y);
}

void Display::moveCursorToEnd()
{
    x = DisplayStr::getLength()-1;
    emit cursorPosChanged(x,y);
}

void Display::nextString()
{
    int lastStrNum = data.value(y).count() - 1;
    int curStrNum = curStr.value(y);
    if(curStrNum<lastStrNum) curStr.insert(y,curStrNum+1);
    emit curStrNumChanged(y,curStr.value(y));
}

void Display::prevString()
{
    int curStrNum = curStr.value(y);
    if(curStrNum>0) curStr.insert(y,curStrNum-1);
    emit curStrNumChanged(y,curStr.value(y));
}

const DisplayStr Display::getString(int strNum, int subStrNum)
{
    DisplayStr *str = nullptr;
    if((strNum>=0)&&(strNum<strCount)) {
        QVector<DisplayStr*> v = data.value(strNum);
        if(subStrNum<v.count()) {
            str = v.at(subStrNum);
            return (*str);
        }
    }
    return DisplayStr();
}

const DisplayStr Display::getCursorString()
{
    DisplayStr str = getString(y,getCurSubStrNum(y));
    return str;
}

int Display::getCurSubStrNum(int strNum) const
{
    if((strNum>=0)&&(strNum<strCount)) {
        return curStr.value(strNum);
    }
    return -1;
}

void Display::setReplaceMode(bool value)
{
    if(value!=getReplaceMode()) {
        DisplayStr::setReplaceMode(value);
        emit cursorPosChanged(x,y);
    }

}

bool Display::addEmptyStrBefore(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return false;
    DisplayStr* str = new DisplayStr();
    QVector<DisplayStr*> subStrings = data.value(strNum);
    subStrings.insert(subStrNum,str);
    data.insert(strNum,subStrings);
    curStr.insert(strNum,subStrNum);
    x=0;y=strNum;
    emit cursorPosChanged(x,y);
    emit strListChanged(strNum);
    emit curStrNumChanged(strNum,subStrNum);
    return true;
}

bool Display::addEmptyStrAfter(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return false;
    DisplayStr* str = new DisplayStr();
    QVector<DisplayStr*> subStrings = data.value(strNum);
    subStrings.insert(subStrNum+1,str);
    data.insert(strNum,subStrings);
    curStr.insert(strNum,subStrNum+1);
    x=0;y=strNum;
    emit cursorPosChanged(x,y);
    emit strListChanged(strNum);
    emit curStrNumChanged(strNum,subStrNum+1);
    return true;
}

bool Display::copyStrToBuffer(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return false;
    if(copyStrBuf!=nullptr) delete copyStrBuf;
    copyStrBuf = new DisplayStr(*(data.value(strNum).at(subStrNum)));
    return true;
}

bool Display::pasteStrFromBuffer(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return false;
    if(copyStrBuf==nullptr) return false;
    QVector<DisplayStr*> subStrings = data.value(strNum);
    DisplayStr* str = subStrings.at(subStrNum);
    str->operator =(*copyStrBuf);
    curStr.insert(strNum,subStrNum);
    x=0;y=strNum;
    emit cursorPosChanged(x,y);
    emit curStrNumChanged(strNum,subStrNum);
    emit strChanged(strNum, subStrNum);
    return true;
}

bool Display::deleteStr(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return false;
    QVector<DisplayStr*> subStrings = data.value(strNum);
    if(subStrings.count()==1) return false;
    subStrings.remove(subStrNum);
    data.insert(strNum,subStrings);
    if(subStrNum>=subStrings.count()) subStrNum--;
    curStr.insert(strNum,subStrNum);
    x=0;y=strNum;
    emit cursorPosChanged(x,y);
    emit curStrNumChanged(strNum,subStrNum);
    emit strListChanged(strNum);
    return true;
}

bool Display::insertSymbol(quint8 code)
{
    if(checkStrNum(y,getCurSubStrNum(y))==false) return false;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    if(str->insertSymbol(x,code)==true) {
        moveCursorRight();
        emit strChanged(y,getCurSubStrNum(y));
        return true;
    }
    return false;
}

void Display::deleteSymbol()
{
    if(checkStrNum(y,getCurSubStrNum(y))==false) return;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    str->deleteSymbol(x);
    emit strChanged(y,getCurSubStrNum(y));
}

void Display::backspace()
{
    if(x>0) {
        x--;
        deleteSymbol();
        emit cursorPosChanged(x,y);
    }
}

bool Display::addVar(const VarPattern &vP)
{
    if(checkStrNum(y,getCurSubStrNum(y))==false) return false;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    bool res =  str->addVar(vP,x);
    if(res) emit strChanged(y,getCurSubStrNum(y));
    return res;
}

bool Display::updVar(const VarPattern &vP)
{
    if(checkStrNum(y,getCurSubStrNum(y))==false) return false;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    bool res = str->updVar(vP,x);
    if(res) {
        while((!str->isThisABeginningOfVar(x))&&(x>0)) x--;
        emit cursorPosChanged(x,y);
        emit strChanged(y,getCurSubStrNum(y));
    }
    return res;
}

bool Display::goToStr(int strNum, int subStrNum)
{
    if(checkStrNum(y,getCurSubStrNum(y))==false) return false;
    curStr.insert(strNum,subStrNum);
    x = 0; y = strNum;
    emit curStrNumChanged(strNum, subStrNum);
    emit cursorPosChanged(x,y);
    return true;
}

void Display::toggleActive(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return;
    DisplayStr* str = data.value(strNum).at(subStrNum);
    str->setActive(!str->isActive());
    emit strListChanged(strNum);
}

void Display::clearDisplay()
{
    DisplayStr::setReplaceMode(false);
    QList< QVector<DisplayStr*> > strings = data.values();
    for(int i=0;i<strCount;i++) {
        foreach (DisplayStr* str, strings[i]) {
           delete str;
        }
    }

    data.clear();
    copyStrBuf = nullptr;

    for(int i=0;i<strCount;i++) {
        QVector<DisplayStr*> v;
        DisplayStr* s = new DisplayStr();
        v += s;
        data.insert(i,v);
        curStr.insert(i,0);
    }

    for(int i=0;i<getStrCount();i++) {
        curStr.insert(i,0);
    }
    x=0;y=0;
    for(int i=0;i<getStrCount();i++) {
        emit strListChanged(i);
        emit curStrNumChanged(i,0);
        emit strChanged(i,0);
    }
    emit cursorPosChanged(0,0);
}

Display::~Display()
{
    for(int i=0;i<strCount;i++) {
        QVector<DisplayStr*> v = data.value(i);
        foreach (DisplayStr* ptr, v) {
           delete ptr;
        }
    }
    if(copyStrBuf!=nullptr) delete copyStrBuf;
}

