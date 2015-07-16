#ifndef MEMBLOCK_H
#define MEMBLOCK_H

// класс хранения данных для одного типа памяти (RAM, FRAM, USER, IO, ...)

#include <QStringList>
#include <QByteArray>
#include <QMultiHash>

class MemBlock
{
    QString memType;
    QMultiHash<int,QString> addrID;  // соответствие адреса ячейки и идентификаторов переменных
    QByteArray data;
public:
    MemBlock(const QString &typeOfMem, int count);
    quint8 getCell(int address) const;
    bool updateCell(int address, quint8 value);
    const QString& getMemType() const {return memType;}
    QStringList getID(int addr);
    bool addID(int addr, const QString& id);
    int getSize() const {return data.count();}
    void clearIDs(void) {addrID.clear();}
    ~MemBlock();
};

#endif // MEMBLOCK_H
