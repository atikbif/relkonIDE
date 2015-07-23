#include "varparser.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QHash>
#include <QVector>

void VarParser::getVarsBlock()
{
    QRegExp stopData("\\s*#INIT\\b");
    QStringList resList;
    foreach (QString str, dataBlock) {
       if(str.contains(stopData)) break;
       resList+=str;
    }
    dataBlock = resList;
}

void VarParser::removeComments()
{
    QRegExp singleComment("//[^\n]*");
    QRegExp multiCommentInLine("/\\*[^\n]*\\*/");
    QRegExp multiCommentStart("/\\*[^\n]*");
    QRegExp multiCommentStop("[^\n]*\\*/");
    bool multiComments = false;
    for(int i=0;i<dataBlock.count();i++) {
        if(multiComments==false){
            dataBlock[i].remove(multiCommentInLine);
            dataBlock[i].remove(singleComment);
            if(multiCommentStart.indexIn(dataBlock[i])!=-1){
                dataBlock[i].remove(multiCommentStart);
                multiComments=true;
            }
        }else{
            if(multiCommentStop.indexIn(dataBlock[i])!=-1) {
                dataBlock[i].remove(multiCommentStop);
                multiComments=false;
                if(i) i--;
            }else dataBlock[i]="\n";
        }
    }
}

void VarParser::treatDefines()
{
    // замена define в указании длины массивов
    QHash<QString,QString> defTab;
    QRegExp defineExpression("#define[\\s\\t]*\\b(\\w*)[\\s\\t]*(\\w*)\\b");
    for(int i=0;i<dataBlock.count();i++){
        QString str = dataBlock.at(i);
        if(defineExpression.indexIn(str) != -1) {
            QString inpStr = defineExpression.cap(1);
            QString resStr = defineExpression.cap(2);
            defTab.insert(inpStr,resStr);
            dataBlock.replace(i,QString());
        }
    }
    for(int i=0;i<dataBlock.count();i++) {
        if(dataBlock.at(i).isEmpty()) continue;
        if(dataBlock.at(i).contains('['))
        for(int j=0;j<defTab.count();j++) {
            QRegExp defExpr("\\b"+defTab.keys().at(j)+"\\b");
            dataBlock[i].replace(defExpr,defTab.values().at(j));
        }
    }
}

void VarParser::searchVars()
{
    QMultiHash<QString,QString> vars;
    QStringList standTypes;
    QString multiLineType;
    QStringList multiLineAlignments;
    QStringList alignments;
    bool multiLineDefinition = false;
    standTypes << "char" <<  "short" << "int" << "long" << "float" << "double";
    bool repeatPrevStrTest = false;
    for(int i=0;i<dataBlock.count();i++) {
        if(repeatPrevStrTest) {
            repeatPrevStrTest = false;
            if(i) i--;
        }
        if(multiLineDefinition==false) {
            for(int j=0;j<standTypes.count();j++) {
                int pos = dataBlock.at(i).indexOf(standTypes.at(j));
                if(pos != -1) {
                    alignments = getAlignments(dataBlock.at(i),pos);
                    int semicolonPos = dataBlock.at(i).indexOf(';',pos);
                    if(semicolonPos==-1){
                        multiLineDefinition = true;
                        multiLineType = standTypes[j];
                        multiLineAlignments = alignments;

                        QString remainder = dataBlock.at(i).mid(pos);
                        remainder.remove(multiLineType);
                        vars+=getVarsInStr(remainder,multiLineType,multiLineAlignments);
                    }else {
                        QString remainder = dataBlock.at(i).mid(pos,semicolonPos-pos);
                        remainder.remove(standTypes[j]);
                        vars+=getVarsInStr(remainder,standTypes[j],alignments);
                    }
                }
            }
        }else {
            int semicolonPos = dataBlock.at(i).indexOf(';');
            if(semicolonPos==-1) {
                QString remainder = dataBlock.at(i);
                vars+=getVarsInStr(remainder,multiLineType,multiLineAlignments);
            }else {
                multiLineDefinition = false;
                QString remainder = dataBlock.at(i).mid(0,semicolonPos);
                vars+=getVarsInStr(remainder,multiLineType,multiLineAlignments);
                repeatPrevStrTest = true;
            }
        }

    }
}

void VarParser::searchStructures()
{
    // поиск и удаление структур, перечислений, объединений
    QString allData;
    foreach (QString str, dataBlock) {
       allData+=str;
    }
    // поиск описания структур
    QRegExp structExpr("struct[\\s\\t\\n]*([\\w]*)[\\s\\t\\n]*\\{([^\\{\\}]*)\\}([^;]*);");
    int pos = 0;
    while(pos>=0) {
        pos = structExpr.indexIn(allData,pos);
        if(pos>=0) {
            QString nameOfType = structExpr.cap(1);
            QString body = structExpr.cap(2);
            QString nameOfVar = structExpr.cap(3);
            addStruct(nameOfType,body,nameOfVar);
            pos+=structExpr.matchedLength();
        }
    }
    // поиск переменных реализующих структуры
    QRegExp structVarExpr("struct[\\s\\t\\n]+([\\w]+)[\\s\\t\\n]+([^;\\{\\}]*);");
    pos = 0;
    while(pos>=0) {
        pos = structVarExpr.indexIn(allData,pos);
        if(pos>=0) {
            QString nameOfType = structExpr.cap(1);
            QString nameOfVar = structExpr.cap(2);
            addStructVar(nameOfType,nameOfVar);
            pos+=structVarExpr.matchedLength();
        }
    }

}

