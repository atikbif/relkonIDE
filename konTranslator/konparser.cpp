#include "konparser.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>

#include <QDateTime>
#include <QApplication>
#include "pathstorage.h"

KonParser::KonParser(const Display &d):lcd(d)
{
    factory = nullptr;
}

void KonParser::setCHFactory(AbstractCHFilesFactory *factory)
{
    this->factory = factory;
}

void KonParser::removeComments()
{
    QRegExp singleComment("//[^\n]*");
    QRegExp multiCommentInLine("/\\*[^\n]*\\*/");
    QRegExp multiCommentStart("/\\*[^\n]*");
    QRegExp multiCommentStop("[^\n]*\\*/");
    bool multiComments = false;
    for(int i=0;i<konSource.count();i++) {
        if(multiComments==false){
            konSource[i].remove(multiCommentInLine);
            konSource[i].remove(singleComment);
            if(multiCommentStart.indexIn(konSource[i])!=-1){
                konSource[i].remove(multiCommentStart);
                multiComments=true;
            }
        }else{
            if(multiCommentStop.indexIn(konSource[i])!=-1) {
                konSource[i].remove(multiCommentStop);
                multiComments=false;
                if(i) i--;
            }else konSource[i]="\n";
        }
    }
}

void KonParser::addStringNum()
{
    for(int i=0;i<konSource.count();i++) {
        konSource[i] += " /* " + QString::number(i+1) + " */";
    }
}

int KonParser::readSourceFile()
{
    QString fileName = PathStorage::getSrcDir() + "/" + sourceKonFileName;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return -1;
    QTextStream in(&file);
    konSource.clear();
    while (!in.atEnd()) {
       QString line = in.readLine();
       konSource += line;
    }
    file.close();
    return 1;
}

int KonParser::createVarBlock()
{
    if(konSource.count()==0) return -1;
    for(int i=0;i<konSource.count();i++) {
        if(konSource[i].contains(QRegExp("\\s*#INIT\\b"))) break;
        if(!konSource[i].contains("#DATA")) varBlock.addString(konSource[i],i+1);
        else varBlock.addString("",i+1);
    }
    return 1;
}

int KonParser::createInitBlock()
{
    bool initEnable = false;
    if(konSource.count()==0) return -1;
    for(int i=0;i<konSource.count();i++) {
        if(initEnable==false) {
            if(konSource[i].contains(QRegExp("\\s*#INIT\\b"))) initEnable=true;
        }else {
            if(konSource[i].contains(QRegExp("\\s*#PROCESS\\s+\\d+\\b"))) break;
            else initBlock.addString(konSource[i],i+1);
        }
    }
    return 1;
}

int KonParser::createProcessBlock()
{
    if(konSource.count()==0) return -1;
    for(int i=0;i<konSource.count();i++) {
        if(konSource[i].contains(QRegExp("\\s*#PROCESS\\s+\\d+\\b"))) {
            // add process
            QRegExp prNum("\\d+");
            if(prNum.indexIn(konSource[i])>=0) {
                int number = prNum.cap().toInt();
                KonProcess pr(number);
                int sitPeriod = 100;   // период ситуации по умолчанию в мс
                int sitNum = 0;         // номер ситуации

                // scan situations inside process
                bool convRes=false;
                QString err;
                while(1) {
                    i++;
                    if(i>=konSource.count()) break;
                    if(konSource[i].contains(QRegExp("\\s*#PROCESS\\s+\\d+\\b"))){
                        i--;
                        break;
                    }
                    sitNum=0;
                    err="";
                    QRegExp sitFullExp("\\s*#SIT(\\d+)\\((.+)\\)");
                    QRegExp sitShortExp("\\s*#SIT(\\d+)\\b");
                    if(sitFullExp.indexIn(konSource[i])!=-1) {
                        sitNum = sitFullExp.cap(1).toInt(&convRes);
                        if(convRes==false) {parsingErrors+="Некорректный номер ситуации. Строка " + QString::number(i+1);}
                        sitPeriod = sitFullExp.cap(2).toDouble(&convRes)*1000 + 0.5;
                        if(convRes==false) {sitPeriod=0;parsingErrors+="Некорректный период ситуации. Строка " + QString::number(i+1);}
                    }else if(sitShortExp.indexIn(konSource[i])!=-1) {
                        sitNum = sitShortExp.cap(1).toInt(&convRes);
                        if(convRes==false) {parsingErrors+="Некорректный номер ситуации. Строка " + QString::number(i+1);}
                    }else if(konSource[i].contains("SIT")) {
                        parsingErrors+="Некорректное название ситуации. Строка " + QString::number(i+1);
                    }
                    if(sitNum) {
                        // read a content of situation
                        Situation s(sitNum);
                        s.setPeriod(sitPeriod);
                        s.setPocessNum(number);

                        while(1) {
                            i++;
                            if(i>=konSource.count()) {
                                pr.addSituation(s);
                                break;
                            }
                            if((konSource[i].contains("#SIT"))||(konSource[i].contains("#PROCESS"))) {
                                pr.addSituation(s);
                                i--;
                                break;
                            }
                            s.addString(konSource[i],i+1);
                        }
                    }
                }
                prBlock+=pr;
            }
        }
    }
    return -1;
}

void KonParser::parse()
{
    int resCode; // operation's result
    resCode = readSourceFile();
    if(resCode==-1) return;
    parsingErrors.clear();
    removeComments();
    addStringNum();
    createVarBlock();
    createInitBlock();
    createProcessBlock();
    if(factory != nullptr) {
        CHGenerator* generator = factory->createCHGenerator(lcd);
        generator->createFiles(varBlock,initBlock,prBlock);

        parsingErrors += generator->getErrors();
    }

}

const QStringList &KonParser::getErrors() const
{
    return parsingErrors;
}
