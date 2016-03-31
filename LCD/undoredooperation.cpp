#include "undoredooperation.h"
#include "display.h"

UndoRedoOperation::UndoRedoOperation(Display &inpDispl):startX(0), startY(0), resX(0), resY(0),
    opType(ReplaceString), displ(inpDispl), strNum(-1), subStrNum (-1)
{

}

void UndoRedoOperation::undo()
{
    switch(opType) {
    case ReplaceString:
        if((strNum<0)||(subStrNum<0)) return;
        displ.replaceStr(strNum,subStrNum,startStr);
        displ.setCursor(startX, startY);
        break;
    case DelString:
        if((strNum<0)||(subStrNum<0)) return;
        displ.addEmptyStrBefore(strNum,subStrNum,false);
        displ.replaceStr(strNum,subStrNum,startStr);
        displ.setCursor(startX, startY);
        break;
    case InsertString:
        if((strNum<0)||(subStrNum<0)) return;
        displ.deleteStr(strNum,subStrNum,false);
        displ.setCursor(startX, startY);
        break;
    }
}

void UndoRedoOperation::redo()
{
    switch(opType) {
    case ReplaceString:
        if((strNum<0)||(subStrNum<0)) return;
        displ.replaceStr(strNum,subStrNum,resStr);
        displ.setCursor(resX, resY);
        break;
    case DelString:
        if((strNum<0)||(subStrNum<0)) return;
        displ.deleteStr(strNum,subStrNum,false);
        displ.setCursor(resX, resY);
        break;
    case InsertString:
        if((strNum<0)||(subStrNum<0)) return;
        if(subStrNum==0) displ.addEmptyStrBefore(strNum,subStrNum,false);
        else displ.addEmptyStrAfter(strNum,subStrNum-1,false);
        displ.replaceStr(strNum,subStrNum,resStr);
        displ.setCursor(resX, resY);
        break;
    }
}
