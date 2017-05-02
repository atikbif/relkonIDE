#include "codeeditor.h"
#include <QPainter>
#include <QTextBlock>
#include "leftverticalwidget.h"
#include <QPalette>
#include <QScrollBar>
#include <QAbstractSlider>
#include <QApplication>
#include <QCompleter>
#include <QAbstractItemView>
#include <QModelIndex>
#include <QAbstractItemModel>
#include "dialoggotostring.h"

/* определение и сохранение номеров текстовых блоков и их координат по вертикали */
void CodeEditor::scanBlocksNums()
{
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    numList.clear();
    while(block.isValid() && top <= viewport()->rect().bottom()) {
        if(block.isVisible() && bottom >= viewport()->rect().top()) {
            numList+=blockNumber;   // номер блока
            numList+=top;   // y координата
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
    lNumbers->updateData("lineNums",numList); // lineNums - идентификатор считанных настроек
    scanFolding();
}

CodeEditor::CodeEditor(QWidget *parent): QPlainTextEdit(parent)
{
    c = nullptr;
    releaseEnable = true;
    setLineWrapMode(QPlainTextEdit::NoWrap);
    lNumbers = new LeftVerticalWidget(this);
    connect(lNumbers,SIGNAL(sendValue(QString,int)),this,SLOT(getCmdFromChildWidget(QString,int)));

    setViewportMargins(lNumbers->width(),0,0,0);


    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this, SIGNAL(textChanged()), this , SLOT(scanFolding()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    scanBlocksNums();
    scanFolding();

    QPalette p = palette();
    p.setColor(QPalette::Highlight, QColor("black"));
    p.setColor(QPalette::HighlightedText, QColor("yellow"));
    setPalette(p);

    QScrollBar *vBar = verticalScrollBar();
    connect(vBar,SIGNAL(actionTriggered(int)),this,SLOT(handleScrollAction(int)));


    //setCenterOnScroll(true);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

/* возвращает необходимую ширину для виджета с номерами текстовых блоков */
int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1,blockCount());
    while(max>=10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * (digits+2);
    return space;
}

QString CodeEditor::getSelectedText()
{
    QTextCursor curs = textCursor();
    return curs.selectedText();
}

void CodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    scanBlocksNums();
    QRect cr = contentsRect();
    lNumbers->setGeometry(QRect(cr.left(),cr.top(),lNumbers->width(),cr.height()));
}

void CodeEditor::paintEvent(QPaintEvent *event)
{
    QPlainTextEdit::paintEvent(event);
}

void CodeEditor::mousePressEvent(QMouseEvent *event)
{
    QScrollBar *vBar = verticalScrollBar();
    vBar->setSingleStep(1);
    QPlainTextEdit::mousePressEvent(event);
    QPlainTextEdit::ensureCursorVisible();
}

void CodeEditor::updateLineNumberAreaWidth(int /*newBlockCount*/)
{
    scanBlocksNums();
    lNumbers->update();
}

/* подсветка строки с курсором */
void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if(!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::blue).lighter(190);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection,true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    Q_UNUSED(rect);
    Q_UNUSED(dy);
    scanBlocksNums();
    lNumbers->update();
}

/* поиск и сохранение фрагментов кода, допускающих сворачивание разворачивание */
void CodeEditor::scanFolding(void)
{
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    foldList.clear();
    while(block.isValid() && top <= viewport()->rect().bottom()) {
        if(block.isVisible() && bottom >= viewport()->rect().top()) {
            QRegExp rExp1("\\s*#PROCESS\\s+\\d+\\b");
            QRegExp rExp2("\\s*#DATA\\b");
            if(block.text().contains(rExp1) || block.text().contains(rExp2)) {
                if(block.next().isValid()) {
                    foldList += blockNumber;    // номер текстового блока
                    foldList += top;    // y координата
                    if(block.next().isVisible()) {
                        foldList += 1;  // блок развёрнут
                    }
                    else {
                        foldList += 0;  // блок свёрнут
                    }
                }
            }
            else {
                /* раскрытие свёрнутых блоков в случае повреждения заголовка */
                if(block.next().isValid()) {
                    if(!block.next().isVisible()) {
                        toggleFolding(block);
                    }
                }
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
    lNumbers->updateData("folding",foldList); // folding - идентификатор настроек
    lNumbers->update();
}

/* обработка сигнала, полученного от дочернего виджета */
void CodeEditor::getCmdFromChildWidget(QString code, int value)
{
    if(!code.contains("folding")) return; // сигнал на сворачивание/разворачивание блока текста
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    foldList.clear();
    while(block.isValid() && top <= viewport()->rect().bottom()) {
        if(block.isVisible() && bottom >= viewport()->rect().top()) {
            if(blockNumber==value) {
                if(block.next().isValid()) {
                    toggleFolding(block);
                }
            }
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
    scanBlocksNums();
}

void CodeEditor::foldAll()
{
    QTextBlock block = document()->findBlockByNumber(0);
    while(block.isValid()) {
        QRegExp rExp1("\\s*#PROCESS\\s+\\d+\\b");
        QRegExp rExp2("\\s*#DATA\\b");
        if(block.text().contains(rExp1) || block.text().contains(rExp2)) {
            if(block.next().isValid()) {
                if(block.next().isVisible()) {
                    toggleFolding(block);
                }
            }
        }
        block = block.next();
    }
}

void CodeEditor::unfoldAll()
{
    QTextBlock block = document()->findBlockByNumber(0);
    while(block.isValid()) {
        QRegExp rExp1("\\s*#PROCESS\\s+\\d+\\b");
        QRegExp rExp2("\\s*#DATA\\b");
        if(block.text().contains(rExp1) || block.text().contains(rExp2)) {
            if(block.next().isValid()) {
                if(!block.next().isVisible()) {
                    toggleFolding(block);
                }
            }
        }
        block = block.next();
    }
}

void CodeEditor::keyReleaseEvent(QKeyEvent *event)
{
    if(releaseEnable)
    switch(event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        {
            QTextCursor cursor = textCursor();
            QTextBlock block = cursor.block();
            block = block.previous();
            if(block.isValid()) {
                QString txt = block.text();
                for(int i=0;i<txt.size();i++) {
                    if(txt.at(i)==' ') insertPlainText(" ");
                    else if(txt.at(i)=='\t') insertPlainText("\t");
                    else break;
                }
            }
        }
        break;
    }
}


void CodeEditor::keyPressEvent(QKeyEvent *e)
{



    if (c) // do not process the shortcut when we have a completer
    {
        if (c->popup()->isVisible()) {
            // The following keys are forwarded by the completer to the widget
           switch (e->key()) {
           case Qt::Key_Enter:
           case Qt::Key_Return:
           case Qt::Key_Escape:
           case Qt::Key_Tab:
           case Qt::Key_Backtab:
                e->ignore();
                return; // let the completer do default behavior
           default:
               break;
           }
        }

        bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space); // CTRL+Space

        if (!c || !isShortcut) // do not process the shortcut when we have a completer
        {
            releaseEnable = true;

            switch(e->key()) {
            case Qt::Key_G:
                if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
                    // переход на строку по номеру
                    DialogGoToString *dialog = new DialogGoToString(this);
                    if(dialog->exec()==QDialog::Accepted) {
                        int strNum = dialog->getStrNum()-1;
                        // unfold str
                        QTextBlock block = document()->findBlockByNumber(strNum);
                        if(!block.isVisible()) {
                            while(!block.isVisible()) {
                                block = block.previous();
                                if(block.isValid()) {
                                    if(block.isVisible()) {
                                        toggleFolding(block);
                                        break;
                                    }
                                }
                            }
                        }
                        block = document()->findBlockByNumber(strNum);
                        QTextCursor cursor(block);
                        setTextCursor(cursor);
                    }
                    delete dialog;
                }
                break;
            case Qt::Key_C:
                if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
                    QTextCursor curs = textCursor();
                    if(curs.hasSelection()) QPlainTextEdit::keyPressEvent(e);
                    else {
                        int startPos = curs.position();
                        curs.movePosition(QTextCursor::StartOfBlock);
                        int pos = curs.position();
                        forever{
                            curs.setPosition(pos+1,QTextCursor::KeepAnchor);
                            if((curs.selectedText()=="\t")||(curs.selectedText()==" ")) {
                                pos++;
                                curs.setPosition(pos);
                            }
                            else break;
                        }
                        curs.setPosition(pos);
                        curs.movePosition(QTextCursor::EndOfBlock,QTextCursor::KeepAnchor);
                        setTextCursor(curs);
                        QPlainTextEdit::keyPressEvent(e);
                        curs.setPosition(startPos);
                        setTextCursor(curs);
                    }
                }else QPlainTextEdit::keyPressEvent(e);
                break;
            case Qt::Key_X:
                if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
                    QTextCursor curs = textCursor();
                    if(curs.hasSelection()) QPlainTextEdit::keyPressEvent(e);
                    else {
                        curs.movePosition(QTextCursor::StartOfBlock);
                        int pos = curs.position();
                        forever{
                            curs.setPosition(pos+1,QTextCursor::KeepAnchor);
                            if((curs.selectedText()=="\t")||(curs.selectedText()==" ")) {
                                pos++;
                                curs.setPosition(pos);
                            }
                            else break;
                        }
                        curs.setPosition(pos);
                        curs.movePosition(QTextCursor::EndOfBlock,QTextCursor::KeepAnchor);
                        setTextCursor(curs);
                        QPlainTextEdit::keyPressEvent(e);
                    }
                }else QPlainTextEdit::keyPressEvent(e);
                break;
            case Qt::Key_Insert:
                setOverwriteMode(!overwriteMode());
                break;
            case Qt::Key_Delete:
                if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
                    QTextCursor curs = textCursor();
                    curs.select(QTextCursor::BlockUnderCursor);
                    curs.removeSelectedText();
                    curs.movePosition(QTextCursor::NextBlock);
                    setTextCursor(curs);
                }else QPlainTextEdit::keyPressEvent(e);
                break;
            case Qt::Key_Home:
                {
                // выделение с фильтрацией табуляции и пробелов в начале строки
                    QTextCursor curs = textCursor();
                    if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier)) {
                        if(!curs.hasSelection())  {

                            int startPos = curs.position();
                            curs.movePosition(QTextCursor::StartOfBlock);
                            int pos = curs.position();
                            forever{
                                curs.setPosition(pos+1,QTextCursor::KeepAnchor);
                                if((curs.selectedText()=="\t")||(curs.selectedText()==" ")) {
                                    pos++;
                                    curs.setPosition(pos);
                                }
                                else break;
                            }
                            if(pos<startPos) {
                                curs.setPosition(startPos);
                                curs.setPosition(pos,QTextCursor::KeepAnchor);
                            }else curs.setPosition(startPos);
                            setTextCursor(curs);
                        }else {
                            bool startOfBlock = false;
                            QTextCursor startCurs = curs;
                            startCurs.movePosition(QTextCursor::StartOfBlock);
                            if(startCurs.position()==curs.position()) startOfBlock=true;
                            if(startOfBlock) {
                                int pos = startCurs.position();
                                forever{
                                    startCurs.setPosition(pos+1,QTextCursor::KeepAnchor);
                                    if((startCurs.selectedText()=="\t")||(startCurs.selectedText()==" ")) {
                                        pos++;
                                        startCurs.setPosition(pos);
                                        curs.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);
                                    }
                                    else break;
                                }
                            }else {
                                curs.movePosition(QTextCursor::StartOfBlock,QTextCursor::KeepAnchor);
                            }
                            setTextCursor(curs);
                        }
                    }else if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
                        QPlainTextEdit::keyPressEvent(e);
                    }else {
                        bool startOfBlock = false;
                        QTextCursor startCurs = curs;
                        startCurs.movePosition(QTextCursor::StartOfBlock);
                        if(startCurs.position()==curs.position()) startOfBlock=true;

                        int pos = startCurs.position();
                        forever{
                            startCurs.setPosition(pos+1,QTextCursor::KeepAnchor);
                            if((startCurs.selectedText()=="\t")||(startCurs.selectedText()==" ")) {
                                pos++;
                                startCurs.setPosition(pos);
                            }
                            else break;
                        }

                        if(startOfBlock) {
                            curs.setPosition(pos);
                        }else {
                            if(curs.position()==pos) curs.movePosition(QTextCursor::StartOfBlock);
                            else curs.setPosition(pos);
                        }
                        setTextCursor(curs);
                    }
                }
                break;
            case Qt::Key_Backtab:
                {
                // сдвиг строки или выделенного текста влево
                    QTextCursor curs = textCursor();

                    if(!curs.hasSelection())  {
                        int pos = curs.position();
                        curs.setPosition(pos-1, QTextCursor::KeepAnchor);
                        if((curs.selectedText()=="\t")||(curs.selectedText()==" ")) {
                            curs.removeSelectedText();
                            curs.setPosition(pos-1);
                            setTextCursor(curs);
                        }
                        return;
                    }
                    int spos = curs.anchor();
                    int epos = curs.position();

                    if(spos > epos)
                    {
                        std::swap(spos, epos);
                    }

                    curs.setPosition(spos, QTextCursor::MoveAnchor);
                    int sblock = curs.block().blockNumber();

                    curs.setPosition(epos, QTextCursor::MoveAnchor);
                    int eblock = curs.block().blockNumber();

                    curs.setPosition(spos, QTextCursor::MoveAnchor);
                    curs.beginEditBlock();

                    for(int i = 0; i <= (eblock - sblock); ++i)
                    {
                        curs.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
                        int pos = curs.position();
                        curs.setPosition(pos+1,QTextCursor::KeepAnchor);
                        if((curs.selectedText()=="\t")||(curs.selectedText()==" ")) {
                            curs.removeSelectedText();
                        }
                        curs.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
                    }

                    curs.endEditBlock();

                    // Set our cursor's selection to span all of the involved lines.

                    curs.setPosition(spos, QTextCursor::MoveAnchor);
                    curs.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);

                    while(curs.block().blockNumber() < eblock)
                    {
                        curs.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor);
                    }

                    curs.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

                    // Done!

                    setTextCursor(curs);
                }
                break;
            case Qt::Key_Tab:
                {
                // сдвиг выделенного текста вправо
                    QTextCursor curs = textCursor();

                    if(!curs.hasSelection())  {
                        QPlainTextEdit::keyPressEvent(e);
                        return;
                    }

                    // Get the first and count of lines to indent.

                    int spos = curs.anchor();
                    int epos = curs.position();

                    if(spos > epos)
                    {
                        std::swap(spos, epos);
                    }

                    curs.setPosition(spos, QTextCursor::MoveAnchor);
                    int sblock = curs.block().blockNumber();

                    curs.setPosition(epos, QTextCursor::MoveAnchor);
                    int eblock = curs.block().blockNumber();

                    // Do the indent.

                    curs.setPosition(spos, QTextCursor::MoveAnchor);
                    curs.beginEditBlock();

                    for(int i = 0; i <= (eblock - sblock); ++i)
                    {
                        curs.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);
                        curs.insertText("\t");
                        curs.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
                    }

                    curs.endEditBlock();

                    // Set our cursor's selection to span all of the involved lines.

                    curs.setPosition(spos, QTextCursor::MoveAnchor);
                    curs.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor);

                    while(curs.block().blockNumber() < eblock)
                    {
                        curs.movePosition(QTextCursor::NextBlock, QTextCursor::KeepAnchor);
                    }

                    curs.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

                    // Done!

                    setTextCursor(curs);
                }
                break;
            default:
                QPlainTextEdit::keyPressEvent(e);
                break;
            }
        }

        const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
        if (!c || (ctrlOrShift && e->text().isEmpty()))
            return;
        static QString eow("~!@#$%^&*+{}()|:\"<>?,./;'[]\\-="); // end of word
        bool hasModifier = (e->modifiers() != Qt::NoModifier);// && !ctrlOrShift;
        QString completionPrefix = textUnderCursor();

        if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                          || eow.contains(e->text().right(1)))) {
            c->popup()->hide();
            return;
        }

        if (completionPrefix != c->completionPrefix()) {
            c->setCompletionPrefix(completionPrefix);
            c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
        }
        QRect cr = cursorRect();
        cr.setWidth(c->popup()->sizeHintForColumn(0)
                    + c->popup()->verticalScrollBar()->sizeHint().width());
        c->complete(cr); // popup it up!
    }






}

