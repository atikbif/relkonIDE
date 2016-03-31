#ifndef UNDOREDOSTACK_H
#define UNDOREDOSTACK_H

#include "undoredooperation.h"
#include <QVector>

class UndoRedoStack
{
    QVector<UndoRedoOperation*> stack;
    int pos;
    static const int maxCnt = 200;
public:
    UndoRedoStack();
    ~UndoRedoStack();
    void clear();
    void addOperation(const UndoRedoOperation &op);
    void undo();
    void redo();
};

#endif // UNDOREDOSTACK_H