bool VarParser::buildXML()
{
    return true;
}

QStringList VarParser::getAlignments(const QString &str, int startTypePos)
{
    QStringList res;
    QVector<int> semicolonPos;
    int pos = 0;
    while(1){
        pos = str.indexOf(';',pos);
        if(pos==-1) break;
        semicolonPos+=pos;pos++;
    }
    pos = 0;
    foreach (int sPos, semicolonPos) {
        if(sPos<startTypePos) pos = sPos;
    }

    QString testPart = str.mid(pos,startTypePos - pos);
    pos=0;
    while(1) {
        QRegExp alignment("\\b(\\w+)\\b");
        pos = alignment.indexIn(testPart,pos);
        if(pos==-1) break;
        res += testPart.mid(pos,alignment.matchedLength());
        pos++;
    }
    return res;
}

QMultiHash<QString, QString> VarParser::getVarsInStr(const QString &str, const QString &varType, const QStringList &varAlignments)
{
    QMultiHash<QString, QString> strVars;
    QString tmpStr = str;
    tmpStr.remove(QRegExp("[\\s\\t]"));
    tmpStr.remove(QRegExp("=[^,;]+"));
    QStringList varNames = tmpStr.split(',');
    foreach(QString varName, varNames) {
        if(varName.isEmpty()) break;
        QString alignStr="";
        if(varAlignments.contains("const")) alignStr += "const ";
        if(varAlignments.contains("unsigned")) alignStr += "unsigned ";
        strVars.insert(alignStr + varType,varName);
    }
    return strVars;
}

void VarParser::addStruct(const QString &name, const QString &body, const QString &vars)
{
    Q_UNUSED(name)
    Q_UNUSED(body)
    Q_UNUSED(vars)
}

void VarParser::addStructVar(const QString &structName, const QString &varName)
{
    Q_UNUSED(structName)
    Q_UNUSED(varName)
}

void VarParser::createFundTypes()
{
    struct sType{QString name;int size;}standTypes[] =
    {
        {"char",1},
        {"unsigned char",1},
        {"short",2},
        {"unsigned short",2},
        {"int",4},
        {"unsigned int",4},
        {"long",4},
        {"unsigned long",4},
        {"float",4},
        {"double",8}
    };

    int cnt = sizeof(standTypes)/sizeof(sType);
    for(int i=0;i<cnt;i++) {
        FundamentalType* fType = new FundamentalType();
        fType->setId(idNum++);
        fType->setName(standTypes[i].name);
        fType->setSize(standTypes[i].size);
        fundTypes+=fType;
    }
}

int VarParser::idNum = 0;

VarParser::VarParser(const QString &fName)
{
    inpFileName = fName;

    createFundTypes();
}

bool VarParser::createXML()
{
    QFile file(inpFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;
    QTextStream in(&file);
    dataBlock.clear();
    while (!in.atEnd()) {
       QString line = in.readLine();
       dataBlock += line;
    }
    file.close();

    removeComments();
    getVarsBlock();
    treatDefines();
    searchStructures();
    searchVars();
    return buildXML();
}

VarParser::~VarParser()
{
    for(int i=0;i<fundTypes.count();i++) {
        delete fundTypes.at(i);
    }
}


int VarParser::FundamentalType::getId() const
{
    return id;
}

void VarParser::FundamentalType::setId(int value)
{
    id = value;
}

QString VarParser::FundamentalType::getName() const
{
    return name;
}

void VarParser::FundamentalType::setName(const QString &value)
{
    name = value;
}

int VarParser::FundamentalType::getSize() const
{
    return size;
}

void VarParser::FundamentalType::setSize(int value)
{
    size = value;
}



int VarParser::Variable::getId() const
{
    return id;
}

void VarParser::Variable::setId(int value)
{
    id = value;
}

QString VarParser::Variable::getName() const
{
    return name;
}

void VarParser::Variable::setName(const QString &value)
{
    name = value;
}

int VarParser::Variable::getType() const
{
    return type;
}

void VarParser::Variable::setType(int value)
{
    type = value;
}

int VarParser::Variable::getAddress() const
{
    return address;
}

void VarParser::Variable::setAddress(int value)
{
    address = value;
}

QString VarParser::Variable::getMemType() const
{
    return memType;
}

void VarParser::Variable::setMemType(const QString &value)
{
    memType = value;
}

int VarParser::Structure::getId() const
{
    return id;
}

void VarParser::Structure::setId(int value)
{
    id = value;
}

QVector<int> VarParser::Structure::getMembers() const
{
    return members;
}

void VarParser::Structure::setMembers(const QVector<int> &value)
{
    members = value;
}

int VarParser::Field::getId() const
{
    return id;
}

void VarParser::Field::setId(int value)
{
    id = value;
}

QString VarParser::Field::getName() const
{
    return name;
}

void VarParser::Field::setName(const QString &value)
{
    name = value;
}

int VarParser::Field::getType() const
{
    return type;
}

void VarParser::Field::setType(int value)
{
    type = value;
}

int VarParser::Field::getOffset() const
{
    return offset;
}

void VarParser::Field::setOffset(int value)
{
    offset = value;
}

int VarParser::Array::getId() const
{
    return id;
}

void VarParser::Array::setId(int value)
{
    id = value;
}

int VarParser::Array::getType() const
{
    return type;
}

void VarParser::Array::setType(int value)
{
    type = value;
}

int VarParser::Array::getSize() const
{
    return size;
}

void VarParser::Array::setSize(int value)
{
    size = value;
}
