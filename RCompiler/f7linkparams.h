#ifndef F7LINKPARAMS_H
#define F7LINKPARAMS_H

#include <QString>
#include <vector>

class F7LinkParams
{
    std::vector<QString> includeDirs;
    std::vector<QString> compileFiles;
    QString compileParams;
    QString linkParams;
    QString ldFile;
    std::vector<QString> objFiles;
public:
    F7LinkParams()=default;
    bool readParams(const QString &fName);

    const std::vector<QString> &getIncludeDirs() const;
    const std::vector<QString> &getCompileFiles() const;
    const QString &getCompileParams() const;
    const QString &getLinkParams() const;
    const QString &getLdFile() const;
    const std::vector<QString> &getObjFiles() const;
};

#endif // F7LINKPARAMS_H
