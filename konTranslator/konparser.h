#ifndef KONPARSER_H
#define KONPARSER_H

#include <QStringList>
#include "textblock.h"
#include "konprocess.h"
#include "abstractchfilesfactory.h"
#include "LCD/display.h"
#include "fcucsettings.h"

class KonParser
{
    const QString sourceKonFileName="input.kon";
    QStringList konSource;
    TextBlock varBlock;
    TextBlock initBlock;
    QVector<KonProcess> prBlock;
    AbstractCHFilesFactory* factory;
    QStringList parsingErrors;

    void removeComments(void);
    void addStringNum(void);
    int readSourceFile(void);
    int createVarBlock(void);
    int createInitBlock(void);
    int createProcessBlock(void);
    const Display& lcd;
    QString plcType;
    FCUCSettings fc_conf;

public:
    explicit KonParser(const Display& d);
    void setCHFactory(AbstractCHFilesFactory* factory);
    void parse(void);
    const QStringList &getErrors(void) const;
    void setPLCType(const QString &plc);
    void setFCConf(FCUCSettings conf) {fc_conf = conf;}
private:
    double getCoeff(void);
};

#endif // KONPARSER_H
