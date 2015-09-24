#ifndef LCDPHONT_H
#define LCDPHONT_H

#include <QString>
#include <QHash>
#include <QList>
#include <QBitArray>

class LCDPhont
{
    int rowCount;
    int columnCount;
    int symbCount;
    QHash<int,int> uncdTable; // the first - unicodeValue, the second - number in phont's table
    QHash<int, QList<QBitArray> > pixels; // the first - number in phont table, the second - data
public:
    explicit LCDPhont(const QString& fName);
    int getSymbolsCount(void) const {return symbCount;}
    int getRowCount(void) const {return rowCount;}
    int getColumnCount(void) const {return columnCount;}
    bool getBitValue(int phCode,int row,int column) const;
    bool hasSymbol(int uncdValue) const;
    int getSymbCodeinPhont(int unicodeValue) const;
    ~LCDPhont();
private:
    void createUnicodeTable(void);
};

#endif // LCDPHONT_H
