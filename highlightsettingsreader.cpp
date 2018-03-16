#include "highlightsettingsreader.h"
#include <QFile>
#include <QApplication>
#include <QTextCodec>
#include <QSharedPointer>

HighlightSettingsReader::HighlightSettingsReader(): fName("highlight.xml")
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
    cList = ColorList::readUserColors();
}

QTextCharFormat HighlightSettingsReader::parseFormat(const QXmlStreamAttributes &attributes)
{
    QTextCharFormat format;
    QColor color(Qt::green);
    if(attributes.hasAttribute("red")) {
        color.setRed(attributes.value("red").toInt());
    }
    if(attributes.hasAttribute("green")) {
        color.setGreen(attributes.value("green").toInt());
    }
    if(attributes.hasAttribute("blue")) {
        color.setBlue(attributes.value("blue").toInt());
    }
    if(attributes.hasAttribute("italic")) {
        if(attributes.value("italic").toString()=="true") format.setFontItalic(true);
    }
    if(attributes.hasAttribute("weight")) {
        if(attributes.value("weight").toString()=="true") format.setFontWeight(QFont::Bold);
    }
    format.setForeground(QBrush(color));
    return format;
}

QString HighlightSettingsReader::parsePattern(QXmlStreamReader &xml)
{
    if(xml.tokenType() != QXmlStreamReader::StartElement) return QString();
    xml.readNext();
    if(xml.tokenType() != QXmlStreamReader::Characters) return QString();
    return xml.text().toString();
}

int HighlightSettingsReader::parseXML()
{
    QFile* file = new QFile(QApplication::applicationDirPath() + "/" + fName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return -1;
    }
    QXmlStreamReader xml(file);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "highlightings") {
                continue;
            }
            if(xml.name() == "highlight") {
                HighlightAlgorithm* alg = parseAlgorithm(xml);
                if(alg != nullptr) algs += alg;
            }
        }
    }
    if(xml.hasError()) {
        return -1;
    }
    xml.clear();
    ColorList::writeUserColors(cList);
    return 0;
}

QList<HighlightAlgorithm *> HighlightSettingsReader::getAlgorithms()
{
    return algs;
}

HighlightAlgorithm* HighlightSettingsReader::parseAlgorithm(QXmlStreamReader &xml)
{
    HighlightAlgorithm* alg = nullptr;
    if(xml.tokenType() != QXmlStreamReader::StartElement &&
                xml.name() == "highlight") {
        return nullptr;
    }
    QXmlStreamAttributes attributes = xml.attributes();
    if(attributes.hasAttribute("type")) {
        QString algType = attributes.value("type").toString();
        if(algType.toLower()=="key word") {
            alg = HighlightAlgorithmFactory::createAlgorithm(HighlightAlgorithmFactory::KEY_WORD);
        }else if(algType.toLower()=="multiline comments") {
            alg = HighlightAlgorithmFactory::createAlgorithm(HighlightAlgorithmFactory::MULTILINE_COMMENTS);
        }else if(algType.toLower()=="brackets") {
            alg = HighlightAlgorithmFactory::createAlgorithm(HighlightAlgorithmFactory::BRACKETS);
        }
    }
    QString descr;
    if(attributes.hasAttribute("description")) {
        descr = attributes.value("description").toString();
        if(alg != nullptr) alg->setAlgName(descr);
    }
    alg->setFormat(parseFormat(attributes));

    if(!descr.isEmpty()) {
        QSharedPointer<ColorForWord> cw = cList.getColor(descr);
        QColor col = alg->getFormat().foreground().color();
        if(cw->getCodeWord()!=cw->getDefaultName()) {
            cw->setSysRed(col.red());
            cw->setSysGreen(col.green());
            cw->setSysBlue(col.blue());
            if(!cw->isSystem()) {
                int red = cw->getUserRed();
                int green = cw->getUserGreen();
                int blue = cw->getUserBlue();
                col = QColor(red,green,blue);
                QTextCharFormat f = alg->getFormat();
                f.setForeground(QBrush(col));
                alg->setFormat(f);
            }
        }else {
            cList.addColor(descr,col.red(),col.green(),col.blue());
        }
    }

    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
                xml.name() == "highlight")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            if(xml.name() == "pattern") {
                QString pattern = parsePattern(xml);
                HighlightKeyword* keyWordAlg = dynamic_cast<HighlightKeyword*> (alg);
                if(keyWordAlg != nullptr) keyWordAlg->addKeyWord(pattern);
            }
            if(xml.name() == "start_comments") {
                QString pattern = parsePattern(xml);
                HighlightMultilineComments* commentsAlg = dynamic_cast<HighlightMultilineComments*> (alg);
                if(commentsAlg != nullptr) {
                    commentsAlg->setStartPattern(pattern);
                }
            }
            if(xml.name() == "end_comments") {
                QString pattern = parsePattern(xml);
                HighlightMultilineComments* commentsAlg = dynamic_cast<HighlightMultilineComments*> (alg);
                if(commentsAlg != nullptr) {
                    commentsAlg->setEndPattern(pattern);
                }
            }
        }
        xml.readNext();
    }
    return alg;
}
