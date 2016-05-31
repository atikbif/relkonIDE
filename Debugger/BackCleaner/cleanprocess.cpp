#include "cleanprocess.h"
#include <QMutexLocker>
#include <QThread>
#include <QDateTime>
#include "pathstorage.h"
#include <QDir>
#include <QFileInfoList>

CleanProcess::CleanProcess(QObject *parent): QObject(parent), startCmd(true) , finishCmd(false)
{

}

void CleanProcess::startClean()
{
    QMutexLocker locker(&mutex);
    startCmd = true;
}

void CleanProcess::finishProcess()
{
    QMutexLocker locker(&mutex);
    finishCmd = true;
}

void CleanProcess::startProcess()
{
    forever{
        mutex.lock();
        if(finishCmd) {mutex.unlock();break;}
        if(startCmd) {
            mutex.unlock();
            // search files
            fKonList.clear();
            fLcdList.clear();
            QDir dir(PathStorage::getBackDir());
            QFileInfoList files = dir.entryInfoList();
            QStringList allFiles;
            foreach(QFileInfo file, files) {
                if(file.isFile()) {
                    QString fName = file.fileName();
                    allFiles += fName;
                    if(fName.contains(".kon")) {
                        QString fTime = fName;
                        fTime.remove(".kon");
                        qint64 timeValue = QDateTime::fromString(fTime,"dd_MM_yyyy__hh_mm_ss").toMSecsSinceEpoch();
                        if(timeValue>0) fKonList.insert(fName,timeValue);
                    }else if(fName.contains(".lcd")) {
                        QString fTime = fName;
                        fTime.remove(".lcd");
                        qint64 timeValue = QDateTime::fromString(fTime,"dd_MM_yyyy__hh_mm_ss").toMSecsSinceEpoch();
                        if(timeValue>0) fLcdList.insert(fName,timeValue);
                    }
                }
            }
            QStringList lastKonFileNames;
            QList<qint64> timesMsec = fKonList.values();
            if(timesMsec.count()>=10) {
                qSort(timesMsec);
                while(timesMsec.count()>10) timesMsec.removeFirst();
            }
            foreach(qint64 t, timesMsec) {
                lastKonFileNames+=fKonList.keys(t);
            }

            QStringList lastLcdFileNames;
            timesMsec = fLcdList.values();
            if(timesMsec.count()>=10) {
                qSort(timesMsec);
                while(timesMsec.count()>10) timesMsec.removeFirst();
            }
            foreach(qint64 t, timesMsec) {
                lastLcdFileNames+=fLcdList.keys(t);
            }

            foreach(QString fName, allFiles) {
                bool delFlag = true;
                if(lastKonFileNames.contains(fName)) delFlag=false;
                if(lastLcdFileNames.contains(fName)) delFlag=false;
                if(delFlag) {
                    QFile::remove(PathStorage::getBackDir()+"/"+fName);
                }
                QThread::msleep(10);
                mutex.lock();
                if(finishCmd) {startCmd=false;mutex.unlock();break;}
                mutex.unlock();
            }

            mutex.lock();
            startCmd = false;
            mutex.unlock();

        }else mutex.unlock();
        QThread::msleep(100);
    }
}
