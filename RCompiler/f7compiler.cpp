#include "f7compiler.h"
#include "pathstorage.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QProcess>
#include <QDebug>

F7Compiler::F7Compiler():RCompilerInterface()
{
    applPath = QCoreApplication::applicationDirPath();
    gccDir.setPath(applPath+"/arm-gcc/bin");
    buildResDir.setPath(PathStorage::getBuildDir());
    objDir.setPath(PathStorage::getObjDir());
}

QByteArray F7Compiler::compFile(const QString &fName, const F7LinkParams &params)
{
    QByteArray res;

    QFileInfo fInfo(fName);
    QString inpFileName = fInfo.fileName();
    if (QFile::exists(PathStorage::getSrcDir() + "/" + inpFileName)) {
        QDir::setCurrent(gccDir.absolutePath());

        if(!objDir.exists()) {
            objDir.mkdir(".");
        }

        QString outFileName = fName;
        outFileName.replace(".c",".o");

        if (QFile::exists(objDir.absolutePath()+"/" + outFileName)) {
            QFile::remove(objDir.absolutePath()+"/" + outFileName);
        }
        QProcess builder;
        builder.setProcessChannelMode(QProcess::MergedChannels);
        QString program = "\"" + gccDir.absolutePath() + "/arm-none-eabi-gcc.exe\"";
        QString attr = " ";
        QString srcFileName = "\"" + PathStorage::getSrcDir() + "/" + inpFileName + "\" ";
        attr += srcFileName;
        qDebug() << srcFileName;
        QString compileAttr = " " + params.getCompileParams();
        attr += compileAttr;
        qDebug() << compileAttr;
        for(const QString &incDir: params.getIncludeDirs()) {
            QString inclDir = QString(" -I ") + "\"" + PathStorage::getSrcDir() + "/" + incDir + "\"";
            attr += inclDir;
        }
        QString objFile = QString(" -o ") + "\"" + PathStorage::getObjDir() + "/" + outFileName + "\"";
        attr += objFile;

        builder.start(program+attr);
        if (!builder.waitForFinished()) {
            QDir::setCurrent(applPath);
            return builder.errorString().toUtf8();
        }
        QDir::setCurrent(applPath);
        return builder.readAll();
    }
    QString errMessage;
    errMessage = "файл " + fName + " не был найден";
    QByteArray noFileMessage(errMessage.toUtf8());
    QDir::setCurrent(applPath);
    return noFileMessage;
}

void F7Compiler::checkErrors()
{
    QFile logFile;
    outMessage errInfo;
    logFile.setFileName(PathStorage::getLogFileFullName());
    if(logFile.open(QIODevice::ReadOnly)){
        QTextStream in(&logFile);
        QStringList errMessage;
        while(!in.atEnd()) {
            errMessage << in.readLine();
        }
        if(errMessage.count())
        {
            int errCnt=0;
            for(int i=0;i<errMessage.count();i++) {
                QRegExp errWithStrNum("[^\n]*:(\\d+):\\d+:\\s*(error:|warning:|note:)([^\n]*)");
                if (errWithStrNum.indexIn(errMessage[i]) != -1) {
                    errInfo.strNum = errWithStrNum.cap(1).toInt();
                    errInfo.message = errWithStrNum.cap(2) + errWithStrNum.cap(3);
                    errors += errInfo;
                    errCnt++;
                    QString strNum = "строка:" + QString::number(errInfo.strNum);
                }
            }
            if(errCnt==0) {
                for(int i=0;i<errMessage.count();i++) {
                    errInfo.message = errMessage[i];
                    errInfo.strNum = 0;
                    errors += errInfo;
                }
            }
        }
        logFile.close();
    }
}

void F7Compiler::createMapFile()
{
    QProcess builder;
    QString program;
    QString attr;

    QDir::setCurrent(gccDir.absolutePath());

    if (QFile::exists(PathStorage::getMapFileFullName()))
        QFile::remove(PathStorage::getMapFileFullName());

    QFile memFile;
    memFile.setFileName(PathStorage::getMapFileFullName());
    if(memFile.open(QIODevice::WriteOnly)){
        QTextStream map(&memFile);
        program = "\"" + gccDir.absolutePath() + "/arm-none-eabi-readelf.exe\"";
        attr = QString(" -a \"") + buildResDir.absolutePath()+QString("/project.elf\"");

        builder.start(program+attr);
        if(builder.waitForFinished()) {
            map << builder.readAll();
        }
        memFile.close();
    }
    QDir::setCurrent(applPath);
}

