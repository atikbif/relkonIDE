#include "display.h"

bool Display::checkStrNum(int strNum, int subStrNum)
{
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
    emit cursorPosChanged(xPos,yPos);
    return true;
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

bool Display::addEmptyStrBefore(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return false;
    DisplayStr* str = new DisplayStr();
    QVector<DisplayStr*> subStrings = data.value(strNum);
    subStrings.insert(subStrNum,str);
    data.insert(strNum,subStrings);
    emit strListChanged(strNum);
    return true;
}

bool Display::addEmptyStrAfter(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return false;
    DisplayStr* str = new DisplayStr();
    QVector<DisplayStr*> subStrings = data.value(strNum);
    subStrings.insert(subStrNum+1,str);
    data.insert(strNum,subStrings);
    emit strListChanged(strNum);
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
    emit strChanged(strNum, subStrNum);
    return true;
}

bool Display::deleteStr(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return false;
    QVector<DisplayStr*> subStrings = data.value(strNum);
    subStrings.remove(subStrNum);
    data.insert(strNum,subStrings);
    emit strListChanged(strNum);
    return true;
}

bool Display::insertSymbol(quint8 code)
{
    if(checkStrNum(y,getCurSubStrNum(y))==false) return false;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    emit strChanged(y,getCurSubStrNum(y));
    return str->insertSymbol(x,code);
}

void Display::deleteSymbol()
{
    if(checkStrNum(y,getCurSubStrNum(y))==false) return;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    emit strChanged(y,getCurSubStrNum(y));
    return str->deleteSymbol(x);
}

bool Display::addVar(const VarPattern &vP)
{
    if(checkStrNum(y,getCurSubStrNum(y))==false) return false;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    emit strChanged(y,getCurSubStrNum(y));
    return str->addVar(vP,x);
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

