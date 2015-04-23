#include "highlightbrackets.h"

HighlightBrackets::HighlightBrackets(const QString &name): HighlightAlgorithm(name)
{
    additionConf.insert("previousBlockState",0);
    additionConf.insert("currentBlockState",0);
    additionConf.insert("cursorPos",0);
}

QVector<HighlightAlgorithm::HighlightPositionInText> HighlightBrackets::getPosition()
{
    QVector<HighlightAlgorithm::HighlightPositionInText> highlightBlocks;
    return highlightBlocks;
}
