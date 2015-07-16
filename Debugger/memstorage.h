#ifndef MEMSTORAGE_H
#define MEMSTORAGE_H

#include <QObject>
#include <QVector>
#include <QByteArray>
#include "memblock.h"

class MemStorage : public QObject
{
    Q_OBJECT
    QVector<MemBlock*> blocks;
public:
    explicit MemStorage(QObject *parent = 0);
    bool updateBlock(const QString &memType, int addr, const QByteArray &data);
    QByteArray getData(const QString &memType, int addr, int count);
    bool connectCellToID(const QString &memType, int addr, const QString &id);
    QStringList getMemTypes() const;
    void clearIDs();
    ~MemStorage();

signals:
    updateMemory(QStringList ids);
public slots:
};

#endif // MEMSTORAGE_H
