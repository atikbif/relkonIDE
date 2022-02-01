#ifndef RCOMPILER_H
#define RCOMPILER_H

#include "rcompilerinterface.h"
#include <QtXml>
#include <QMap>

typedef struct {
    QString inpName;
    QString outName;
    QString patternName;
}inpFile;

class RCompiler: public RCompilerInterface
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
    QVector<outMessage>& getOutErrors(void) override {return errors;}
    void compile(void) override;
    bool link(void) override;
};

#endif // RCOMPILER_H
