#include "highlightmultilinecomments.h"
#include <QRegExp>

HighlightMultilineComments::HighlightMultilineComments(const QString &name): HighlightAlgorithm(name)
{
    additionConf.insert("previousBlockState",0);
    additionConf.insert("currentBlockState",0);
}

void HighlightMultilineComments::setStartPattern(const QString &pattern)
{
    startPattern = pattern;
}

void HighlightMultilineComments::setEndPattern(const QString &pattern)
{
    endPattern = pattern;
}

QVector<HighlightAlgorithm::HighlightPositionInText> HighlightMultilineComments::getPosition()
{
    QVector<HighlightAlgorithm::HighlightPositionInText> highlightBlocks;
    HighlightPositionInText block;
    QRegExp commentStartExpression(startPattern);
    QRegExp commentEndExpression(endPattern);

    additionConf.insert("currentBlockState",0);
    int startIndex = 0;
    if (additionConf.value("previousBlockState") != 1)
        startIndex = commentStartExpression.indexIn(inpText);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(inpText, startIndex);
        int commentLength;
        if (endIndex == -1) {
            additionConf.insert("currentBlockState",1);
            commentLength = inpText.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                         + commentEndExpression.matchedLength();
        }
        block.startPosition = startIndex;
        block.length = commentLength;
        highlightBlocks += block;
        startIndex = commentStartExpression.indexIn(inpText, startIndex + commentLength);
    }
    return highlightBlocks;
}
