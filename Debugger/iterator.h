#ifndef ITERATOR_H
#define ITERATOR_H

// абстрактный интерфейс для передвижения по дереву объектов VarItem

#include "varitem.h"

class Iterator
{
public:
    Iterator();
    virtual bool next() = 0;
    virtual bool previous() = 0;
    virtual bool first() = 0;
    virtual bool isTop() = 0;
    virtual bool isNode() = 0;
    virtual bool up() = 0;
    virtual bool down() = 0;
    virtual bool topFirst() = 0;
    virtual VarItem* current() = 0;
    virtual int getItemCount() = 0;

    ~Iterator();
};

#endif // ITERATOR_H
