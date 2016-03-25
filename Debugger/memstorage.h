#ifndef MEMSTORAGE_H
#define MEMSTORAGE_H

// хранилище всех типов памяти

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
    static const int ioMemSize = 500;
    static const int ramMemSize = 64*1024;
    static const int framMemSize = 32*1024;
    static const int userMemSize = 256;
    static const int eeMemSize = 1024;
    static const QString ioMemName;
    static const QString ramMemName;
    static const QString framMemName;
    static const QString userMemName;
    static const QString timeMemName;
    static const QString eeMemName;
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
