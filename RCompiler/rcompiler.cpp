#include "rcompiler.h"
#include <QFile>
#include <QProcess>
#include <QDir>
#include <QRegExp>
#include "pathstorage.h"

//const QString RCompiler::dirOutName = "/obj";
//const QString RCompiler::dirBuildName = "/build";

void RCompiler::init()
{
    applPath = QCoreApplication::applicationDirPath();
    gccDir.setPath(applPath+"/arm-gcc/bin");
    buildResDir.setPath(PathStorage::getBuildDir());
    objDir.setPath(PathStorage::getObjDir());

    const QString fName = PathStorage::getSrcDir()+"/compiler.xml";
    QDomDocument domDoc;
    QFile file(fName);
    if(file.open(QIODevice::ReadOnly)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement=domDoc.documentElement();
            files.clear();
            linkFiles.clear();
            errors.clear();
            linkPattern="";
            traverseNode(domElement);
        }
        file.close();
    }else {
        outMessage fileError;
        fileError.strNum = -1;
        fileError.message = "Не удалось прочитать файл настроек " + fName;
        errors += fileError;
    }
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
}

void RCompiler::traverseNode(const QDomNode &node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                if(domElement.tagName() == "source") {
                    inpFile fileDefinition;
                    fileDefinition.inpName = domElement.text();
                    fileDefinition.outName = domElement.attribute("out");
                    fileDefinition.patternName = domElement.attribute("pattern");
                    files += fileDefinition;
                }else if(domElement.tagName() == "linkSource") {
                    inpFile fileDefinition;
                    fileDefinition.inpName = domElement.text();
                    fileDefinition.outName = domElement.attribute("out");
                    fileDefinition.patternName = domElement.attribute("pattern");
                    linkFiles += fileDefinition;
                }else if(domElement.tagName() == "link") {
                    linkPattern = domElement.text();
                    linkScript = domElement.attribute("script");
                }else if(domElement.tagName() == "pattern") {
                    QString patName = domElement.attribute("name");
                    if(!patName.isEmpty()) {
                        patterns.insert(patName,domElement.text());
                    }
                }
            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
}

void RCompiler::createMapFile()
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

void RCompiler::createBinFile()
{
    QProcess builder;
    QString program;
    QString attr;

    QDir::setCurrent(gccDir.absolutePath());

    if (QFile::exists(buildResDir.absolutePath()+"/project.bin"))
        QFile::remove(buildResDir.absolutePath()+"/project.bin");

    program = "\"" + gccDir.absolutePath() + "/arm-none-eabi-objcopy.exe\"";
    attr = QString(" -O binary \"") + buildResDir.absolutePath() + QString("/project.elf\"");
    attr += QString(" \"") + buildResDir.absolutePath() + QString("/project.bin\"");

    builder.start(program+attr);
    builder.waitForFinished();
    QDir::setCurrent(applPath);
}

void RCompiler::createMemSizeFile()
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

void RCompiler::errorAnalysis()
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

QByteArray RCompiler::compFile(const QString &fName)
{
    QDir::setCurrent(gccDir.absolutePath());

    QString outName;
    QString patternName;
    bool hasFileBeenFound = false;
    for(int i=0;i<files.count();i++) {
        if(files[i].inpName == fName) {
            hasFileBeenFound = true;
            outName = files[i].outName;
            patternName = files[i].patternName;
            break;
        }
    }
    if(!hasFileBeenFound) for(int i=0;i<linkFiles.count();i++) {
        if(linkFiles[i].inpName == fName) {
            hasFileBeenFound = true;
            outName = linkFiles[i].outName;
            patternName = linkFiles[i].patternName;
            break;
        }
    }
    if(hasFileBeenFound) {

        if(!objDir.exists()) {
            objDir.mkdir(".");
        }
        if (QFile::exists(objDir.absolutePath()+"/" + outName)) {
            QFile::remove(objDir.absolutePath()+"/" + outName);
        }
        QProcess builder;
        builder.setProcessChannelMode(QProcess::MergedChannels);
        QString program = "\"" + gccDir.absolutePath() + "/arm-none-eabi-gcc.exe\"";

        QString attr = " " + patterns[patternName];
        attr += " -I \"" + PathStorage::getSrcDir() + "\"";
        attr += " -o \"" + PathStorage::getObjDir() + "/" + outName + "\"";
        attr += " \"" + PathStorage::getSrcDir() + "/" + fName + "\"";

        builder.start(program+attr);
        if (!builder.waitForFinished()) {
            QDir::setCurrent(applPath);
            return builder.errorString().toUtf8();
        }
        QDir::setCurrent(applPath);
        return builder.readAll();
    }
    QString errMessage;
    errMessage = "file " + fName + " was not found";
    QByteArray noFileMessage(errMessage.toUtf8());
    QDir::setCurrent(applPath);
    return noFileMessage;
}

RCompiler::RCompiler()
{
    init();
}

void RCompiler::compile()
{
    QDir::setCurrent(gccDir.absolutePath());
    if(!buildResDir.exists()) buildResDir.mkdir(".");

    QFile logFile;
    logFile.setFileName(buildResDir.absolutePath()+"/compile.log");
    if(logFile.open(QIODevice::WriteOnly)){



        QTextStream out(&logFile);

        for(int i=0;i<files.count();i++) {
            QByteArray result = compFile(files[i].inpName);
            if(result.count()) out << result;
        }


        logFile.close();
    }
    QDir::setCurrent(applPath);
}

void RCompiler::link()
{
    QFile::remove(PathStorage::getLogFileFullName());
    QFile::remove(PathStorage::getSizeFileFullName());

    QDir::setCurrent(gccDir.absolutePath());

    if(!objDir.exists()) objDir.mkdir(".");
    if(!buildResDir.exists()) buildResDir.mkdir(".");

    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.setWorkingDirectory(gccDir.absolutePath());
    QString program = "\"" + gccDir.absolutePath() + "/arm-none-eabi-gcc.exe\"";

    QFile logFile;
    logFile.setFileName(PathStorage::getLogFileFullName());
    if(logFile.open(QIODevice::WriteOnly)){


        QTextStream out(&logFile);

        for(int i=0;i<linkFiles.count();i++) {
            QByteArray result = compFile(linkFiles[i].inpName);
            if(result.count()) out << result;
        }

        // build process

        // remove elf file
        if (QFile::exists(buildResDir.absolutePath() + QString("/project.elf"))) {
            QFile::remove(buildResDir.absolutePath() + QString("/project.elf"));
        }

        // form attributes
        QString attr;
        for(int i=0;i<files.count();i++) {
            attr+=" \"" + PathStorage::getObjDir() + "/" + files[i].outName + "\"";
        }
        for(int i=0;i<linkFiles.count();i++) {
            attr+=" \"" + PathStorage::getObjDir() + "/" + linkFiles[i].outName + "\"";
        }
        attr+=" ";

        attr += linkPattern;
        attr += QString(" -T ") + "\"" + PathStorage::getSrcDir() + "/" + linkScript + "\"";
        attr += QString(" -o ") + "\"" + buildResDir.absolutePath() + QString("/project.elf") + "\"";

        // start build
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
        }else {
            errorAnalysis();
        }

    }
    QDir::setCurrent(applPath);
}
