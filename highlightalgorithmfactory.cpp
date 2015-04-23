#include "highlightalgorithmfactory.h"

HighlightAlgorithmFactory::HighlightAlgorithmFactory()
{
}

HighlightAlgorithm* HighlightAlgorithmFactory::createAlgorithm(HighlightAlgorithmFactory::AlgType type)
{
    HighlightAlgorithm* algorithm = nullptr;
    switch(type){
    case KEY_WORD:algorithm = new HighlightKeyword();break;
    case MULTILINE_COMMENTS:algorithm = new HighlightMultilineComments();break;
    case BRACKETS:algorithm = new HighlightBrackets();break;
    }
    return algorithm;
}
