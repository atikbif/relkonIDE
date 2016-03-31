#include "undoredostack.h"

UndoRedoStack::UndoRedoStack()
{

}

UndoRedoStack::~UndoRedoStack()
{
    clear();
}

void UndoRedoStack::clear()
{
    foreach (UndoRedoOperation *op, stack) {
        delete op;
    }
    stack.clear();
    pos = 0;
}

void UndoRedoStack::addOperation(const UndoRedoOperation &op)
{
    UndoRedoOperation *newOp = new UndoRedoOperation(op);
    if(pos==stack.count()) {stack.append(newOp);pos++;}
    else {
        int remCnt = stack.count() - pos;
        for(int i=0;i<remCnt;i++) {
            UndoRedoOperation *lastOp = stack.last();
            stack.removeLast();
            delete lastOp;
        }
        stack.append(newOp);
        pos++;
    }
    if(stack.count()>=maxCnt) {
        UndoRedoOperation *firstOp = stack.at(0);
        stack.remove(0);
        delete firstOp;
        pos--;
    }
}

void UndoRedoStack::undo()
{
    if(stack.count()==0) return;
    if(pos==0) return;
    UndoRedoOperation *op = stack.at(pos-1);
    op->undo();
    pos--;
}

void UndoRedoStack::redo()
{
    if(stack.count()==0) return;
    if(pos==stack.count()) return;
    UndoRedoOperation *op = stack.at(pos);
    op->redo();
    pos++;
}
