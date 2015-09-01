#include <gtest/gtest.h>
#include "display.h"
#include "lcdtest.h"
#include "displaystr.h"

TEST_F(LCDTest,initLCD) {
    Display d;
    ASSERT_EQ(4,d.getStrCount());   // проверка формата дисплея
    ASSERT_EQ(20,d.getLength());
    for(int i=0;i<d.getStrCount();i++) {
        ASSERT_EQ(1,d.getSubStrCount(i));   // по одной подстроке в каждой строке
        ASSERT_EQ(0,d.getCurSubStrNum(i));  // текущие строки должны быть с индексом 0
        DisplayStr str = d.getString(i,0);
        for(int j=0;j<d.getLength();j++) {
            ASSERT_EQ(0x20,str.getSymbol(j));   // строки заполнены пробелами
        }
    }
}

TEST_F(LCDTest,addRemoveStrings) {
    Display d;
    // проверка добавления строк
    for(int i=0;i<1000;i++) {
        d.addEmptyStrAfter(0,d.getSubStrCount(0)-1);
        d.addEmptyStrAfter(1,d.getSubStrCount(1)-1);
        d.addEmptyStrAfter(1,d.getSubStrCount(1)-1);
        d.addEmptyStrAfter(2,d.getSubStrCount(2)-1);
        d.addEmptyStrAfter(2,d.getSubStrCount(2)-1);
        d.addEmptyStrAfter(2,d.getSubStrCount(2)-1);
        d.addEmptyStrAfter(3,d.getSubStrCount(3)-1);
        d.addEmptyStrAfter(3,d.getSubStrCount(3)-1);
        d.addEmptyStrAfter(3,d.getSubStrCount(3)-1);
        d.addEmptyStrAfter(3,d.getSubStrCount(3)-1);
    }
    ASSERT_EQ(1001,d.getSubStrCount(0));
    ASSERT_EQ(2001,d.getSubStrCount(1));
    ASSERT_EQ(3001,d.getSubStrCount(2));
    ASSERT_EQ(4001,d.getSubStrCount(3));
    // проверка удаления строк
    while(d.getSubStrCount(0)>1) d.deleteStr(0,0);
    while(d.getSubStrCount(1)>1) d.deleteStr(1,0);
    while(d.getSubStrCount(2)>1) d.deleteStr(2,0);
    while(d.getSubStrCount(3)>1) d.deleteStr(3,0);
    ASSERT_EQ(1,d.getSubStrCount(0));
    ASSERT_EQ(1,d.getSubStrCount(1));
    ASSERT_EQ(1,d.getSubStrCount(2));
    ASSERT_EQ(1,d.getSubStrCount(3));
    // проверка контроля входных параметров
    ASSERT_FALSE(d.deleteStr(0,-1));
    ASSERT_FALSE(d.deleteStr(-1,0));
    ASSERT_FALSE(d.deleteStr(0,0));
    ASSERT_FALSE(d.addEmptyStrAfter(0,-1));
    ASSERT_FALSE(d.addEmptyStrBefore(0,-1));
    ASSERT_FALSE(d.addEmptyStrAfter(5,0));
    ASSERT_FALSE(d.addEmptyStrBefore(5,0));
    ASSERT_FALSE(d.addEmptyStrAfter(0,2));
    ASSERT_FALSE(d.addEmptyStrBefore(0,2));
    // проверка порядка вставки строк
    d.goToStr(0,0);
    d.insertSymbol(0x01);
    d.addEmptyStrBefore(0,0);
    d.insertSymbol(0x02);
    d.addEmptyStrAfter(0,0);
    d.insertSymbol(0x03);
    d.goToStr(0,0);
    ASSERT_EQ(0x02,d.getCursorString().getSymbol(0));
    d.goToStr(0,1);
    ASSERT_EQ(0x03,d.getCursorString().getSymbol(0));
    d.goToStr(0,2);
    ASSERT_EQ(0x01,d.getCursorString().getSymbol(0));
}

