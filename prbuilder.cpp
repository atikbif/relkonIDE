#include "prbuilder.h"
#include <QDateTime>
#include "RCompiler/rcompiler.h"
#include "konTranslator/konparser.h"
#include "konTranslator/freertosfactory.h"
#include <QApplication>
#include <QRegExp>

int PrBuilder::convertStrNum(int cStrNum)
{
    QString fileName = QApplication::applicationDirPath();
    fileName += "/src/fc_u.c";
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in (&file);
        int strNum = 0;
        QString str;
        while (!in.atEnd()) {
            str = in.readLine();
            strNum++;
            if(strNum==cStrNum) {
                QRegExp numExp("/\\* (\\d+) \\*/");
                if(numExp.indexIn(str)!=-1) {
                    file.close();
                    return numExp.cap(1).toInt();
                }
            }
        }
        file.close();
    }
    return 0;
}

void PrBuilder::removeBuildFiles(const QString & prPath, const QString &prName)
{
    if(!prPath.isEmpty()) {
        QDir dir(prPath + "/build");
        if(!dir.exists()) {
            dir.mkdir(".");
        }
        QString binFileName = prName;
        binFileName.remove(".kon");
        binFileName = dir.path() + "/" + binFileName + ".bin";
        QFile::remove(binFileName);
        QFile::remove(dir.path() + "/memory.map");
        QFile::remove(dir.path() + "/build.log");
        QFile::remove(dir.path() + "/fc_u.c");
    }
}

PrBuilder::PrBuilder(QObject *parent) :
    QObject(parent)
{
}

void PrBuilder::setFileText(QStringList str)
{
    konFile = str;
}

void PrBuilder::buildRequest(QString prPath, QString prName)
{
    if(newBuild==false) {
        newBuild = true;

        // save file

        QString fileName = QApplication::applicationDirPath();
        fileName += "/src/input.kon";


        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out.setCodec("Windows-1251");
            for(int i=0;i<konFile.count();i++) {
                out << konFile.at(i);
                out << "\r\n";
            }

            file.close();
        }else
        {
            emit printMessage("ошибка записи файла " + fileName);
            emit buildIsFinished();
            newBuild = false;
            return;
        }

        KonParser parser;
        FreeRtosFactory factory;
        parser.setCHFactory(&factory);
        parser.parse();
        QStringList err = parser.getErrors();
        if(err.count()==0) {
            emit printMessage(QDateTime::currentDateTime().time().toString() + " :преобразование в си файл выполнено ");
            emit printMessage(QDateTime::currentDateTime().time().toString() + " :запуск сборки проекта");
            RCompiler compiler;
            compiler.link();
            QVector<outMessage> compileErr = compiler.getOutErrors();
            if(compileErr.count()==0) {
                emit printMessage(QDateTime::currentDateTime().time().toString() + " :сборка успешно закончена ");

                // print project size
                QString fileName = QApplication::applicationDirPath();
                fileName += "/build/size.log";

                if(QFile::exists(QApplication::applicationDirPath()+"/build/project.elf")) {
                    QFile sizeFile(fileName);
                    if (sizeFile.open(QIODevice::ReadOnly)) {
                        QTextStream in (&sizeFile);
                        while (!in.atEnd()) {
                            QString str = in.readLine();
                            QStringList sList = str.split(" ");
                            sList.removeAll("");
                            if(sList.count()>=3)
                            emit printMessage(sList[0] + sList[1] + sList[2]);
                        }
                        sizeFile.close();
                    }

                    if(!prPath.isEmpty()) {
                        removeBuildFiles(prPath,prName);

                        QString binFileName = prName;
                        binFileName.remove(".kon");
                        binFileName = prPath + "/build/" + binFileName + ".bin";

                        bool copyFlag = true;
                        copyFlag = copyFlag && QFile::copy(QApplication::applicationDirPath()+"/build/project.bin",binFileName);
                        copyFlag = copyFlag && QFile::copy(QApplication::applicationDirPath()+"/build/memory.map",prPath + "/build/memory.map");

                        if(copyFlag) emit printMessage("bin файл сохранён");
                        else emit printMessage("Ошибка сохранения BIN файла");
                    }
                }

            }else {
                for(int i=0;i<compileErr.count();i++) {
                    QString errText = compileErr.at(i).message;
                    if(compileErr.at(i).strNum>0) {
                        int konNum = convertStrNum(compileErr.at(i).strNum);
                        if(konNum>0) {
                            errText += " (строка:" +QString::number(konNum)+")";
                        }
                    }
                    emit printMessage(errText);
                }

                if(!prPath.isEmpty()) {
                    removeBuildFiles(prPath,prName);
                    QFile::copy(QApplication::applicationDirPath()+"/build/build.log",prPath + "/build/build.log");
                    QFile::copy(QApplication::applicationDirPath()+"/src/fc_u.c",prPath + "/build/fc_u.c");
                }

            }
        }else {
            for(int i=0;i<err.count();i++) {
                emit printMessage(err.at(i));
            }
        }

        emit buildIsFinished();
        newBuild = false;
    }
}

