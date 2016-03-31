#ifndef UNDOREDOOPERATION_H
#define UNDOREDOOPERATION_H

#include "displaystr.h"
//#include "display.h"

class Display;

class UndoRedoOperation
{
public:
    enum OpType {DelString, ReplaceString, InsertString};
private:
    DisplayStr startStr;
    DisplayStr resStr;
    int startX, startY;
    int resX, resY;
    OpType opType;
    Display &displ;
    int strNum;
    int subStrNum;
public:
    explicit UndoRedoOperation(Display &inpDispl);
    void setStartStr(const DisplayStr &str) {startStr=str;}
    void setResStr(const DisplayStr &str) {resStr=str;}
    DisplayStr getStartStr(void) const {return startStr;}
    DisplayStr getResStr(void) const {return resStr;}
    void setStartCursor(int x, int y) {startX = x; startY = y;}
    int getStartX() const {return startX;}
    int getStartY() const {return startY;}
    void setResCursor(int x, int y) {resX = x; resY = y;}
    int getResX() const {return resX;}
    int getResY() const {return resY;}
    void setOperationType(OpType value) {opType = value;}
    OpType getOperationType() const {return opType;}
    void setStrNum(int value) {strNum = value;}
    void setSubStrNum(int value) {subStrNum = value;}
    void undo();
    void redo();
};

#endif // UNDOREDOOPERATION_H