void CodeEditor::handleScrollAction(int action)
{
    QScrollBar *bar = verticalScrollBar();
    if(action==QAbstractSlider::SliderMove) bar->setSingleStep(3);else bar->setSingleStep(1);
}

/* сворачивание/разворачивание текстового блока */
void CodeEditor::toggleFolding(QTextBlock &block)
{
    int startNum = block.blockNumber();
    int endNum = block.blockNumber();

    QTextBlock tmpBl = block.next();
    if(tmpBl.isValid()) {
        if(!tmpBl.isVisible()) {
            while(tmpBl.isValid()) {
                if(tmpBl.isVisible()) break;
                tmpBl.setVisible(true);
                tmpBl.setLineCount(qMax(1,block.next().layout()->lineCount()));
                tmpBl = tmpBl.next();
            }
        }
        else {
            while(tmpBl.isValid()) {
                QRegExp rExp1("\\s*#PROCESS\\s+\\d+\\b");
                QRegExp rExp2("\\s*#INIT\\b");

                if(tmpBl.text().contains(rExp1) || tmpBl.text().contains(rExp2)) break;

                QString txt = tmpBl.text();
                txt.remove(' ');
                txt.remove('\t');

                if(txt.length() && (txt.left(2) != "//")) endNum = tmpBl.blockNumber();
                tmpBl = tmpBl.next();
            }
            if(endNum>startNum) {
                QTextCursor tmpCursor = textCursor();
                tmpCursor.setVisualNavigation(true);
                tmpCursor.setPosition(document()->findBlockByNumber(startNum).position());
                setTextCursor(tmpCursor);

                startNum++;
                for(int i=startNum;i<=endNum;i++) {
                    tmpBl = document()->findBlockByNumber(i);
                    if(tmpBl.isVisible()) {
                        tmpBl.setVisible(false);
                        tmpBl.setLineCount(0);
                    }
                }
            }
        }
    }
    EditorLayout *layout = static_cast<EditorLayout *>(document()->documentLayout());
    layout->requestUpdate();
    layout->emitDocumentSizeChanged();
}

void CodeEditor::setCompleter(QCompleter *completer)
{
    if (c)
        disconnect(c, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
    c = completer;

    if (!c)
        return;

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(c, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
}

QCompleter *CodeEditor::completer() const
{
    return c;
}

void CodeEditor::insertCompletion(const QString& completion)
{
    if (c->widget() != this)
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - c->completionPrefix().length();
    //tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
    releaseEnable = false;
}

QString CodeEditor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void CodeEditor::focusInEvent(QFocusEvent *e)
{
    if (c)
        c->setWidget(this);
    QPlainTextEdit::focusInEvent(e);
}
