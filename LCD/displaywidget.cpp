#include "displaywidget.h"
#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
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

void DisplayWidget::destroyPatternMem()
{
    patMem.strNum = -1;
    patMem.startPos = -1;
    patMem.pat = "";
    emit patternUpdate("",-1);
}

void DisplayWidget::justKey(QKeyEvent *event)
{
    QString s = event->text();
    if(!s.isEmpty()) {
        int ucdValue = s.at(0).unicode();
        if(phont->hasSymbol(ucdValue)) {
            if(displ.insertSymbol(phont->getSymbCodeinPhont(ucdValue))) {
                if(((event->key()>=0x30)&&(event->key()<=0x39))||(event->text()==".")) {
                    if(patMem.strNum!=-1) {
                        patMem.pat+=event->text();
                        emit patternUpdate(patMem.pat, patMem.startPos);
                    }else {
                        patMem.strNum = displ.getYPosition();
                        patMem.startPos = displ.getXPosition()-1;
                        patMem.pat = event->text();
                        emit patternUpdate(patMem.pat, patMem.startPos);
                    }
                }else destroyPatternMem();
            }else if(patMem.strNum!=-1) destroyPatternMem();
        }
    }
    QWidget::keyPressEvent(event);
}

DisplayWidget::DisplayWidget(Display &d, QWidget *parent) : QWidget(parent),
    displ(d)
{
    destroySelection();
    destroyPatternMem();
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
            QRectF sRect(x*widthOneSymb+1,y*heightOneSymb+1,widthOneSymb,heightOneSymb);
            QPointF clPos(event->x(),event->y());
            if(sRect.contains(clPos)) {
                if(event->button() == Qt::LeftButton) {
                    displ.setCursor(x,y);
                    destroySelection();
                }
            }

        }
    }
    destroyPatternMem();
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
        if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
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
        }else if(selection.strNum!=-1) destroySelection();
        if(patMem.strNum!=-1) destroyPatternMem();

        break;
    case Qt::Key_Right:
        displ.moveCursorRight();
        if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
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
        }else if(selection.strNum!=-1) destroySelection();
        if(patMem.strNum!=-1) destroyPatternMem();
        break;
    case Qt::Key_Up:
        destroySelection();
        displ.moveCursorUp();
        if(patMem.strNum!=-1) destroyPatternMem();
        if(selection.strNum!=-1) destroySelection();
        break;
    case Qt::Key_Down:
        destroySelection();
        displ.moveCursorDown();
        if(patMem.strNum!=-1) destroyPatternMem();
        if(selection.strNum!=-1) destroySelection();
        break;
    case Qt::Key_PageUp:
        destroySelection();
        displ.prevString();
        emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
        if(patMem.strNum!=-1) destroyPatternMem();
        if(selection.strNum!=-1) destroySelection();
        break;
    case Qt::Key_PageDown:
        destroySelection();
        displ.nextString();
        emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
        if(patMem.strNum!=-1) destroyPatternMem();
        if(selection.strNum!=-1) destroySelection();
        break;
    case Qt::Key_Home:
        displ.moveCursorToBegin();
        if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
            selection.startPos = 0;
            repaint();
        }else destroySelection();
        if(patMem.strNum!=-1) destroyPatternMem();
        break;
    case Qt::Key_End:
        displ.moveCursorToEnd();
        if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
            selection.stopPos = displ.getLength()-1;
            repaint();
        }else destroySelection();
        if(patMem.strNum!=-1) destroyPatternMem();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        destroySelection();
        displ.addEmptyStrAfter(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
        if(patMem.strNum!=-1) destroyPatternMem();
        break;
    case Qt::Key_Delete:
        if (QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
            displ.deleteStr(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
        }else {
            if((selection.strNum>=0)&&(selection.startPos!=selection.stopPos)) {
                int begPos = (selection.startPos<selection.stopPos)?selection.startPos:selection.stopPos;
                int endPos = (selection.stopPos>selection.startPos)?selection.stopPos:selection.startPos;
                int delta = endPos - begPos + 1;
                displ.setCursor(begPos,displ.getYPosition());
                int delCnt = 0;
                while(delCnt<delta) {
                    int cnt = displ.deleteSymbol();
                    if(cnt==0) break;
                    delCnt+=cnt;
                }
                destroySelection();
            }else displ.deleteSymbol();
        }
        if(patMem.strNum!=-1) destroyPatternMem();
        break;
    case Qt::Key_Backspace:
        if((selection.strNum>=0)&&(selection.startPos!=selection.stopPos)) {
            int begPos = (selection.startPos<selection.stopPos)?selection.startPos:selection.stopPos;
            int endPos = (selection.stopPos>selection.startPos)?selection.stopPos:selection.startPos;
            int delta = endPos - begPos + 1;
            displ.setCursor(begPos,displ.getYPosition());
            int delCnt = 0;
            while(delCnt<delta) {
                int cnt = displ.deleteSymbol();
                if(cnt==0) break;
                delCnt+=cnt;
            }
            destroySelection();
        }
        displ.backspace();
        if(patMem.strNum!=-1) {
            patMem.pat = patMem.pat.remove(patMem.pat.length()-1,1);
            emit patternUpdate(patMem.pat, patMem.startPos);
        }
        break;
    case Qt::Key_Insert:
        displ.setReplaceMode(!displ.getReplaceMode());
        break;
    case Qt::Key_C:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            displ.clearCopyStrList();
            if((selection.strNum>=0)&&(selection.startPos!=selection.stopPos)) {
                selection.copyData.clear();
                int begPos = (selection.startPos<selection.stopPos)?selection.startPos:selection.stopPos;
                int endPos = (selection.stopPos>selection.startPos)?selection.stopPos:selection.startPos;
                int delta = endPos - begPos + 1;

                selection.copyData = displ.getString(selection.strNum,displ.getCurSubStrNum(selection.strNum)).getString().mid(begPos,delta);
                displ.setCopySubject(true);
            }else {
                displ.copyStrToBuffer(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
            }
        }else justKey(event);
        break;
    case Qt::Key_X:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            displ.clearCopyStrList();
            if((selection.strNum>=0)&&(selection.startPos!=selection.stopPos)) {
                selection.copyData.clear();
                int begPos = (selection.startPos<selection.stopPos)?selection.startPos:selection.stopPos;
                int endPos = (selection.stopPos>selection.startPos)?selection.stopPos:selection.startPos;
                int delta = endPos - begPos + 1;
                selection.copyData = displ.getString(selection.strNum,displ.getCurSubStrNum(selection.strNum)).getString().mid(begPos,delta);
                displ.setCopySubject(true);
                displ.setCursor(begPos,displ.getYPosition());
                int delCnt = 0;
                while(delCnt<delta) {
                    int cnt = displ.deleteSymbol();
                    if(cnt==0) break;
                    delCnt+=cnt;
                }
                destroySelection();
            }else {
                displ.copyStrToBuffer(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
                displ.deleteStr(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
            }
        }else justKey(event);
        if(patMem.strNum!=-1) destroyPatternMem();
        break;
    case Qt::Key_V:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            if(displ.getCopySubject()==false) {
                displ.addEmptyStrBefore(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
                displ.pasteStrFromBuffer(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
            }else {
                UndoRedoOperation op(displ);
                op.setOperationType(UndoRedoOperation::ReplaceString);
                op.setStartCursor(displ.getXPosition(),displ.getYPosition());
                op.setStartStr(displ.getCursorString());
                op.setStrNum(displ.getYPosition());
                op.setSubStrNum(displ.getCurSubStrNum(displ.getYPosition()));

                if((selection.strNum>=0)&&(selection.startPos!=selection.stopPos)) {
                    int begPos = (selection.startPos<selection.stopPos)?selection.startPos:selection.stopPos;
                    int endPos = (selection.stopPos>selection.startPos)?selection.stopPos:selection.startPos;
                    int delta = endPos - begPos + 1;
                    int delCnt = 0;
                    displ.setCursor(begPos,displ.getYPosition());
                    while(delCnt<delta) {
                        int cnt = displ.deleteSymbol();
                        if(cnt==0) break;
                        delCnt+=cnt;
                    }
                    destroySelection();
                }

                foreach (char s, selection.copyData) {
                   displ.insertSymbol(s,false);
                }
                op.setResCursor(displ.getXPosition(),displ.getYPosition());
                op.setResStr(displ.getCursorString());
                displ.addOperation(op);
            }
            destroySelection();
        }else justKey(event);
        if(patMem.strNum!=-1) destroyPatternMem();
        break;
    case Qt::Key_Q:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            if(displ.getCursorString().isActive()) displ.toggleActive(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
            destroySelection();
            displ.nextString();
            emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
            if(patMem.strNum!=-1) destroyPatternMem();
        }else justKey(event);
        break;
    case Qt::Key_W:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            if(!displ.getCursorString().isActive()) displ.toggleActive(displ.getYPosition(),displ.getCurSubStrNum(displ.getYPosition()));
            destroySelection();
            displ.nextString();
            emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
            if(patMem.strNum!=-1) destroyPatternMem();
        }else justKey(event);
        break;
    case Qt::Key_Z:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            displ.undo();
        }else justKey(event);
        if(patMem.strNum!=-1) destroyPatternMem();
        break;
    case Qt::Key_Y:
        if (QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            displ.redo();
        }else justKey(event);
        if(patMem.strNum!=-1) destroyPatternMem();
        break;
    default:
        if (event->key()<=0xFFFF) {
            if((selection.strNum>=0)&&(selection.startPos!=selection.stopPos)) {
                int begPos = (selection.startPos<selection.stopPos)?selection.startPos:selection.stopPos;
                int endPos = (selection.stopPos>selection.startPos)?selection.stopPos:selection.startPos;
                int delta = endPos - begPos + 1;
                int delCnt = 0;
                displ.setCursor(begPos,displ.getYPosition());
                while(delCnt<delta) {
                    int cnt = displ.deleteSymbol();
                    if(cnt==0) break;
                    delCnt+=cnt;
                }
                destroySelection();
            }
            destroySelection();
        }
        justKey(event);



    }
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    QString curID;
    QPainter painter(this);
    painter.save();

    QRect rect = event->rect();

    float widthOneSymb = ((float)rect.width()-10)/symbInStrCount;
    float heightOneSymb = ((float)rect.height()-10)/strCount;

    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    QPen penLight(Qt::lightGray);
    QPen penDark(Qt::darkBlue);
    penDark.setWidth(3);
    QPen penCurs(Qt::black);
    penCurs.setWidth(1);

    painter.setBrush(QBrush(QColor(220,220,220)));
    painter.setPen(penDark);
    painter.drawRect(rect);

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
                            painter.setBrush(QBrush(QColor(150,150,150)));
                            painter.setPen(QColor(150,150,150));
                        }else {
                            if((displ.getXPosition()==x)&&(displ.getYPosition()==y)) {
                                if(displ.getReplaceMode()==false) {
                                    painter.setBrush(QBrush(QColor(250,240,200)));
                                    painter.setPen(QColor(225,225,225));
                                }else {
                                    painter.setBrush(QBrush(QColor(240,200,200)));
                                    painter.setPen(QColor(225,225,225));
                                }
                            }else {
                                painter.setBrush(QBrush(QColor(240,240,255)));
                                painter.setPen(QColor(225,225,225));
                            }
                        }

                    }
                    QRectF pixRect(x*widthOneSymb+5+pixX*pixWidth,y*heightOneSymb+5+pixY*pixHeight,pixWidth,pixHeight);
                    painter.drawRect(pixRect);
                }
            }
            painter.setBrush(Qt::NoBrush);
            QRectF sRect(x*widthOneSymb+5,y*heightOneSymb+5,widthOneSymb-spaceBetwSymb,heightOneSymb-spaceBetwSymb);
            if((displ.getXPosition()==x)&&(displ.getYPosition()==y)) {
                painter.setPen(penCurs);
                painter.drawRect(sRect);
            }
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

    destroyPatternMem();

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
                        int begPos = (selection.startPos<selection.stopPos)?selection.startPos:selection.stopPos;
                        int endPos = (selection.stopPos>selection.startPos)?selection.stopPos:selection.startPos;
                        int delta = endPos - begPos + 1;
                        selection.copyData = displ.getString(y,displ.getCurSubStrNum(y)).getString().mid(begPos,delta);
                        displ.setCopySubject(true);
                    }else if(selectedItem==pasteAction) {
                        displ.setCursor(x,y);
                        UndoRedoOperation op(displ);
                        op.setOperationType(UndoRedoOperation::ReplaceString);
                        op.setStartCursor(displ.getXPosition(),displ.getYPosition());
                        op.setStartStr(displ.getCursorString());
                        op.setStrNum(displ.getYPosition());
                        op.setSubStrNum(displ.getCurSubStrNum(displ.getYPosition()));
                        foreach (char s, selection.copyData) {
                           displ.insertSymbol(s,false);
                        }
                        op.setResCursor(displ.getXPosition(),displ.getYPosition());
                        op.setResStr(displ.getCursorString());
                        displ.addOperation(op);
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

void DisplayWidget::wheelEvent(QWheelEvent *event)
{
    destroySelection();
    destroyPatternMem();
    QPoint numDegrees = event->angleDelta() / 8;
    if(numDegrees.ry()>=5) {
        destroySelection();
        displ.prevString();
        emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
    }else if(numDegrees.ry()<-5) {
        destroySelection();
        displ.nextString();
        emit displ.cursorPosChanged(displ.getXPosition(),displ.getYPosition());
    }
}



