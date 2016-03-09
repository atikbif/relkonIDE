#ifndef PATHSTORAGE_H
#define PATHSTORAGE_H

#include <QString>
#include <QMutex>

class PathStorage
{
    static QString buildDir;
    static QString objDir;
    static QString coreDir;
    static QString srcDir;
    static QString konFileName;
    static QString buildName;
    static QString prDir;
    static QMutex mutex;
    PathStorage();


    static void setObjDir(const QString &value);    // входные obj файлы
    static void setSrcDir(const QString &value);    // входные h файлы
    static void setBuildDir(const QString &value);  // выходные bin,elf,log,map

public:

    static void setCoreDir(const QString &value);       // папка с версиями сборок
    static void setPrDir(const QString &value);         // текущий проект
    static void setKonFileName(const QString &value);   // имя kon файла
    static void setBuildName(const QString & value);    // текущая сборка

    static QString getBuildName();


    static QString getCoreDir();
    static QString getPrDir();

    static QString getObjDir();
    static QString getSrcDir();

    static QString getBuildDir();
    static QString getBackDir();


    static QString getKonFileName();
    static QString getKonFileFullName();
    static QString getBinFileFullName();
    static QString getMapFileFullName();
    static QString getDebugFileFullName();

};

#endif // PATHSTORAGE_H
