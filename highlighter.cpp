#include "highlighter.h"
#include "highlightsettingsreader.h"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightSettingsReader reader;
    reader.parseXML();
    algs = reader.getAlgorithms();
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (HighlightAlgorithm* alg, algs) {
       alg->setInputText(text);
       alg->setAdditionPar("previousBlockState",previousBlockState());
       alg->setAdditionPar("currentBlockState",currentBlockState());
       QVector<HighlightAlgorithm::HighlightPositionInText> blocks = alg->getPosition();
       int state = alg->getAdditionPar("currentBlockState");
       if(state>=0) setCurrentBlockState(state);
       QTextCharFormat format = alg->getFormat();
       foreach (HighlightAlgorithm::HighlightPositionInText block, blocks) {
           setFormat(block.startPosition,block.length,format);
       }
    }
}

