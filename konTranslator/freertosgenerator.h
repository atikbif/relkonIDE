#ifndef FREERTOSGENERATOR_H
#define FREERTOSGENERATOR_H

#include "chgenerator.h"
#include "moduleio.h"
#include <QTextStream>

class FreeRtosGenerator: public CHGenerator
{
    TextBlock varBlock;
    TextBlock initBlock;
    QVector<KonProcess> prBlock;
    QVector<ModuleIO> modIo;
    int curSitNum=1;
    int curPrNum=1;
    int curSitSpeed=1;
public:
    FreeRtosGenerator();
    QStringList getFileNames();
    int createFiles(TextBlock &varBlock,TextBlock &initBlock,QVector<KonProcess> &prBlock);
private:
    void scanMatchbox(void);
    void translateKonToC(void);
    void createFcuC(void);
    void createIoDefinesH(void);
    void translateIO(QString &str, int konNum);
    void translateSitJump(QString &str, int konNum);
    void translateStartStopProc(QString &str, int konNum);
    void translateTextBlock(QStringList &strList, QVector<int> &konStrNum);
    void printProcess(QTextStream &out, int procId,int period);
};

#endif // FREERTOSGENERATOR_H
