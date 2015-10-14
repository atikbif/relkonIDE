#ifndef LCDPHONT_H
#define LCDPHONT_H

// класс для работы с шрифтом дисплея

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
    static const QString defName;
    explicit LCDPhont(const QString& fName = defName);
    int getRowCount(void) const {return rowCount;}  // число строк символа
    int getColumnCount(void) const {return columnCount;}    // число столбцов символа
    bool getBitValue(int phCode,int row,int column) const;  // вернуть пиксел
    bool hasSymbol(int uncdValue) const;
    int getSymbCodeinPhont(int unicodeValue) const; // код символа в таблице шрифта по юникод значению
    int getUnicodeValue(int phontCode) const;   // юникод из кода символа в таблице шрифта
    ~LCDPhont();
private:
    void createUnicodeTable(void);
};

#endif // LCDPHONT_H
