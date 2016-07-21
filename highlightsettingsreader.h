#ifndef HIGHLIGHTSETTINGSREADER_H
#define HIGHLIGHTSETTINGSREADER_H

#include<QXmlStreamReader>
#include "highlightalgorithmfactory.h"

/* read highlight settings from xml file */

class QTextCharFormat;
class QXmlStreamAttributes;
#include "ColTable/colorlist.h"

class HighlightSettingsReader
{
    const QString fName;
    QList<HighlightAlgorithm*> algs;
    ColorList cList;

    static QTextCharFormat parseFormat(const QXmlStreamAttributes &attributes);
    static QString parsePattern(QXmlStreamReader &xml);
    HighlightAlgorithm* parseAlgorithm(QXmlStreamReader &xml);
public:
    HighlightSettingsReader();
    int parseXML(void);
    QList<HighlightAlgorithm*> getAlgorithms();
};

#endif // HIGHLIGHTSETTINGSREADER_H