TEST_F(LCDTest,addRemoveVars) {
    Display d;
    VarPattern vp1("1","123");
    VarPattern vp2("2","123.45");
    VarPattern vp3("3","12345678");
    VarPattern vp4("4","-123.45");
    VarPattern vp5("5","-255");
    VarPattern vp6("6","0.0000056");
    VarPattern vp7("7","123,45");
    VarPattern vp8("8","abc");
    VarPattern vp9("9","123f");
    VarPattern vp10("10","12d3.4");
    ASSERT_TRUE(vp1.checkPattern());
    ASSERT_TRUE(vp2.checkPattern());
    ASSERT_FALSE(vp3.checkPattern());   // TOO LONG (only 7 digits)
    ASSERT_TRUE(vp4.checkPattern());
    ASSERT_TRUE(vp5.checkPattern());
    ASSERT_FALSE(vp6.checkPattern());   // TOO LONG (only 7 digits)
    ASSERT_TRUE(vp7.checkPattern());
    ASSERT_FALSE(vp8.checkPattern());   // incorrect symbols
    ASSERT_FALSE(vp9.checkPattern());   // incorrect symbols
    ASSERT_FALSE(vp10.checkPattern());  // incorrect symbols

    d.goToStr(0,0);
    ASSERT_TRUE(d.addVar(vp1));
    ASSERT_EQ(vp1.getLength(),d.getXPosition());    // проверка смещения курсора
    d.moveCursorLeft();
    ASSERT_FALSE(d.addVar(vp2)); // пересечение областей переменных
    d.setCursor(10,0);
    ASSERT_FALSE(d.addVar(vp3));    // добавление переменной с некорректным шаблоном
    ASSERT_TRUE(d.addVar(vp4));
    ASSERT_EQ(2,d.getCursorString().getVarsCount());
    vPatt v1,v2;
    ASSERT_TRUE(d.getCursorString().getVar(0,v1));
    ASSERT_TRUE(d.getCursorString().getVar(1,v2));
    ASSERT_EQ(0,v1.pos);
    ASSERT_EQ(10,v2.pos);
    d.setCursor(0,0);
    d.deleteSymbol();  // удаление переменной
    ASSERT_TRUE(d.getCursorString().getVar(0,v1));
    ASSERT_EQ(1,d.getCursorString().getVarsCount());  // осталась только одна переменная
    ASSERT_EQ(10-vp1.getLength(),v1.pos);  // координаты второй сместились влево на ширину первой
    d.setCursor(0,0);
    for(int i=0;i<d.getLength();i++) d.deleteSymbol(); // очистка строки
    // проверка на заполнение очищенной строки пробелами
    for(int i=0;i<d.getLength();i++) {
        ASSERT_EQ(0x20,d.getCursorString().getSymbol(i));
    }
    // проверка на отсутствие места при добавлении переменной
    d.setCursor(5,0);
    for(int i=0;i<15;i++) {
        d.insertSymbol('+');
    }
    d.setCursor(3,0);
    ASSERT_FALSE(d.addVar(vp1));
}

TEST_F(LCDTest,addRemoveSymbols) {
    Display d;
    for(int i=0;i<d.getLength();i++) {
        d.insertSymbol(i);
    }
    d.setCursor(0,0);
    for(int i=0;i<d.getLength();i++) {
        ASSERT_EQ(i,d.getCursorString().getSymbol(i));
    }
    ASSERT_FALSE(d.insertSymbol(0x01)); // нет свободного места
    d.setReplaceMode(true);
    ASSERT_TRUE(d.insertSymbol(0x01));  // перезапись в режиме вставки
    d.setCursor(0,0);
    ASSERT_EQ(0x01,d.getCursorString().getSymbol(0));
    d.setReplaceMode(false);
    d.deleteSymbol();   // освобождение места для вставки нового символа
    ASSERT_EQ(0,d.getXPosition());  // курсор должен остаться на своём месте
    ASSERT_TRUE(d.insertSymbol(0x00));
    ASSERT_EQ(1,d.getXPosition());  // курсор должен сместиться на одну позицию вправо
    // проверка вставки символов поверх переменных
    d.setCursor(0,1);
    VarPattern vp1("1","123");
    d.setReplaceMode(true);
    d.addVar(vp1);
    d.setCursor(1,0);
    ASSERT_FALSE(d.insertSymbol(0x00));
    d.setCursor(1,1);
    ASSERT_FALSE(d.insertSymbol(0x00));

    // вставка символа на первом элементе переменной приводит к сдвигу переменной
    // только в режиме вставки
    d.setReplaceMode(false);
    d.setCursor(1,1);
    ASSERT_FALSE(d.insertSymbol(0x00));
    d.setCursor(1,0);
    ASSERT_TRUE(d.insertSymbol(0x00));
    vPatt v;
    ASSERT_TRUE(d.getCursorString().getVar(0,v));
    ASSERT_EQ(0x01,v.pos);
}

TEST_F(LCDTest,copyPaste) {
    Display d;
    for(int i=0;i<5;i++) d.insertSymbol(i);
    d.setCursor(10,0);
    VarPattern vp1("1","123");
    d.addVar(vp1);
    d.copyStrToBuffer(0,0);
    d.pasteStrFromBuffer(1,0);
    // курсор должен поменять указывать на вставленную строку
    ASSERT_EQ(1,d.getYPosition());
    ASSERT_EQ(0,d.getXPosition());
    ASSERT_EQ(1,d.getSubStrCount(1)); // количество строк не должно поменяться
    // проверка содержимого вставленной строки
    for(int i=0;i<d.getLength();i++) {
        ASSERT_EQ(d.getString(0,0).getSymbol(i),d.getCursorString().getSymbol(i));
    }
    // проверка копирования переменных
    ASSERT_EQ(d.getString(0,0).getVarsCount(),d.getCursorString().getVarsCount());
    ASSERT_EQ(1,d.getCursorString().getVarsCount());
    DisplayStr copyStr = d.getString(0,0);
    DisplayStr pasteStr = d.getCursorString();
    vPatt v1,v2;
    ASSERT_TRUE(copyStr.getVar(0,v1));
    ASSERT_TRUE(pasteStr.getVar(0,v2));
    ASSERT_EQ(v1.pos,v2.pos);
    ASSERT_STREQ(v1.variable.getVarID().toStdString().c_str(),v2.variable.getVarID().toStdString().c_str());
    ASSERT_STREQ(v1.variable.getPattern().toStdString().c_str(),v2.variable.getPattern().toStdString().c_str());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
