#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

// виджет имитации дисплея с возможностью ввода данных

#include <QWidget>
#include "lcdphont.h"
#include "display.h"

class DisplayWidget : public QWidget
{
    Q_OBJECT
    LCDPhont* phont;
    static const int strCount = 4;
    static const int spaceBetwSymb = 3;
    int symbInStrCount;

    Display& displ;
    struct {
        int strNum;
        int startPos;
        int stopPos;
        int prevXPos;
        QByteArray copyData;
    }selection;

    struct {
        int strNum;
        int startPos;
        QString pat;
    }patMem;

    void justKey(QKeyEvent *event); // обработка стандартных клавиш
    void destroySelection(void);
    void destroyPatternMem(void);
public:
    explicit DisplayWidget(Display& d, QWidget *parent = 0);
    const LCDPhont&  getPhont(void) const {return *phont;}

    ~DisplayWidget();

signals:
    void patternUpdate(const QString &varPattern, int startPos);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);


    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *event);

    // QWidget interface
protected:

    // QWidget interface
protected:
    void contextMenuEvent(QContextMenuEvent *event);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event);
};

#endif // DISPLAYWIDGET_H
