#include "display.h"
#include <QStringList>
#include "undoredostack.h"

bool Display::checkStrNum(int strNum, int subStrNum)
{
    if(subStrNum<0) return false;
    if((strNum>=0)&&(strNum<strCount)) {
        if(subStrNum<data.value(strNum).count()) return true;
    }
    return false;
}

void Display::updVarDefinition(int strNum, int subStrNum, int VarNum, PultVarDefinition &vd)
{
    if(checkStrNum(strNum,subStrNum)) {
        QVector<DisplayStr*> v = data.value(strNum);
        v[subStrNum]->updVarDefinition(VarNum,vd);
    }
}

Display::Display(QObject *parent):QObject(parent),changed(false),copyStrBuf(nullptr),x(0),y(0),copySubject(false)
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

int Display::getVisibleSubStrCount(int strNum) const
{
    if((strNum<0)||(strNum>=strCount)) return -1;
    int num = 0;
    int allStrCnt = getSubStrCount(strNum);
    for(int i=0;i<allStrCnt;++i) {
        if(getString(strNum,i).isActive()) num++;
    }
    return num;
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
    if(curStrNum<lastStrNum) goToStr(y,curStrNum+1);
}

void Display::prevString()
{
    int curStrNum = curStr.value(y);
    if(curStrNum>0) goToStr(y,curStrNum-1);
}

