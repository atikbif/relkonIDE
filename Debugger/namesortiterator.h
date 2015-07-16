#ifndef NAMESORTITERATOR_H
#define NAMESORTITERATOR_H

// класс итератора по дереву переменных VarItem
// с сортировкой по имени.
// Не является владельцем указателей на переменные
// поэтому в деструкторе нет необходимость очищать память

#include "iterator.h"
#include <QVector>
#include "idstorage.h"

class NameSortIterator : public Iterator
{
    int posIncash;
    QStringList cash;
    IDStorage& ids;

    void createCash(const QString& varID); // создаёт отсортированный список sibling переменных
    bool testCashState();   // проверяет корректность кэшированного списка переменных
public:
    NameSortIterator(IDStorage &idStor);
    bool next();
    bool previous();
    bool first();   // перейти к первому элементу текущего среза
    bool isNode();  // имеет потомков
    bool up();  // подняться на родительский уровень
    bool down();    // спуститься к дочерним элементам
    bool topFirst();    // перейти к вершине всего дерева
    bool hasParent();   // имеет родителя
    bool goToID(const QString& id);
    QString getParentID();    // вернуть id родителя
    QString currentID();
    int getItemCount(); // количество элементов в текущем уровне
    ~NameSortIterator();
};

#endif // NAMESORTITERATOR_H
