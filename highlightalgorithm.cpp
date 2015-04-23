#include "highlightalgorithm.h"

HighlightAlgorithm::HighlightAlgorithm(const QString &name): algName(name)
{
}

int HighlightAlgorithm::getAdditionPar(const QString &parName)
{
    if(additionConf.keys().contains(parName)) {
        return additionConf.value(parName);
    }
    return -1;
}

int HighlightAlgorithm::setAdditionPar(const QString &parName, int parValue)
{
    if(additionConf.keys().contains(parName)) {
        additionConf.insert(parName, parValue);
        return 0;
    }
    return -1;
}

const QString HighlightAlgorithm::getAlgName() const
{
    return algName;
}

void HighlightAlgorithm::setAlgName(const QString &name)
{
    algName = name;
}

void HighlightAlgorithm::setInputText(const QString &textValue)
{
    inpText = textValue;
}

void HighlightAlgorithm::setFormat(const QTextCharFormat &algFormat)
{
    format = algFormat;
}

QTextCharFormat HighlightAlgorithm::getFormat() const
{
    return format;
}
