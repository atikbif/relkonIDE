#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QTextBlockUserData>
#include <QObject>
#include "leftverticalwidget.h"

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

    void scanBlocksNums(void);

public:
    explicit CodeEditor(QWidget *parent = 0);
    void toggleFolding(QTextBlock &block);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void updateLineNumberAreaWidth(int);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    void scanFolding(void);
    void getCmdFromChildWidget(QString code,int value);
public slots:
    void foldAll(void);
    void unfoldAll(void);


private:
    //LineNumbersWidget *lineNumberArea;
    //QVector<int> foldBlocksNumbers;

    LeftVerticalWidget *lNumbers;
    QList<int> numList;
    QList<int> foldList;
};

class LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(),0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

class EditorLayout : public QPlainTextDocumentLayout
{
    Q_OBJECT

public:
    explicit EditorLayout(QTextDocument *document) : QPlainTextDocumentLayout(document) {
    }

    void emitDocumentSizeChanged() {
        emit documentSizeChanged(documentSize());
    }
};

class BlockInfo : public QTextBlockUserData
{
    QString descr;
public:
    explicit BlockInfo(QString description) : QTextBlockUserData(), descr(description) {
    }

    const QString getDescription() {
        return descr;
    }
};

#endif // CODEEDITOR_H
