#ifndef CHGENERATOR_H
#define CHGENERATOR_H

#include<QStringList>
#include "textblock.h"
#include "konprocess.h"
#include <LCD/display.h>
#include "fcucsettings.h"

class CHGenerator
{
protected:
    QStringList errorList;
    const Display& lcd;
    FCUCSettings fc_conf;
public:
    explicit CHGenerator(const Display& d);
    virtual QStringList getFileNames(void) = 0;
    virtual int createFiles(TextBlock &varBlock,TextBlock &initBlock,QVector<KonProcess> &prBlock)=0;
    const QStringList& getErrors(void) const;
    void setFCConf(FCUCSettings conf) {fc_conf = conf;}
};

#endif // CHGENERATOR_H
