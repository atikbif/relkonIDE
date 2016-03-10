#include "prbuilder.h"
#include <QDateTime>
#include "RCompiler/rcompiler.h"
#include "konTranslator/konparser.h"
#include "konTranslator/freertosfactory.h"
#include <QApplication>
#include <QRegExp>
#include "VarDef/varparser.h"
#include "pathstorage.h"


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
    Q_UNUSED(prName)
    Q_UNUSED(prPath)
    QString binFileName = PathStorage::getBinFileFullName();
    QString mapFileName = PathStorage::getMapFileFullName();

    QFile::remove(binFileName);
    QFile::remove(mapFileName);
}

PrBuilder::PrBuilder(const Display &d, QObject *parent) :
    QObject(parent),lcd(d)
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

        QString fileName = PathStorage::getSrcDir() + "/input.kon";

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

        KonParser parser(lcd);
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

                QString fileName = PathStorage::getSizeFileFullName();

                if(QFile::exists(PathStorage::getBuildDir() + "/project.elf")) {
                    QFile sizeFile(fileName);
                    if (sizeFile.open(QIODevice::ReadOnly)) {
                        emit printMessage("-------расход памяти-------");
                        QTextStream in (&sizeFile);
                        while (!in.atEnd()) {
                            QString str = in.readLine();
                            QStringList sList = str.split(" ");
                            sList.removeAll("");
                            if(sList.count()>=3)
                            emit printMessage(sList[0] + sList[1] + sList[2]);
                        }
                        sizeFile.close();
                        emit printMessage("---------------------------");
                    }

                    VarParser parser(PathStorage::getKonFileFullName());
                    emit printMessage(QDateTime::currentDateTime().time().toString() + " :анализ переменных проекта");
                    if(parser.createXML()) {
                        emit printMessage(QDateTime::currentDateTime().time().toString() + " :создание карты памяти завершено");
                        emit buildIsOk();
                    }else emit printMessage(QDateTime::currentDateTime().time().toString() + " :ошибка разбора переменных");
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

