#ifndef F7GENERATOR_H
#define F7GENERATOR_H

#include "chgenerator.h"
#include "moduleio.h"
#include <QTextStream>
#include "LCD/display.h"

class F7Generator : public CHGenerator
{
    TextBlock varBlock;
    TextBlock initBlock;
    QVector<KonProcess> prBlock;
    QVector<ModuleIO> modIo;
    int curSitNum=1;
    int curPrNum=1;
    int curSitSpeed=1;
public:
    F7Generator(const Display &d);

    // CHGenerator interface
public:
    QStringList getFileNames() override;
    int createFiles(TextBlock &varBlock, TextBlock &initBlock, QVector<KonProcess> &prBlock) override;
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

#endif // F7GENERATOR_H
