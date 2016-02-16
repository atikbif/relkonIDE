#include "aninpslider.h"
#include <QKeyEvent>

AnInpSlider::AnInpSlider(QWidget *parent): QSlider(parent), eightBit(true)
{
    setEightBit(true);
    setPageStep(256*5);
}

void AnInpSlider::mousePressEvent(QMouseEvent *event)
{
    QSlider::mousePressEvent(event);
}

void AnInpSlider::keyPressEvent(QKeyEvent *event)
{
    int key=event->key();
    if(key==Qt::Key_Left) {
        int curValue = value();
        if(eightBit) curValue-=256;else curValue--;
        if(curValue<minimum()) curValue=minimum();
        setValue(curValue);
    }else if(key==Qt::Key_Right) {
        int curValue = value();
        if(eightBit) curValue+=256;else curValue++;
        if(curValue>maximum()) curValue=maximum();
        setValue(curValue);
    }
    event->accept();
}

void AnInpSlider::setEightBit(bool value)
{
    eightBit = value;
}
