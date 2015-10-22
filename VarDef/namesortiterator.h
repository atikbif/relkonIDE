#ifndef NAMESORTITERATOR_H
#define NAMESORTITERATOR_H

// класс итератора по дереву переменных VarItem
// с сортировкой по имени.
// Не является владельцем указателей на переменные
// поэтому в деструкторе нет необходимости очищать память

#include "iterator.h"
#include <QVector>
#include "idstorage.h"

class NameSortIterator : public Iterator
{
    int posIncash;  // позиция текущего элемента в срезе дерева
    QStringList cash;   // идентификаторы в текущем срезе дерева
    IDStorage& ids;     // ссылка на хранилище переменных

    void createCash(const QString& varID); // создаёт отсортированный список sibling переменных
    bool testCashState();   // проверяет корректность кэшированного списка переменных
    static bool lessThan(const QString &s1, const QString &s2);
public:
    explicit NameSortIterator(IDStorage &idStor);
    bool next();
    bool first();   // перейти к первому элементу текущего среза
    bool isNode();  // имеет потомков
    bool up();  // подняться на родительский уровень
    bool down();    // спуститься к дочерним элементам
    bool topFirst();    // перейти к вершине всего дерева
    bool goToID(const QString& id);
    QString currentID();
    int getItemCount(); // количество элементов в текущем уровне
    ~NameSortIterator();
};

#endif // NAMESORTITERATOR_H
