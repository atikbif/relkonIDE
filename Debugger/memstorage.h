#ifndef MEMSTORAGE_H
#define MEMSTORAGE_H

#include <QObject>
#include <QVector>
#include <QByteArray>
#include "memblock.h"
#include <QMutex>

class MemStorage : public QObject
{
    Q_OBJECT
    QVector<MemBlock*> blocks;
    QMutex mutex;
public:
    explicit MemStorage(QObject *parent = 0);
    QByteArray getData(const QString &memType, int addr, int count);
    bool connectCellToID(const QString &memType, int addr, const QString &id);
    QStringList getMemTypes() const;
    void clearIDs();
    ~MemStorage();

signals:
    updateMemory(QStringList ids);
public slots:
    bool updateBlock(QString memType, int addr, QByteArray data);
};

#endif // MEMSTORAGE_H
