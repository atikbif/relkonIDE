#ifndef COLORLIST_H
#define COLORLIST_H

#include <QString>
#include <QHash>
#include <QVector>
#include <QSharedPointer>

class ColorForWord
{
    QString codeWord;
    bool sysColor;
    int userRed;
    int userGreen;
    int userBlue;
    int sysRed;
    int sysGreen;
    int sysBlue;
    static const QString defName;
public:
    ColorForWord(const QString &word=defName,int r=0, int g=0, int b=0);
    QString getCodeWord() const {return codeWord;}
    bool isSystem() const {return sysColor;}
    int getUserRed() const {return userRed;}
    int getUserGreen() const {return userGreen;}
    int getUserBlue() const {return userBlue;}
    void setUserRed(int value) {userRed=value;}
    void setUserGreen(int value) {userGreen=value;}
    void setUserBlue(int value) {userBlue=value;}
    void setSystem(bool value) {sysColor=value;}
    QString getDefaultName() const {return defName;}
    int getSysRed() const;
    void setSysRed(int value);
    int getSysGreen() const;
    void setSysGreen(int value);
    int getSysBlue() const;
    void setSysBlue(int value);
};

class ColorList
{   
    QHash<QString,QString> knownCodeWords;
    QVector<QSharedPointer<ColorForWord>> cList;
public:
    ColorList();
    void addColor(const QString& word,int r, int g, int b);
    QString getWordDefinition(const QString &word) const;
    QString getCodeByDefinition(const QString &word) const;
    QSharedPointer<ColorForWord> getColor(const QString &word) const;
    void setUserColors(const QString &word, int r, int g, int b);
    void setSysColors(const QString &word, int r, int g, int b);
    void setSysColor(const QString &word, bool value);
    int getCount() const {return cList.count();}
    QSharedPointer<ColorForWord> getColor(int i);
    static ColorList readUserColors();
    static void writeUserColors(ColorList &list);
};

#endif // COLORLIST_H
