#ifndef MEMSTORAGE_H
#define MEMSTORAGE_H

// класс для хранения данных различных видов памяти ПЛК

#include "memcell.h"
#include <QHash>
#include <QString>


class MemStorage
{
    QHash<QString, MemCell*> blockData; // массив ячеек (тип памяти - QString)
    QHash<QString, int> blockSize;  // размер указаннного типа памяти
public:
    void createBlock(const QString &memType,int blSize);
    int getCount(const QString &memType);
    MemCell* getCell(const QString &memType, int cellAddress);
    MemStorage();
    ~MemStorage();
};

#endif // MEMSTORAGE_H
