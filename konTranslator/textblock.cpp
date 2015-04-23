#include "textblock.h"

TextBlock::TextBlock()
{
}

void TextBlock::clearText()
{
    text.clear();
}

void TextBlock::addString(const QString &str, int konNum)
{
    text += str;
    konStrNum += konNum;
}

QStringList &TextBlock::getText()
{
    return text;
}

QVector<int> &TextBlock::getKonNums()
{
    return konStrNum;
}
