#ifndef ITERATOR_H
#define ITERATOR_H

// абстрактный интерфейс для передвижения по дереву объектов VarItem

#include "varitem.h"
#include <QString>

class Iterator
{
public:
    Iterator();
    virtual bool next() = 0;
    virtual bool previous() = 0;
    virtual bool first() = 0;
    virtual bool hasParent() = 0;
    virtual bool isNode() = 0;
    virtual bool up() = 0;
    virtual bool down() = 0;
    virtual bool topFirst() = 0;
    virtual QString currentID() = 0;
    virtual QString getParentID() = 0;
    virtual bool goToID(const QString& id) = 0;
    virtual int getItemCount() = 0;

    virtual ~Iterator();
};

#endif // ITERATOR_H
