#ifndef MEMSTORAGE_H
#define MEMSTORAGE_H

#include <QString>

class MemStorage
{
public:
    MemStorage();

    static const int ioMemSize = 484;
    static const int ramMemSize = 64*1024;
    static const int framMemSize = 32*1024;
    static const int userMemSize = 256;
    static const QString ioMemName;
    static const QString ramMemName;
    static const QString framMemName;
    static const QString userMemName;
    static const QString timeMemName;

    ~MemStorage();
};

#endif // MEMSTORAGE_H