void F7Compiler::createBinFile()
{
    QProcess builder;
    QString program;
    QString attr;

    QDir::setCurrent(gccDir.absolutePath());

    if (QFile::exists(PathStorage::getBinFileFullName()))
        QFile::remove(PathStorage::getBinFileFullName());

    program = "\"" + gccDir.absolutePath() + "/arm-none-eabi-objcopy.exe\"";
    attr = QString(" -O binary \"") + buildResDir.absolutePath() + QString("/project.elf\"");
    attr += QString(" \"") + PathStorage::getBinFileFullName() + QString("\"");

    builder.start(program+attr);
    builder.waitForFinished();
    QDir::setCurrent(applPath);
}

void F7Compiler::createMemSizeFile()
{
    QProcess builder;
    QString program;
    QString attr;

    QDir::setCurrent(gccDir.absolutePath());

    program = "\"" + gccDir.absolutePath() + "/arm-none-eabi-size.exe\"";
    attr = QString(" \"") + buildResDir.absolutePath()+QString("/project.elf\"");

    QFile logFile;
    logFile.setFileName(PathStorage::getSizeFileFullName());
    if(logFile.open(QIODevice::WriteOnly)){
        QTextStream out(&logFile);
        builder.start(program+attr);
        if (!builder.waitForFinished())
            out << builder.errorString();
        else
            out << builder.readAll();
        logFile.close();
    }
    QDir::setCurrent(applPath);
}

QVector<outMessage> &F7Compiler::getOutErrors()
{
    return errors;
}

void F7Compiler::compile()
{

    QDir::setCurrent(gccDir.absolutePath());
    if(!buildResDir.exists()) buildResDir.mkdir(".");

    compileResult.clear();

    QFile compileLogFile;
    compileLogFile.setFileName(buildResDir.absolutePath()+"/compile.log");
    if(compileLogFile.open(QIODevice::WriteOnly)){
        QTextStream compileOut(&compileLogFile);
        F7LinkParams params;
        QString fName = PathStorage::getSrcDir()+"/compiler.json";
        params.readParams(fName);

        for(const QString& f:params.getCompileFiles()) {
            QByteArray result = compFile(f,params);
            if(result.count()) {
                compileResult.append(result);
                compileOut << result;
            }
        }
        compileLogFile.close();
    }
    QDir::setCurrent(applPath);
}

void F7Compiler::link()
{
    QFile::remove(PathStorage::getLogFileFullName());
    QFile::remove(PathStorage::getSizeFileFullName());
    F7LinkParams params;
    QString fName = PathStorage::getSrcDir()+"/compiler.json";
    params.readParams(fName);

    QFile logFile;
    logFile.setFileName(PathStorage::getLogFileFullName());
    if(logFile.open(QIODevice::WriteOnly)){
        QTextStream out(&logFile);
        compile();
        if(compileResult.count()) out << compileResult;

        if (QFile::exists(buildResDir.absolutePath() + QString("/project.elf"))) {
            QFile::remove(buildResDir.absolutePath() + QString("/project.elf"));
        }
        QString program = "\"" + gccDir.absolutePath() + "/arm-none-eabi-gcc.exe\"";
        QString attr = " ";

        QString elfFile = QString(" -o ") + "\"" + buildResDir.absolutePath() + QString("/project.elf") + "\"";
        attr += elfFile;

        QFile objListFile;
        objListFile.setFileName(PathStorage::getObjDir()+"/objects.list");
        if(objListFile.open(QIODevice::WriteOnly)){
            QTextStream out(&objListFile);
            for(const QString& ob:params.getObjFiles()) {
                QString obFile = QString(" \"") + PathStorage::getObjDir() + "/" + ob + "\"\n";
                out << obFile;
            }
            objListFile.close();
        }

        QString objFile = QString(" @") + "\"" + PathStorage::getObjDir() + "/objects.list" + "\"";
        attr += objFile;

        QString ldFile = QString(" -T ") + "\"" + PathStorage::getSrcDir() + "/" + params.getLdFile() + "\"";
        attr += ldFile;

        QString linkParams = QString(" ") + params.getLinkParams();
        attr += linkParams;

        QProcess builder;
        builder.setProcessChannelMode(QProcess::MergedChannels);
        builder.start(program+attr);
        if (!builder.waitForFinished())
            out << builder.errorString();
        else
            out <<  builder.readAll();
        logFile.close();

        if (QFile::exists(buildResDir.absolutePath()+"/project.elf")) {
            createMemSizeFile();
            createMapFile();
            createBinFile();
        }else checkErrors();
    }

}
