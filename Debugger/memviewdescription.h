#ifndef MEMVIEWDESCRIPTION_H
#define MEMVIEWDESCRIPTION_H

// класс с данными для вкладки просмотра памяти в отладчике

#include <QString>

class MemViewDescription
{
    int memType;    // FRAM RAM
    int startAddr;  // начальный адрес блока отображаемой памяти
    int rowCount;
    int colCount;
    bool checkAddr(int addr);   // проверка на выход за границы допустимого адр. пространства
public:
    enum {FRAM,RAM};
    MemViewDescription(int r=10, int c=10);
    void setMemType(int memCode);
    int getMemType(void) const;
    int getRowCount(void) const;
    int getcolumnCount(void) const;
    bool checkAddress(int address) const;
};

#endif // MEMVIEWDESCRIPTION_H
