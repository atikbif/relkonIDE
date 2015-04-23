#ifndef HIGHLIGHTMULTILINECOMMENTS_H
#define HIGHLIGHTMULTILINECOMMENTS_H

#include "highlightalgorithm.h"
#include <QString>

class HighlightMultilineComments : public HighlightAlgorithm
{
    QString startPattern;
    QString endPattern;
public:
    explicit HighlightMultilineComments(const QString &name="");
    void setStartPattern(const QString &pattern);
    void setEndPattern(const QString &pattern);
    QVector<HighlightPositionInText> getPosition(void);
};

#endif // HIGHLIGHTMULTILINECOMMENTS_H
