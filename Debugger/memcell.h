#ifndef MEMCELL_H
#define MEMCELL_H

// однобайтовая ячейка памяти

#include <QObject>
#include <QDateTime>

class MemCell : public QObject
{
    Q_OBJECT
    unsigned char value;
    int quality;
    QDateTime timeLabel;
    int address;
public:
    explicit MemCell(int address = 0, QObject *parent = 0);
    void setValue(unsigned char newValue);
    void setQuality(int newQuality);
    unsigned char getValue() const {return value;}
    int getQuality() const {return quality;}
    void setAdderss(int value) {address=value;}
    int getAddress(void) const {return address;}
    QDateTime getCellTime() const {return timeLabel;}
    ~MemCell();

signals:
    dataUpdate(const MemCell&);
public slots:
};

#endif // MEMCELL_H
