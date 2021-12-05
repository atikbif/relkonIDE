#include "f7linkparams.h"
#include "pathstorage.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

const std::vector<QString> &F7LinkParams::getIncludeDirs() const
{
    return includeDirs;
}

const std::vector<QString> &F7LinkParams::getCompileFiles() const
{
    return compileFiles;
}

const QString &F7LinkParams::getCompileParams() const
{
    return compileParams;
}

const QString &F7LinkParams::getLinkParams() const
{
    return linkParams;
}

const QString &F7LinkParams::getLdFile() const
{
    return ldFile;
}

const std::vector<QString> &F7LinkParams::getObjFiles() const
{
    return objFiles;
}

bool F7LinkParams::readParams(const QString &fName)
{
    QFile confFile(fName);
    if(confFile.open(QIODevice::ReadOnly)) {
        QByteArray saveData = confFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
        QJsonObject loadOb = loadDoc.object();
        compileFiles.clear();
        if(loadOb.contains("compile files") && loadOb["compile files"].isArray()) {
            QJsonArray compFiles = loadOb["compile files"].toArray();
            int cnt = compFiles.size();
            for(int i=0;i<cnt;i++) {
                QString compFile = compFiles[i].toString();
                compileFiles.push_back(compFile);
            }
        }else return false;
        includeDirs.clear();
        if(loadOb.contains("inclide dirs") && loadOb["inclide dirs"].isArray()) {
            QJsonArray dirs = loadOb["inclide dirs"].toArray();
            int cnt = dirs.size();
            for(int i=0;i<cnt;i++) {
                QString dir = dirs[i].toString();
                includeDirs.push_back(dir);
            }
        }else return false;
        objFiles.clear();
        if(loadOb.contains("link files") && loadOb["link files"].isArray()) {
            QJsonArray objs = loadOb["link files"].toArray();
            int cnt = objs.size();
            for(int i=0;i<cnt;i++) {
                QString obj = objs[i].toString();
                objFiles.push_back(obj);
            }
        }else return false;
        compileParams.clear();
        if(loadOb.contains("compile attr") && loadOb["compile attr"].isString()) {
            compileParams = loadOb["compile attr"].toString();
        }else return false;
        linkParams.clear();
        if(loadOb.contains("link attr") && loadOb["link attr"].isString()) {
            linkParams = loadOb["link attr"].toString();
        }else return false;
        ldFile.clear();
        if(loadOb.contains("ld file") && loadOb["ld file"].isString()) {
            ldFile = loadOb["ld file"].toString();
        }else return false;
    }else return false;
    return true;
}
