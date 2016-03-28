#include "displaywidget.h"
#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QBrush>
#include <QMenu>
#include <QApplication>
#include "dialogspessymb.h"

void DisplayWidget::destroySelection()
{
    selection.strNum = -1;
    selection.startPos = -1;
    selection.stopPos = -1;
    selection.prevXPos = -1;
    repaint();
}

DisplayWidget::DisplayWidget(Display &d, QWidget *parent) : QWidget(parent),
    displ(d)
{
    destroySelection();
    phont = new LCDPhont();
    symbInStrCount = d.getLength();
    setFocusPolicy(Qt::ClickFocus);
    setFocus();
    setContextMenuPolicy(Qt::DefaultContextMenu);
    selection.copyData.clear();
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
            if(sRect.contains(clPos)) {
                if(event->button() == Qt::LeftButton) {
                    displ.setCursor(x,y);
                    destroySelection();
                }
            }

        }
    }

}

void DisplayWidget::keyPressEvent(QKeyEvent *event)
{
    if(QApplication::keyboardModifiers() && Qt::NoModifier) destroySelection();
    if(QApplication::keyboardModifiers() && Qt::ShiftModifier) {
        if(selection.strNum!=displ.getYPosition()) {
            selection.strNum = displ.getYPosition();
            selection.startPos = selection.stopPos = displ.getXPosition();
        }
    }
    switch (event->key()) {
    case Qt::Key_Left:
        displ.moveCursorLeft();
        if(QApplication::keyboardModifiers() && Qt::ShiftModifier) {
            int x = displ.getXPosition();
            bool updFl = false;
            if(x>selection.prevXPos) {
                if(x<=selection.stopPos) {selection.startPos=x;updFl=true;}
                else if(x>selection.startPos) {selection.stopPos=x;updFl=true;}
            }else if(x<selection.prevXPos) {
                if(x<selection.startPos) {selection.startPos=x;updFl=true;}
                else if(x<selection.stopPos) {selection.stopPos=x;updFl=true;}
            }
            selection.prevXPos = x;
            if(updFl) repaint();
        }
        break;
    case Qt::Key_Right:
        displ.moveCursorRight();
        if(QApplication::keyboardModifiers() && Qt::ShiftModifier) {
            int x = displ.getXPosition();
            bool updFl = false;
            if(x>selection.prevXPos) {
                if(x<=selection.stopPos) {selection.startPos=x;updFl=true;}
                else if(x>selection.startPos) {selection.stopPos=x;updFl=true;}
            }else if(x<selection.prevXPos) {
                if(x<selection.startPos) {selection.startPos=x;updFl=true;}
                else if(x<selection.stopPos) {selection.stopPos=x;updFl=true;}
            }
            selection.prevXPos = x;
            if(updFl) repaint();
        }
        break;
    case Qt::Key_Up:
        destroySelection();
        displ.moveCursorUp();
        break;
    case Qt::Key_Down:
        destroySelection();
        displ.moveCursorDown();
        break;
    case Qt::Key_PageUp:
        destroySelection();
        displ.prevString();
        emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
        break;
    case Qt::Key_PageDown:
        destroySelection();
        displ.nextString();
        emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
        break;
    case Qt::Key_Home:
        displ.moveCursorToBegin();
        if(QApplication::keyboardModifiers() && Qt::ShiftModifier) {
            selection.startPos = 0;
            repaint();
        }else destroySelection();
        break;
    case Qt::Key_End:
        displ.moveCursorToEnd();
        if(QApplication::keyboardModifiers() && Qt::ShiftModifier) {
            selection.stopPos = displ.getLength()-1;
            repaint();
        }else destroySelection();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        destroySelection();
        displ.addEmptyStrAfter(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
        break;
    case Qt::Key_Delete:
        if (QApplication::keyboardModifiers() && Qt::ShiftModifier) {
            displ.deleteStr(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
        }else {
            destroySelection();
            displ.deleteSymbol();
        }
        break;
    case Qt::Key_Backspace:
        destroySelection();
        displ.backspace();
        break;
    case Qt::Key_Insert:
        displ.setReplaceMode(!displ.getReplaceMode());
        break;
    case Qt::Key_C:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            if(selection.strNum>=0) {
                selection.copyData.clear();
                selection.copyData = displ.getString(selection.strNum,displ.getCurSubStrNum(selection.strNum)).getString().mid(selection.startPos,selection.stopPos-selection.startPos+1);
            }
        }
        break;
    case Qt::Key_V:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            foreach (char s, selection.copyData) {
               displ.insertSymbol(s);
            }
            destroySelection();
        }
        break;
    case Qt::Key_Q:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            if(displ.getCursorString().isActive()) displ.toggleActive(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
        }
        destroySelection();
        displ.nextString();
        emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
        break;
    case Qt::Key_W:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) {
            if(!displ.getCursorString().isActive()) displ.toggleActive(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
        }
        destroySelection();
        displ.nextString();
        emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
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
    QString curID;
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

    DisplayStr cursStr = displ.getString(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));

    if(cursStr.isVarHere(displ.getXPosition())) {
        PultVarDefinition vd;
        cursStr.getVarInPos(displ.getXPosition(),vd);
        curID = vd.getId();
    }

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
                            if(vd.isExist()) {
                                if(vd.getId()==curID) painter.setBrush(QBrush(Qt::darkGreen));
                                else painter.setBrush(QBrush(Qt::blue));
                            }else {
                                painter.setBrush(QBrush(Qt::red));
                            }

                        }
                        else painter.setBrush(QBrush(Qt::black));
                        painter.setPen(penLight);
                    }else {
                        if((y==selection.strNum)&&(x>=selection.startPos)&&(x<=selection.stopPos)) {
                            painter.setBrush(QBrush(QColor(200,200,200)));
                            painter.setPen(QColor(225,225,225));
                        }else {
                            painter.setBrush(QBrush(QColor(240,240,255)));
                            painter.setPen(QColor(225,225,225));
                        }

                    }
                    /*if((y==selection.strNum)&&(x>=selection.startPos)&&(x<=selection.stopPos)) {
                        QBrush br = painter.brush();
                        QColor col = br.color();
                        col.setRed(255-col.red());
                        col.setGreen(255-col.green());
                        br.setColor(col.lighter(150));
                        painter.setBrush(br);
                    }*/
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

