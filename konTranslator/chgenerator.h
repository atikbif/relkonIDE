#ifndef CHGENERATOR_H
#define CHGENERATOR_H

#include<QStringList>
#include "textblock.h"
#include "konprocess.h"
#include <LCD/display.h>

class CHGenerator
{
protected:
    QStringList errorList;
    const Display& lcd;
public:
    CHGenerator(const Display& d);
    virtual QStringList getFileNames(void) = 0;
    virtual int createFiles(TextBlock &varBlock,TextBlock &initBlock,QVector<KonProcess> &prBlock)=0;

    const QStringList& getErrors(void) const;
};

#endif // CHGENERATOR_H
