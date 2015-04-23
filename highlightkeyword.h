#ifndef HIGHLIGHTKEYWORD_H
#define HIGHLIGHTKEYWORD_H

#include "highlightalgorithm.h"
#include <QStringList>
#include <QVector>
#include <QRegExp>

class HighlightKeyword : public HighlightAlgorithm
{
   QVector<QRegExp> keyPatterns;
public:
    explicit HighlightKeyword(const QString &name="");
    void addKeyWord(const QString &word);
    QVector<HighlightPositionInText> getPosition(void);
};

#endif // HIGHLIGHTKEYWORD_H
