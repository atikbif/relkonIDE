#ifndef HIGHLIGHTALGORITHM_H
#define HIGHLIGHTALGORITHM_H

/* Abstract class for strategy pattern */

#include<QMap>
#include <QTextCharFormat>
#include <QVector>

class QString;

class HighlightAlgorithm
{
public:
    struct HighlightPositionInText
    {
        int startPosition;
        int length;
    };
protected:
    QString algName;
    QString inpText;
    QTextCharFormat format;
    QVector<HighlightPositionInText> position;
    QMap<QString,int> additionConf;
public:
    explicit HighlightAlgorithm(const QString &name = "");
    int getAdditionPar(const QString &parName);
    int setAdditionPar(const QString &parName, int parValue);
    const QString getAlgName(void) const;
    void setAlgName(const QString &name);
    void setInputText(const QString &textValue);
    void setFormat(const QTextCharFormat &algFormat);
    QTextCharFormat getFormat() const;

    virtual QVector<HighlightPositionInText> getPosition(void) = 0;
};

#endif // HIGHLIGHTALGORITHM_H
