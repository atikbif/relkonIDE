#include "colorlist.h"
#include <QSettings>

const QString ColorForWord::defName="default";

ColorList::ColorList()
{
    knownCodeWords.insert("numbers","числа");
    knownCodeWords.insert("data types","типы данных");
    knownCodeWords.insert("operators","операторы");
    knownCodeWords.insert("brackets","скобки");
    knownCodeWords.insert("directives","директивы");
    knownCodeWords.insert("quotation","текст в кавычках");
    knownCodeWords.insert("macroses","макросы");
    knownCodeWords.insert("sysVariables","системные переменные");
    knownCodeWords.insert("sysFunctions","системные функции");
    knownCodeWords.insert("singleline comments","однострочные комментарии");
    knownCodeWords.insert("multiline comments","многострочные комментарии");
}

void ColorList::addColor(const QString &word, int r, int g, int b)
{
    auto c = QSharedPointer<ColorForWord>(new ColorForWord(word,r,g,b));
    cList.append(c);
}

QString ColorList::getWordDefinition(const QString &word) const
{
    if(knownCodeWords.keys().contains(word)) return knownCodeWords.value(word);
    return word;
}

QString ColorList::getCodeByDefinition(const QString &word) const
{
    if(knownCodeWords.values().contains(word)) return knownCodeWords.key(word);
    return word;
}

QSharedPointer<ColorForWord> ColorList::getColor(const QString &word) const
{
    QSharedPointer<ColorForWord> col = QSharedPointer<ColorForWord>(new ColorForWord());
    foreach (auto c, cList) {
       if(c->getCodeWord()==word) {col = c;break;}
    }
    return col;
}

void ColorList::setSysColors(const QString &word, int r, int g, int b)
{
    foreach (QSharedPointer<ColorForWord> c, cList) {
       if(c->getCodeWord()==word) {
           c->setSysRed(r);
           c->setSysGreen(g);
           c->setSysBlue(b);
           break;
       }
    }
}

void ColorList::setUserColors(const QString &word, int r, int g, int b)
{
    foreach (QSharedPointer<ColorForWord> c, cList) {
       if(c->getCodeWord()==word) {
           c->setUserRed(r);
           c->setUserGreen(g);
           c->setUserBlue(b);
           break;
       }
    }
}

void ColorList::setSysColor(const QString &word, bool value)
{
    foreach (QSharedPointer<ColorForWord> c, cList) {
       if(c->getCodeWord()==word) {
           c->setSystem(value);
           break;
       }
    }
}

QSharedPointer<ColorForWord> ColorList::getColor(int i)
{
    QSharedPointer<ColorForWord> col = QSharedPointer<ColorForWord>(new ColorForWord());
    if((i>=0)&&(i<getCount())) {
        col = cList.at(i);
    }
    return col;
}

ColorList ColorList::readUserColors()
{
    ColorList list;
    QSettings settings;
    int size = settings.beginReadArray("userColors");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString word = settings.value("codeWord").toString();
        int red = settings.value("user_red").toInt();
        int green = settings.value("user_green").toInt();
        int blue = settings.value("user_blue").toInt();
        bool isSys = settings.value("sysColor").toBool();
        list.addColor(word,red,green,blue);
        list.setSysColor(word,isSys);
        red = settings.value("sys_red").toInt();
        green = settings.value("sys_green").toInt();
        blue = settings.value("sys_blue").toInt();
        list.setSysColors(word,red,green,blue);
    }
    settings.endArray();
    return list;
}

void ColorList::writeUserColors(ColorList &list)
{
    QSettings settings;
    settings.beginWriteArray("userColors");
    for (int i = 0; i < list.getCount(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("codeWord", list.getColor(i)->getCodeWord());
        settings.setValue("user_red", list.getColor(i)->getUserRed());
        settings.setValue("user_green", list.getColor(i)->getUserGreen());
        settings.setValue("user_blue", list.getColor(i)->getUserBlue());
        settings.setValue("sysColor", list.getColor(i)->isSystem());
        settings.setValue("sys_red", list.getColor(i)->getSysRed());
        settings.setValue("sys_green", list.getColor(i)->getSysGreen());
        settings.setValue("sys_blue", list.getColor(i)->getSysBlue());
    }
    settings.endArray();
}

int ColorForWord::getSysRed() const
{
    return sysRed;
}

void ColorForWord::setSysRed(int value)
{
    sysRed = value;
}

int ColorForWord::getSysGreen() const
{
    return sysGreen;
}

void ColorForWord::setSysGreen(int value)
{
    sysGreen = value;
}

int ColorForWord::getSysBlue() const
{
    return sysBlue;
}

void ColorForWord::setSysBlue(int value)
{
    sysBlue = value;
}

ColorForWord::ColorForWord(const QString &word, int r, int g, int b)
{
    codeWord = word;
    userRed = r;
    userGreen = g;
    userBlue = b;
    sysRed = r;
    sysGreen = g;
    sysBlue = b;
    sysColor = true;
}
