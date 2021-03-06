#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QTextBlockUserData>
#include <QObject>
#include "leftverticalwidget.h"
#include <QKeyEvent>

class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;

class LineNumberArea;
class QCompleter;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

    void scanBlocksNums(void);
    QString textUnderCursor() const;

public:
    explicit CodeEditor(QWidget *parent = 0);
    void toggleFolding(QTextBlock &block);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    QString getSelectedText(void);

    void setCompleter(QCompleter *c);
    QCompleter *completer() const;

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void focusInEvent(QFocusEvent *e) Q_DECL_OVERRIDE;
private slots:
    void updateLineNumberAreaWidth(int);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    void scanFolding(void);
    void getCmdFromChildWidget(QString code,int value);
    void handleScrollAction(int action);
    void insertCompletion(const QString &completion);
public slots:
    void foldAll(void);
    void unfoldAll(void);


private:
    //LineNumbersWidget *lineNumberArea;
    //QVector<int> foldBlocksNumbers;

    LeftVerticalWidget *lNumbers;
    QList<int> numList;
    QList<int> foldList;

    QCompleter *c;
    bool releaseEnable;


    // QWidget interface
protected:
    void keyReleaseEvent(QKeyEvent *event);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *e);
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
