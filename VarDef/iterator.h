#ifndef ITERATOR_H
#define ITERATOR_H

// абстрактный интерфейс для передвижения по дереву объектов VarItem

#include "varitem.h"
#include <QString>

class Iterator
{
public:
    Iterator();
    virtual bool next() = 0;    // перейти к следующему элементу
    virtual bool first() = 0;   // перейти к первому элементу в узле
    virtual bool isNode() = 0;  // имеет ли дочерние элементы
    virtual bool up() = 0;      // перейти к родителю
    virtual bool down() = 0;    // перейти к потомку
    virtual bool topFirst() = 0;    // перейти на вершину дерева
    virtual QString currentID() = 0;    // идентификатор текущего элемента
    virtual bool goToID(const QString& id) = 0; // перейти к указанному элементу
    virtual int getItemCount() = 0; // количество элементов в текущем уровне

    virtual ~Iterator();
};

#endif // ITERATOR_H
