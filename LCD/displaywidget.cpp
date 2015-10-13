#include "displaywidget.h"
#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QBrush>

DisplayWidget::DisplayWidget(Display &d, QWidget *parent) : QWidget(parent),
    displ(d)
{
    const QString phontFileName = "lcd_phont.rph";
    phont = new LCDPhont(phontFileName);
    QDesktopWidget desk;
    //int height = desk.availableGeometry().height()*0.2;
    //int width = height * 3.2;
    //setFixedSize(width,height);
    setFocusPolicy(Qt::ClickFocus);
    setFocus();
}

DisplayWidget::~DisplayWidget()
{
    delete phont;
}

void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
    float widthOneSymb = ((float)width()-1)/symbInStrCount;
    float heightOneSymb = ((float)height()-1)/strCount;

    for(int y=0;y<strCount;y++) {
        for(int x=0;x<symbInStrCount;x++) {
            QRectF sRect(x*widthOneSymb+1,y*heightOneSymb+1,widthOneSymb-spaceBetwSymb,heightOneSymb-spaceBetwSymb);
            QPointF clPos(event->x(),event->y());
            if(sRect.contains(clPos)) displ.setCursor(x,y);
        }
    }
}

void DisplayWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        displ.moveCursorLeft();
        break;
    case Qt::Key_Right:
        displ.moveCursorRight();
        break;
    case Qt::Key_Up:
        displ.moveCursorUp();
        break;
    case Qt::Key_Down:
        displ.moveCursorDown();
        break;
    case Qt::Key_PageUp:
        displ.prevString();
        break;
    case Qt::Key_PageDown:
        displ.nextString();
        break;
    case Qt::Key_Home:
        displ.moveCursorToBegin();
        break;
    case Qt::Key_End:
        displ.moveCursorToEnd();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        displ.addEmptyStrAfter(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
        break;
    case Qt::Key_Delete:
        displ.deleteSymbol();
        break;
    case Qt::Key_Backspace:
        displ.backspace();
        break;
    case Qt::Key_Insert:
        displ.setReplaceMode(!displ.getReplaceMode());
        break;
    default:
        QString s = event->text();
        if(!s.isEmpty()) {
            int ucdValue = s.at(0).unicode();
            if(phont->hasSymbol(ucdValue)) {
                displ.insertSymbol(phont->getSymbCodeinPhont(ucdValue));
            }
        }
        QWidget::keyPressEvent(event);
    }
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    //setFocus();
    QPainter painter(this);
    painter.save();

    QRect rect = event->rect();
    float widthOneSymb = ((float)rect.width()-1)/symbInStrCount;
    float heightOneSymb = ((float)rect.height()-1)/strCount;

    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QPen penLight(Qt::lightGray);
    QPen penDark(Qt::darkGray);
    QPen penCurs(Qt::darkGreen);
    penCurs.setWidth(3);

    for(int y=0;y<strCount;y++) {
        DisplayStr curStr = displ.getString(y,displ.getCurSubStrNum(y));
        for(int x=0;x<symbInStrCount;x++) {

            float pixWidth = (widthOneSymb - spaceBetwSymb)/phont->getColumnCount();
            float pixHeight = (heightOneSymb - spaceBetwSymb)/phont->getRowCount();
            int phCode = curStr.getSymbol(x);
            for(int pixY=0;pixY<phont->getRowCount();pixY++) {
                for(int pixX=0;pixX<phont->getColumnCount();pixX++) {
                    if(phont->getBitValue(phCode,pixY,pixX)) {
                        if(curStr.isVarHere(x)) {
                            PultVarDefinition vd;
                            curStr.getVarInPos(x,vd);
                            if(vd.getIsExist()) {
                                painter.setBrush(QBrush(Qt::blue));
                            }else {
                                painter.setBrush(QBrush(Qt::red));
                            }

                        }
                        else painter.setBrush(QBrush(Qt::black));
                        painter.setPen(penLight);
                    }else {
                        painter.setBrush(QBrush(QColor(240,240,255)));
                        painter.setPen(QColor(225,225,225));
                    }
                    QRectF pixRect(x*widthOneSymb+1+pixX*pixWidth,y*heightOneSymb+1+pixY*pixHeight,pixWidth,pixHeight);
                    painter.drawRect(pixRect);
                }
            }
            painter.setBrush(Qt::NoBrush);
            QRectF sRect(x*widthOneSymb+1,y*heightOneSymb+1,widthOneSymb-spaceBetwSymb,heightOneSymb-spaceBetwSymb);
            if((displ.getXPosition()==x)&&(displ.getYPosition()==y)) {
                if(displ.getReplaceMode()==false) penCurs.setColor(Qt::darkGray);
                    else penCurs.setColor(Qt::darkBlue);
                painter.setPen(penCurs);
            }else painter.setPen(penDark);
            painter.drawRect(sRect);
        }
    }

    painter.restore();
}