DisplayStr Display::getString(int strNum, int subStrNum) const
{
    if((strNum>=0)&&(strNum<strCount)) {
        QVector<DisplayStr*> v = data.value(strNum);
        if(subStrNum<v.count()) {
            DisplayStr *str = nullptr;
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

void Display::addOperation(UndoRedoOperation &op)
{
    undoRedo.addOperation(op);
}

bool Display::addEmptyStrBefore(int strNum, int subStrNum, bool isUndoEn, bool strListUpdate)
{
    changed = true;
    if(checkStrNum(strNum,subStrNum)==false) return false;
    DisplayStr* str = new DisplayStr();
    UndoRedoOperation op(*this);
    if(isUndoEn) {
        op.setOperationType(UndoRedoOperation::InsertString);
        op.setStartCursor(x,y);
        op.setStartStr(*str);
        op.setStrNum(strNum);
        op.setSubStrNum(subStrNum);
    }
    QVector<DisplayStr*> subStrings = data.value(strNum);
    subStrings.insert(subStrNum,str);
    data.insert(strNum,subStrings);
    curStr.insert(strNum,subStrNum);
    x=0;y=strNum;
    if(isUndoEn) {
        op.setResCursor(x,y);
        op.setResStr(*str);
        undoRedo.addOperation(op);
    }
    emit cursorPosChanged(x,y);
    if(strListUpdate) emit strListChanged(strNum);
    emit curStrNumChanged(strNum,subStrNum);
    return true;
}

bool Display::addEmptyStrAfter(int strNum, int subStrNum, bool isUndoen)
{
    changed = true;
    if(checkStrNum(strNum,subStrNum)==false) return false;
    DisplayStr* str = new DisplayStr();
    UndoRedoOperation op(*this);
    if(isUndoen) {
        op.setOperationType(UndoRedoOperation::InsertString);
        op.setStartCursor(x,y);
        op.setStartStr(*str);
        op.setStrNum(strNum);
        op.setSubStrNum(subStrNum+1);
    }
    QVector<DisplayStr*> subStrings = data.value(strNum);
    subStrings.insert(subStrNum+1,str);
    data.insert(strNum,subStrings);
    curStr.insert(strNum,subStrNum+1);
    x=0;y=strNum;
    if(isUndoen) {
        op.setResCursor(x,y);
        op.setResStr(*str);
        undoRedo.addOperation(op);
    }
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
    setCopySubject(false);
    return true;
}

bool Display::copyStrListToBuffer(int strNum, QVector<int> &subNums)
{
    for(int i=0;i<copyStrList.count();++i) {
        delete copyStrList.at(i);
    }
    copyStrList.clear();
    for(int i=0;i<subNums.count();++i) {
        DisplayStr *s = new DisplayStr(*(data.value(strNum).at(subNums.at(i))));
        copyStrList.append(s);
    }
    return true;
}

bool Display::pasteStrFromBuffer(int strNum, int subStrNum, bool isUndoEn)
{
    changed = true;
    if(checkStrNum(strNum,subStrNum)==false) return false;
    if(copyStrBuf==nullptr) return false;
    QVector<DisplayStr*> subStrings = data.value(strNum);
    DisplayStr* str = subStrings.at(subStrNum);
    UndoRedoOperation op(*this);
    if(isUndoEn) {
        op.setOperationType(UndoRedoOperation::ReplaceString);
        op.setStartCursor(x,y);
        op.setStartStr(*str);
        op.setStrNum(strNum);
        op.setSubStrNum(subStrNum);
    }
    str->operator =(*copyStrBuf);
    curStr.insert(strNum,subStrNum);
    x=0;y=strNum;
    if(isUndoEn) {
        op.setResCursor(x,y);
        op.setResStr(*str);
        undoRedo.addOperation(op);
    }
    emit cursorPosChanged(x,y);
    emit curStrNumChanged(strNum,subStrNum);
    emit strChanged(strNum, subStrNum);
    return true;
}

bool Display::pasteStrFromCopyListBuffer(int strNum, int subStrNum, int listIndex, bool isUndoEn)
{
    if((listIndex<0)||(listIndex>=copyStrList.count())) return false;
    changed = true;
    if(checkStrNum(strNum,subStrNum)==false) return false;
    QVector<DisplayStr*> subStrings = data.value(strNum);
    DisplayStr* str = subStrings.at(subStrNum);
    UndoRedoOperation op(*this);
    if(isUndoEn) {
        op.setOperationType(UndoRedoOperation::ReplaceString);
        op.setStartCursor(x,y);
        op.setStartStr(*str);
        op.setStrNum(strNum);
        op.setSubStrNum(subStrNum);
    }
    str->operator =(*(copyStrList.at(listIndex)));
    curStr.insert(strNum,subStrNum);
    x=0;y=strNum;
    if(isUndoEn) {
        op.setResCursor(x,y);
        op.setResStr(*str);
        undoRedo.addOperation(op);
    }
    emit cursorPosChanged(x,y);
    emit curStrNumChanged(strNum,subStrNum);
    emit strChanged(strNum, subStrNum);
    return true;
}

void Display::clearCopyStrList()
{
    for(int i=0;i<copyStrList.count();++i) {
        delete copyStrList.at(i);
    }
    copyStrList.clear();
}

const DisplayStr Display::getStrFromCopyList(int i) const
{
    if((i>=0)&&(i<copyStrList.count())) {
        return DisplayStr(*(copyStrList.at(i)));
    }
    return DisplayStr();
}

bool Display::deleteStr(int strNum, int subStrNum, bool isUndoEn)
{
    changed = true;
    if(checkStrNum(strNum,subStrNum)==false) return false;
    QVector<DisplayStr*> subStrings = data.value(strNum);
    if(subStrings.count()==1) return false;
    DisplayStr *ptr = subStrings.at(subStrNum);
    UndoRedoOperation op(*this);
    if(isUndoEn) {
        op.setOperationType(UndoRedoOperation::DelString);
        op.setStartCursor(x,y);
        op.setStartStr(*ptr);
        op.setStrNum(strNum);
        op.setSubStrNum(subStrNum);
    }
    subStrings.remove(subStrNum);
    delete ptr;
    data.insert(strNum,subStrings);
    if(subStrNum>=subStrings.count()) subStrNum--;
    curStr.insert(strNum,subStrNum);
    if(isUndoEn) {
        op.setResCursor(x,y);
        undoRedo.addOperation(op);
    }
    x=0;y=strNum;
    emit cursorPosChanged(x,y);
    emit strListChanged(strNum);
    emit curStrNumChanged(strNum,subStrNum);
    return true;
}

bool Display::replaceStr(int strNum, int subStrNum, const DisplayStr &str)
{
    if(strNum>=getStrCount()) return false;
    if(subStrNum>=getSubStrCount(strNum)) return false;
    QVector<DisplayStr*> strings = data.value(strNum);
    DisplayStr *oldStr = strings.at(subStrNum);
    DisplayStr *newStr = new DisplayStr(str);
    strings[subStrNum] = newStr;
    data.insert(strNum, strings);
    delete oldStr;
    return true;
}

bool Display::insertSymbol(quint8 code, bool isUndoEn, bool strListUpdate)
{
    changed = true;
    if(checkStrNum(y,getCurSubStrNum(y))==false) return false;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    UndoRedoOperation op(*this);
    if(isUndoEn) {
        op.setOperationType(UndoRedoOperation::ReplaceString);
        op.setStartCursor(x,y);
        op.setStartStr(*str);
        op.setStrNum(y);
        op.setSubStrNum(getCurSubStrNum(y));
    }
    if(str->insertSymbol(x,code)==true) {
        moveCursorRight();
        if(strListUpdate) emit strChanged(y,getCurSubStrNum(y));
        if(isUndoEn) {
            op.setResCursor(x,y);
            op.setResStr(*(data.value(y).at(getCurSubStrNum(y))));
            undoRedo.addOperation(op);
        }
        return true;
    }
    return false;
}

int Display::deleteSymbol()
{
    changed = true;
    int delCnt=0;
    if(checkStrNum(y,getCurSubStrNum(y))==false) return 0;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    UndoRedoOperation op(*this);
    op.setOperationType(UndoRedoOperation::ReplaceString);
    op.setStartCursor(x,y);
    op.setStartStr(*str);
    op.setStrNum(y);
    op.setSubStrNum(getCurSubStrNum(y));
    delCnt = str->deleteSymbol(x);
    op.setResCursor(x,y);
    op.setResStr(*(data.value(y).at(getCurSubStrNum(y))));
    undoRedo.addOperation(op);
    emit strChanged(y,getCurSubStrNum(y));
    return delCnt;
}

void Display::backspace()
{
    if(x>0) {
        x--;
        deleteSymbol();
        emit cursorPosChanged(x,y);
    }
}

bool Display::addVar(PultVarDefinition &vP, bool isUndoEn)
{
    changed = true;
    if(checkStrNum(y,getCurSubStrNum(y))==false) return false;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    UndoRedoOperation op(*this);
    if(isUndoEn) {
        op.setOperationType(UndoRedoOperation::ReplaceString);
        op.setStartCursor(x,y);
        op.setStartStr(*str);
        op.setStrNum(y);
        op.setSubStrNum(getCurSubStrNum(y));
    }
    vP.setPosInStr(x);
    bool res =  str->addVar(vP);
    if(res) {
        emit strChanged(y,getCurSubStrNum(y));
        if(isUndoEn) {
            op.setResCursor(x,y);
            op.setResStr(*(data.value(y).at(getCurSubStrNum(y))));
        }
        undoRedo.addOperation(op);
    }
    return res;
}

bool Display::updVar(PultVarDefinition &vP)
{
    changed = true;
    if(checkStrNum(y,getCurSubStrNum(y))==false) return false;
    DisplayStr* str = data.value(y).at(getCurSubStrNum(y));
    UndoRedoOperation op(*this);
    op.setOperationType(UndoRedoOperation::ReplaceString);
    op.setStartCursor(x,y);
    op.setStartStr(*str);
    op.setStrNum(y);
    op.setSubStrNum(getCurSubStrNum(y));
    vP.setPosInStr(x);
    bool res = str->updVar(vP);
    if(res) {
        while((!str->isThisABeginningOfVar(x))&&(x>0)) x--;
        op.setResCursor(x,y);
        op.setResStr(*(data.value(y).at(getCurSubStrNum(y))));
        undoRedo.addOperation(op);
        emit cursorPosChanged(x,y);
        emit strChanged(y,getCurSubStrNum(y));
    }
    return res;
}

bool Display::goToStr(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return false;
    curStr.insert(strNum,subStrNum);
    DisplayStr str = getString(strNum,subStrNum);
    x = 0;
    // поиск переменной в строке
    if(str.getVarsCount()) for(int i=0;i<str.getLength();i++) {
        if(str.isVarHere(i)) {
            x = i; break;
        }
    }
    y = strNum;
    emit curStrNumChanged(strNum, subStrNum);
    emit cursorPosChanged(x,y);
    return true;
}

void Display::toggleActive(int strNum, int subStrNum)
{
    if(checkStrNum(strNum,subStrNum)==false) return;
    DisplayStr* str = data.value(strNum).at(subStrNum);
    UndoRedoOperation op(*this);
    op.setOperationType(UndoRedoOperation::ReplaceString);
    op.setStartCursor(x,y);
    op.setStartStr(*str);
    op.setStrNum(strNum);
    op.setSubStrNum(subStrNum);
    str->setActive(!str->isActive());
    op.setResCursor(x,y);
    op.setResStr(*str);
    undoRedo.addOperation(op);
    emit strListChanged(strNum);
}

void Display::clearDisplay()
{
    changed = true;
    DisplayStr::setReplaceMode(false);
    QList< QVector<DisplayStr*> > strings = data.values();
    for(int i=0;i<strCount;i++) {
        foreach (DisplayStr* str, strings[i]) {
           delete str;
        }
    }
    setReplaceMode(false);
    data.clear();
    if(copyStrBuf != nullptr) delete copyStrBuf;
    copyStrBuf = nullptr;

    for(int i=0;i<strCount;i++) {
        QVector<DisplayStr*> v;
        DisplayStr* s = new DisplayStr();
        v += s;
        data.insert(i,v);
        curStr.insert(i,0);
    }

    x=0;y=0;
    for(int i=0;i<getStrCount();i++) {
        emit strListChanged(i);
        emit curStrNumChanged(i,0);
        emit strChanged(i,0);
    }
    undoRedo.clear();
    emit cursorPosChanged(0,0);
}

void Display::clearStack()
{
    undoRedo.clear();
}

void Display::getVars(QVector<PultVarDefinition> &vars)
{
    for(int i=0;i<getStrCount();i++) {
        for(int j=0;j<getSubStrCount(i);j++) {
            DisplayStr s = getString(i,j);
            for(int k=0;k<s.getVarsCount();k++) {
                PultVarDefinition vp;
                s.getVar(k,vp);
                vars << vp;
            }
        }
    }
}

void Display::getVarDefinitions(QVector<PultVarDefinition> &varList,int strNum,int subStrNum) const
{
    varList.clear();
    DisplayStr s = getString(strNum,subStrNum);
    for(int j=0;j<s.getVarsCount();j++) {
        PultVarDefinition v;
        s.getVar(j,v);
        varList += v;
    }
    qSort(varList);
}

// изменения описания переменной в связи с перекомпиляцией
// возможно изменение адреса или типа данных
void Display::updateDefinitions(VarsCreator &varOwner)
{
    varOwner.createPultNames();
    for(int i=0;i<getStrCount();i++) {
        for(int j=0;j<getSubStrCount(i);j++) {
            DisplayStr s = getString(i,j);
            for(int k=0;k<s.getVarsCount();k++) {
                PultVarDefinition vp;
                s.getVar(k,vp);
                QString id = vp.getId();
                if(varOwner.checkID(id)==false) {
                    QString updID = varOwner.getSimilarID(vp.getName());
                    if(updID.isEmpty()) {
                        vp.setExist(false);
                        updVarDefinition(i,j,k,vp);
                    }else {
                        vp.setExist(true);
                        vp.setId(updID);
                        VarItem var = varOwner.getVarByID(updID);
                        vp.setDataType(var.getDataType());
                        updVarDefinition(i,j,k,vp);
                    }
                }
            }
        }
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


bool Display::getCopySubject() const
{
    return copySubject;
}

void Display::setCopySubject(bool value)
{
    copySubject = value;
}

void Display::undo()
{
    undoRedo.undo();
    emit cursorPosChanged(x,y);
    emit strListChanged(y);
    emit curStrNumChanged(y,getCurSubStrNum(y));
    emit strChanged(y,getCurSubStrNum(y));
}

void Display::redo()
{
    undoRedo.redo();
    emit cursorPosChanged(x,y);
    emit strListChanged(y);
    emit curStrNumChanged(y,getCurSubStrNum(y));
    emit strChanged(y,getCurSubStrNum(y));
}
