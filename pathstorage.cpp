#include "pathstorage.h"
#include <QMutexLocker>
#include <QRegExp>

QString PathStorage::buildDir = "build";
QString PathStorage::objDir = "obj";
QString PathStorage::coreDir = "core";
QString PathStorage::srcDir = "src";
QString PathStorage::konFileName = "input.kon";
QString PathStorage::buildName = "master";
QString PathStorage::prDir = "";
QMutex PathStorage::mutex;

PathStorage::PathStorage()
{

}

void PathStorage::setObjDir(const QString &value)
{
    objDir = value;
}

void PathStorage::setSrcDir(const QString &value)
{
    srcDir = value;
}

void PathStorage::setBuildDir(const QString &value)
{
    buildDir = value;
}

void PathStorage::setCoreDir(const QString &value)
{
    QMutexLocker locker(&mutex);
    coreDir = value;
}

void PathStorage::setPrDir(const QString &value)
{
    QMutexLocker locker(&mutex);
    prDir = value;
    setBuildDir(prDir + "/build");
}

void PathStorage::setKonFileName(const QString &value)
{
    QMutexLocker locker(&mutex);
    konFileName = value;
}

void PathStorage::setBuildName(const QString &value)
{
    QMutexLocker locker(&mutex);
    buildName = value;
    setObjDir(coreDir + "/" + buildName + "/obj");
    setSrcDir(coreDir + "/" + buildName + "/src");
}

QString PathStorage::getBuildName()
{
    QMutexLocker locker(&mutex);
    return buildName;
}

QString PathStorage::getBuildDir()
{
    QMutexLocker locker(&mutex);
    return buildDir;
}

QString PathStorage::getBackDir()
{
    QMutexLocker locker(&mutex);
    return prDir + "/" + "back";
}

QString PathStorage::getCoreDir()
{
    QMutexLocker locker(&mutex);
    return coreDir;
}

QString PathStorage::getPrDir()
{
    QMutexLocker locker(&mutex);
    return prDir;
}

QString PathStorage::getObjDir()
{
    QMutexLocker locker(&mutex);
    return objDir;
}

QString PathStorage::getSrcDir()
{
    QMutexLocker locker(&mutex);
    return srcDir;
}

QString PathStorage::getKonFileName()
{
    QMutexLocker locker(&mutex);
    return konFileName;
}

QString PathStorage::getKonFileFullName()
{
    QMutexLocker locker(&mutex);
    return prDir + "/" + konFileName;
}

QString PathStorage::getBinFileFullName()
{
    QMutexLocker locker(&mutex);
    QString binFileName = buildDir + "/" + konFileName;
    binFileName.remove(QRegExp("\\.kon"));
    binFileName+=".bin";
    return binFileName;
}

QString PathStorage::getMapFileFullName()
{
    QMutexLocker locker(&mutex);
    QString mapFileName = buildDir + "/" + konFileName;
    mapFileName.remove(QRegExp("\\.kon"));
    mapFileName+=".map";
    return mapFileName;
}

QString PathStorage::getDebugFileFullName()
{
    QMutexLocker locker(&mutex);
    QString debugFileName = buildDir + "/" + konFileName;
    debugFileName.remove(QRegExp("\\.kon"));
    debugFileName+="_debug.xml";
    return debugFileName;
}

QString PathStorage::getLogFileFullName()
{
    QMutexLocker locker(&mutex);
    QString logFileName = buildDir + "/build.log";
    return logFileName;
}

QString PathStorage::getSizeFileFullName()
{
    QMutexLocker locker(&mutex);
    QString sizeFileName = buildDir + "/size.log";
    return sizeFileName;
}

QString PathStorage::getCoreVersionFileFullName()
{
    QMutexLocker locker(&mutex);
    QString versFileName = coreDir + "/info.txt";
    return versFileName;
}

QString PathStorage::getPLCListFileFullName()
{
    QMutexLocker locker(&mutex);
    QString plcFileName = coreDir + "/controllers.xml";
    return plcFileName;
}
