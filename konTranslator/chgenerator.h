#ifndef CHGENERATOR_H
#define CHGENERATOR_H

#include<QStringList>
#include "textblock.h"
#include "konprocess.h"

class CHGenerator
{
protected:
    QStringList errorList;
public:
    CHGenerator();
    virtual QStringList getFileNames(void) = 0;
    virtual int createFiles(TextBlock &varBlock,TextBlock &initBlock,QVector<KonProcess> &prBlock)=0;
    const QStringList& getErrors(void) const;
};

#endif // CHGENERATOR_H
