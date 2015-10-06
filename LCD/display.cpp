#include "display.h"
#include <QStringList>

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

DisplayStr Display::getString(int strNum, int subStrNum) const
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

void Display::getVars(QStringList &id, QStringList &pattern)
{
    for(int i=0;i<getStrCount();i++) {
        for(int j=0;j<getSubStrCount(i);j++) {
            DisplayStr s = getString(i,j);
            for(int k=0;k<s.getVarsCount();k++) {
                vPatt vp;
                s.getVar(k,vp);
                id << vp.variable.getVarID();
                pattern << vp.variable.getPattern();
            }
        }
    }
}

void Display::getVarDefinitions(QVector<PultVarDefinition> &varList,int strNum) const
{
    varList.clear();
    if(strNum == 1) {
        PultVarDefinition v1;
        v1.setName("test");
        v1.setDataType("unsigned char");
        v1.setPattern("123");
        v1.setStrNum(1);
        v1.setSubStrNum(0);

        PultVarDefinition v2;
        v2.setName("test2");
        v2.setDataType("unsigned char");
        v2.setPattern("12345");
        v2.setStrNum(1);
        v2.setSubStrNum(3);
        v2.setIsEditable(true);

        PultVarDefinition v3;
        v3.setName("test3");
        v3.setDataType("double");
        v3.setPattern("1345");
        v3.setStrNum(1);
        v3.setSubStrNum(2);

        PultVarDefinition v4;
        v4.setName("test4");
        v4.setDataType("double");
        v4.setPattern("1345");
        v4.setStrNum(1);
        v4.setSubStrNum(0);
        v4.setPosInStr(10);

        PultVarDefinition v5;
        v5.setName("test5");
        v5.setDataType("unsigned short");
        v5.setPattern("1345");
        v5.setStrNum(1);
        v5.setSubStrNum(1);
        v5.setForceSign(true);
        v5.setIsEEVar(true);
        v5.setEEposInSettingsTable(5);

        PultVarDefinition v6;
        v6.setName("test6");
        v6.setDataType("unsigned long");
        v6.setPattern("1345");
        v6.setStrNum(1);
        v6.setSubStrNum(1);
        v6.setForceSign(true);
        v6.setIsEEVar(true);
        v6.setEEposInSettingsTable(5);
        v6.setIsEditable(true);
        v6.setPosInStr(12);

        varList += v1;
        varList += v2;
        varList += v3;
        varList += v4;
        varList += v5;
        varList += v6;
    }
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