void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        float widthOneSymb = ((float)width()-1)/symbInStrCount;
        float heightOneSymb = ((float)height()-1)/strCount;

        for(int y=0;y<strCount;y++) {
            for(int x=0;x<symbInStrCount;x++) {
                QRectF sRect(x*widthOneSymb+1,y*heightOneSymb+1,widthOneSymb-spaceBetwSymb,heightOneSymb-spaceBetwSymb);
                QPointF clPos(event->x(),event->y());
                if(sRect.contains(clPos)) {
                    bool updFl = false;
                    if(selection.strNum == y) {
                        if(x>selection.prevXPos) {
                            if(x<=selection.stopPos) {selection.startPos=x;updFl=true;}
                            else if(x>selection.startPos) {selection.stopPos=x;updFl=true;}
                        }else if(x<selection.prevXPos) {
                            if(x<selection.startPos) {selection.startPos=x;updFl=true;}
                            else if(x<selection.stopPos) {selection.stopPos=x;updFl=true;}
                        }
                        selection.prevXPos = x;
                    }else {
                        selection.strNum = y;
                        selection.startPos = x;
                        selection.stopPos = x;
                        selection.prevXPos = x;
                        updFl=true;
                    }
                    if(updFl) repaint();
                }
            }
        }
    }
}

void DisplayWidget::contextMenuEvent(QContextMenuEvent *event)
{
    float widthOneSymb = ((float)width()-1)/symbInStrCount;
    float heightOneSymb = ((float)height()-1)/strCount;

    for(int y=0;y<strCount;y++) {
        for(int x=0;x<symbInStrCount;x++) {
            QRectF sRect(x*widthOneSymb+1,y*heightOneSymb+1,widthOneSymb-spaceBetwSymb,heightOneSymb-spaceBetwSymb);
            QPointF clPos(event->x(),event->y());
            if(sRect.contains(clPos)) {
                QMenu menu;
                QAction *copyAction = nullptr;
                QAction *pasteAction = nullptr;
                QAction *specSymbAction = nullptr;

                if((selection.strNum == y)&&(x>=selection.startPos)&&(x<=selection.stopPos)) {
                    copyAction = new QAction(QIcon(":/copy_32.ico"), "копировать текст", &menu);
                    menu.addAction(copyAction);

                }else {
                    if(selection.copyData.count()){
                        pasteAction = new QAction(QIcon(":/paste_32.ico"), "вставить текст", &menu);
                        menu.addAction(pasteAction);
                    }
                    specSymbAction = new QAction("спец. символы", &menu);
                    menu.addAction(specSymbAction);
                }
                QAction* selectedItem = menu.exec(event->globalPos());
                if(selectedItem!=nullptr) {
                    if(selectedItem==copyAction) {
                        selection.copyData.clear();
                        selection.copyData = displ.getString(y,displ.getCurSubStrNum(y)).getString().mid(selection.startPos,selection.stopPos-selection.startPos+1);
                    }else if(selectedItem==pasteAction) {
                        displ.setCursor(x,y);
                        foreach (char s, selection.copyData) {
                           displ.insertSymbol(s);
                        }
                    }else if(selectedItem==specSymbAction) {
                        DialogSpesSymb *dialog = new DialogSpesSymb();
                        dialog->exec();
                        displ.setCursor(x,y);
                        destroySelection();
                        int code = dialog->getCode();
                        if(code!=-1) displ.insertSymbol(phont->getSymbCodeinPhont(code));
                        delete dialog;
                    }
                }
            }

        }
    }


}



