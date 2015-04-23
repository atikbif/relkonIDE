#ifndef HIGHLIGHTBRACKETS_H
#define HIGHLIGHTBRACKETS_H

#include "highlightalgorithm.h"

class HighlightBrackets : public HighlightAlgorithm
{
public:
    explicit HighlightBrackets(const QString &name="");
    QVector<HighlightPositionInText> getPosition(void);
};

#endif // HIGHLIGHTBRACKETS_H
