#ifndef HIGHLIGHTALGORITHMFACTORY_H
#define HIGHLIGHTALGORITHMFACTORY_H

#include "highlightkeyword.h"
#include "highlightmultilinecomments.h"
#include "highlightbrackets.h"

class HighlightAlgorithmFactory
{
    HighlightAlgorithmFactory();
public:
    enum AlgType {KEY_WORD,MULTILINE_COMMENTS,BRACKETS};
    static HighlightAlgorithm* createAlgorithm(AlgType type);
};

#endif // HIGHLIGHTALGORITHMFACTORY_H
