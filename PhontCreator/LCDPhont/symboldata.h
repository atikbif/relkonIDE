#ifndef SYMBOLDATA_H
#define SYMBOLDATA_H

// класс для хранения данных символа из набора шрифта

#include <QBitArray>
#include <QList>
#include <QObject>

class SymbolData
{
    static const int height = 8;
    static const int width = 5;
    QList<QBitArray> data; // данные в виде набора строк
    int code;   // код символа
    bool checkXY(int strNum, int pos) const;    // проверка корректности координат пиксела
public:
    explicit SymbolData(int sCode=0);
    bool getPixel(int strNum, int pos) const;
    void setPixel(int strNum, int pos, bool value);
    bool setData(const QList<QBitArray> &pixels);
    const QList<QBitArray> getData(void) const;
    static int getHeight(void);
    static int getWidth(void);
    int getCode(void) const;
    ~SymbolData();
};

Q_DECLARE_METATYPE(SymbolData*)

#endif // SYMBOLDATA_H
