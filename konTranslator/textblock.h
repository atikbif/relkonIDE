#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include <QStringList>
#include <QVector>

class TextBlock
{
    QStringList text;
    QVector<int> konStrNum;
public:
    TextBlock();
    void clearText(void);   // очистить весь текст блока
    void addString(const QString& str, int konNum); // добавить строку
    QStringList& getText(void);   // получить содержимое всех строк
    QVector<int>& getKonNums(void);   // получить соответствие номеров строк файлу kon
};

#endif // TEXTBLOCK_H
