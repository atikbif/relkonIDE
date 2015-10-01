#ifndef DISPLAY_H
#define DISPLAY_H

#include "displaystr.h"
#include <QVector>
#include <QHash>
#include <QObject>

// класс дисплея

class Display: public QObject
{
    Q_OBJECT
    const static int strCount = 4;  // количество строк в дисплее
    QHash<int, QVector<DisplayStr*> > data; // номер строки, массив подстрок
    QHash<int, int> curStr; // номер строки, номер активной подстроки
    DisplayStr* copyStrBuf; // указатель на скопированную строку
    int x, y; // координаты курсора
    bool checkStrNum(int strNum, int subStrNum);
public:
    explicit Display(QObject *parent = 0);
    int getStrCount() const {return strCount;}
    int getLength(void) const {return DisplayStr::getLength();}
    bool setCursor(int xPos, int yPos);
    int getXPosition(void) const {return x;}
    int getYPosition(void) const {return y;}
    int getSubStrCount(int strNum) const;
    void moveCursorRight(void);
    void moveCursorLeft(void);
    void moveCursorUp(void);
    void moveCursorDown(void);
    void moveCursorToBegin(void);
    void moveCursorToEnd(void);
    void nextString(void);
    void prevString(void);
    const DisplayStr getString(int strNum, int subStrNum);
    const DisplayStr getCursorString(void);  // вернуть строку, на которую указывает курсор
    int getCurSubStrNum(int strNum) const;
    bool getReplaceMode(void) const {return DisplayStr::getReplaceMode();}
    void setReplaceMode(bool value);
    bool addEmptyStrBefore(int strNum, int subStrNum);
    bool addEmptyStrAfter(int strNum, int subStrNum);
    bool copyStrToBuffer(int strNum, int subStrNum);
    bool pasteStrFromBuffer(int strNum, int subStrNum);
    bool deleteStr(int strNum, int subStrNum);
    bool insertSymbol(quint8 code);
    void deleteSymbol(void);
    void backspace(void);
    bool addVar(const VarPattern& vP);
    bool updVar(const VarPattern& vP);
    bool goToStr(int strNum, int subStrNum); // сделать строку активной и переместить туда курсор
    void toggleActive(int strNum, int subStrNum);
    void clearDisplay(void);
    ~Display();
signals:
    cursorPosChanged(int x,int y); // были изменены координаты курсора
    strListChanged(int strNum);    // были добавлены/удалены подстроки в строке
    curStrNumChanged(int strNum,int subStrNum);    // изменён номер текущей подстроки в строке
    strChanged(int StrNum, int subStrNum); // изменено содержимое подстроки в строке

};

#endif // DISPLAY_H
