#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include "lcdphont.h"
#include "display.h"

class DisplayWidget : public QWidget
{
    Q_OBJECT
    LCDPhont* phont;
    static const int strCount = 4;
    static const int symbInStrCount = 20;
    static const int spaceBetwSymb = 3;
    Display& displ;
public:
    explicit DisplayWidget(Display& d, QWidget *parent = 0);
    ~DisplayWidget();

signals:

public slots:

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // DISPLAYWIDGET_H
