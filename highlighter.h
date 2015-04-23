#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QHash>
#include <QTextCharFormat>
#include "highlightalgorithm.h"

class Highlighter: public QSyntaxHighlighter
{
    Q_OBJECT
    QList<HighlightAlgorithm*> algs;
public:
    Highlighter(QTextDocument *parent = 0);

protected:
     void highlightBlock(const QString &text);
};

#endif // HIGHLIGHTER_H
