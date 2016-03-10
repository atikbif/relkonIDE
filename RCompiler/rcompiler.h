#ifndef RCOMPILER_H
#define RCOMPILER_H

#include <QString>
#include <QVector>
#include <QtXml>
#include <QMap>

typedef struct {
    QString inpName;
    QString outName;
    QString patternName;
}inpFile;

typedef struct {
    int strNum;
    QString message;
}outMessage;

class RCompiler
{
    QVector<inpFile> files;
    QVector<inpFile> linkFiles;
    QVector<outMessage> errors;
    QString linkPattern;
    QString linkScript;
    QMap<QString,QString> patterns; // pattern's name, pattern's body

    static const QString dirOutName;
    static const QString dirBuildName;
    static QString inpDirName;
    static QString inpKonFileName;

    void init(void);    // read settings from xml file
    void traverseNode(const QDomNode &node);    // read node from xml file (settings)
    void createMapFile(void);
    void createBinFile(void);
    void createMemSizeFile(void);
    void errorAnalysis(void);
    QByteArray compFile(const QString &fName);
    QString applPath;
    QDir gccDir;
    QDir buildResDir;
    QDir objDir;
public:
    RCompiler();
    QVector<outMessage>& getOutErrors(void) {return errors;}
    void compile(void);
    void link(void);
};

#endif // RCOMPILER_H
