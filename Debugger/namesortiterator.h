#ifndef NAMESORTITERATOR_H
#define NAMESORTITERATOR_H

// класс итератора по дереву переменных VarItem
// с сортировкой по имени.
// Не является владельцем указателей на переменные
// поэтому в деструкторе нет необходимость очищать память

#include "iterator.h"
#include "compositevar.h"
#include <QVector>

class NameSortIterator : public Iterator
{
    int posIncash;
    QVector<CompositeVar*> cash;
    void createCash(CompositeVar *var); // создаёт отсортированный список sibling переменных
    bool testCashState();   // проверяет корректность кэшированного списка переменных
public:
    NameSortIterator(CompositeVar* var);
    bool next();
    bool previous();
    bool first();   // перейти к первому элементу текущего среза
    bool isTop();   // верхний элемент в текущем срезе
    bool isNode();  // имеет потомков
    bool up();  // подняться на родительский уровень
    bool down();    // спуститься к дочерним элементам
    bool topFirst();    // перейти к вершине всего дерева
    VarItem* current();
    int getItemCount(); // количество элементов в текущем уровне
    ~NameSortIterator();
};

#endif // NAMESORTITERATOR_H
