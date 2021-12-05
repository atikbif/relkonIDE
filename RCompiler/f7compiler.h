#ifndef F7COMPILER_H
#define F7COMPILER_H

#include "rcompilerinterface.h"
#include <QDir>
#include "f7linkparams.h"

class F7Compiler : public RCompilerInterface
{
    QVector<outMessage> errors;
    QDir gccDir;
    QDir buildResDir;
    QDir objDir;
    QString applPath;
    QByteArray compileResult;
public:
    F7Compiler();
    QByteArray compFile(const QString &fName, const F7LinkParams &params);
    void checkErrors();
    void createMapFile(void);
    void createBinFile(void);
    void createMemSizeFile(void);
    // RCompilerInterface interface
public:
    QVector<outMessage> &getOutErrors();
    void compile();
    void link();
};

#endif // F7COMPILER_H
