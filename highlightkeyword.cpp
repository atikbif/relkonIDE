#include "highlightkeyword.h"
#include <QRegExp>

HighlightKeyword::HighlightKeyword(const QString &name) :HighlightAlgorithm(name)
{

}

void HighlightKeyword::addKeyWord(const QString &word)
{
    keyPatterns += QRegExp(word);
}

QVector<HighlightAlgorithm::HighlightPositionInText> HighlightKeyword::getPosition()
{
    QVector<HighlightAlgorithm::HighlightPositionInText> highlightBlocks;
    HighlightPositionInText block;

    foreach(QRegExp exp, keyPatterns) {
        int index = exp.indexIn(inpText);
        while (index >= 0) {
            int length = exp.matchedLength();
            block.startPosition = index;
            block.length = length;
            highlightBlocks += block;
            index = exp.indexIn(inpText, index + length);
        }
    }

    return highlightBlocks;
}
