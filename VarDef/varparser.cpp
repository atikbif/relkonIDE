#include "varparser.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QHash>
#include <QVector>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include "RCompiler/rcompiler.h"
#include "VarDef/varitem.h"

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
    // замена define в указании длины массивов и инициализаци переменных
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
    QString allData;
    foreach (QString str, dataBlock) {
       allData+=str;
    }
    // удаление переходов между строками
    allData.remove(QRegExp("[\\r\\n]+"));
    // замена промежутков пробелом
    allData.replace(QRegExp("[\\s\\t]+")," ");
    // удаление инициализации переменных
    allData.remove(QRegExp("=[\\s\\t]*-*[\\d\\.]+"));
    // удаление фигурных скобок и их содержимого
    allData.remove(QRegExp("\\{[^\\}]*\\}"));
    // удаление фигурных скобок (для влож. массивов) и символа равно
    allData.remove(QRegExp("[\\{\\}=]"));
    // удаление двойных кавычек и их содержимого
    allData.remove(QRegExp("\"[^\"]*\""));

    // сканирование всех фундаментальных типов
    for(int i=0;i<fundTypes.count();i++) {
        QRegExp varsExp(fundTypes.at(i)->getName()+"[\\s\\t]+([^;]+);");
        int pos = 0;
        while(pos>=0) {
            pos = varsExp.indexIn(allData,pos);
            if(pos!=-1) {
                QString body = varsExp.cap(1);
                body.remove(QRegExp("[\\s\\t]+"));
                if(!body.isEmpty()) {
                    QStringList varNames = body.split(',');
                    for(int j=0;j<varNames.count();j++) {
                        // *******************************************
                        QString curVarName = varNames.at(j);
                        if(curVarName.isEmpty()) continue;
                        Variable* var = new Variable();
                        // проверка на массив
                        Array* ptr = checkArray(curVarName,fundTypes.at(i)->getId());
                        if(ptr!=nullptr) {var->setType(ptr->getId());}
                        else{var->setType(fundTypes.at(i)->getId());}
                        var->setName(curVarName);
                        var->setId(idNum++);
                        variables += var;
                        // *******************************************
                    }
                }
                allData.remove(pos,varsExp.matchedLength());
            }
        }
    }
}

void VarParser::searchStructures()
{
    // поиск и удаление структур, перечислений, объединений
    // для удобства все данные в виде сплошной строки
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
            allData.remove(pos,structExpr.matchedLength());
        }
    }
    // поиск переменных реализующих структуры
    QRegExp structVarExpr("struct[\\s\\t\\n]+([\\w]+)[\\s\\t\\n]+([^;\\{\\}]*);");
    pos = 0;
    while(pos>=0) {
        pos = structVarExpr.indexIn(allData,pos);
        if(pos>=0) {
            QString nameOfType = structVarExpr.cap(1);
            QString nameOfVar = structVarExpr.cap(2);
            addStructVar(nameOfType,nameOfVar);
            allData.remove(pos,structVarExpr.matchedLength());
        }
    }
    dataBlock.clear();
    dataBlock += allData;
}

bool VarParser::buildXML()
{
    QXmlStreamWriter xmlWriter;

    if(readMapFile()) {
        xmlWriter.setAutoFormatting(true);
        if(!RCompiler::getBuildDirName().contains(QRegExp("[\\w\\d]+"))) return false;
        QFile file(RCompiler::getBuildDirName()+"/variables.xml");

        if (!file.open(QIODevice::WriteOnly)) {return false;}
        else
        {
            xmlWriter.setDevice(&file);

            /* Writes a document start with the XML version number. */
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("mapForDebug");

            foreach (FundamentalType* fType, fundTypes) {
               xmlWriter.writeStartElement("FundamentalType");
               xmlWriter.writeAttribute("id",QString::number(fType->getId()));
               xmlWriter.writeAttribute("name",fType->getName());
               xmlWriter.writeAttribute("size",QString::number(fType->getSize()));
               xmlWriter.writeEndElement();
            }
            foreach (Array* aType, arrays) {
               xmlWriter.writeStartElement("Array");
               xmlWriter.writeAttribute("id",QString::number(aType->getId()));
               xmlWriter.writeAttribute("type",QString::number(aType->getType()));
               xmlWriter.writeAttribute("size",QString::number(aType->getSize()));
               xmlWriter.writeAttribute("count",QString::number(aType->getCnt()));
               xmlWriter.writeEndElement();
            }
            foreach (Structure* sType, structs) {
               xmlWriter.writeStartElement("Struct");
               xmlWriter.writeAttribute("id",QString::number(sType->getId()));
               xmlWriter.writeAttribute("name",sType->getName());
               xmlWriter.writeAttribute("size",QString::number(sType->getSize()));
               for(int i=0;i<sType->getMembers().count();i++) {
                   xmlWriter.writeStartElement("FieldID");
                   xmlWriter.writeAttribute("type",QString::number(sType->getMembers().at(i)));
                   xmlWriter.writeEndElement();
               }
               xmlWriter.writeEndElement();
            }
            foreach (Field* fieldType, fields) {
               xmlWriter.writeStartElement("Field");
               xmlWriter.writeAttribute("id",QString::number(fieldType->getId()));
               xmlWriter.writeAttribute("name",fieldType->getName());
               xmlWriter.writeAttribute("type",QString::number(fieldType->getType()));
               xmlWriter.writeAttribute("offset",QString::number(fieldType->getOffset()));
               xmlWriter.writeEndElement();
            }
            foreach (Variable* v, variables) {
               xmlWriter.writeStartElement("Variable");
               xmlWriter.writeAttribute("id",QString::number(v->getId()));
               xmlWriter.writeAttribute("name",v->getName());
               xmlWriter.writeAttribute("type",QString::number(v->getType()));
               xmlWriter.writeAttribute("memory",v->getMemType());
               xmlWriter.writeAttribute("address","0x"+QString::number(v->getAddress()-0x20000000,16));
               xmlWriter.writeEndElement();
            }
            xmlWriter.writeEndElement();
            xmlWriter.writeEndDocument();
        }
        return true;
    }
    return false;
}

bool VarParser::readMapFile()
{
    QString fName = RCompiler::getMapFileName();
    QFile file(fName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;
    // чтение map файла
    QTextStream in(&file);

    while (!in.atEnd()) {
       QString line = in.readLine();
       if(line.contains("OBJECT")) {
           QStringList fields = line.split(QRegExp("[\\s\\t]+"));
           fields.removeFirst();
           if(fields.count()==8) {
               bool convRes = false;
               int varAddress = fields[1].toInt(&convRes,16);
               if(convRes) mapOfVars.insert(fields.last(),varAddress);
           }
       }
    }
    file.close();
    // добавить адреса к описанию переменных
    // если переменная отсутствует в карте памяти - удалить из списка
    QVector<Variable*> tmpVarList;
    QVector<Variable*> missingVarList;  // список переменных, отсутствующих в карте памяти
    foreach (Variable* v, variables) {
       QString varName = v->getName().remove(QRegExp("[\\s\\t]+")).remove(QRegExp("\\[\\d+\\]"));
       if(mapOfVars.keys().contains(varName)) {
           int addr = mapOfVars.value(varName);
           tmpVarList += v;
           v->setAddress(addr);
           v->setMemType("RAM");
       }else missingVarList += v;
    }
    variables = tmpVarList;
    for(int i=0;i<missingVarList.count();i++) delete missingVarList[i];
    return true;
}

// добавление одномерного или многомерного массива
VarParser::Array *VarParser::addArray(const QVector<int> &dimension, int baseTypeID)
{
    // поиск базового типа
    int baseSize=0;
    for(int j=0;j<fundTypes.count();j++) {
        if(fundTypes.at(j)->getId()==baseTypeID) {baseSize = fundTypes.at(j)->getSize();break;}
    }
    if(baseSize==0) for(int j=0;j<structs.count();j++) {
        if(structs.at(j)->getId()==baseTypeID) {baseSize = structs.at(j)->getSize();break;}
    }
    if(baseSize==0) baseSize=1;

    // переворачивание размерностей массива базовым индексом к началу (для удобства анализа)
    QVector<int> reverseDmension;
    foreach (int value, dimension) {
       reverseDmension.prepend(value);
    }
    QVector<Array*> resArrays;
    for(int i=0;i<reverseDmension.count();i++) {
        Array* ptr = new Array();
        ptr->setId(idNum++);
        ptr->setCnt(reverseDmension.at(i)); // разрядность массива
        if(i==0) {
            ptr->setType(baseTypeID); // первый элемент ссылается на базовый тип
            ptr->setSize(baseSize*reverseDmension.first());
        }
        else {
            // последующие на предшествующие массивы
            ptr->setType(resArrays.at(i-1)->getId());
            ptr->setSize(reverseDmension.at(i)*resArrays.at(i-1)->getSize());
        }
        resArrays += ptr;
    }
    foreach (Array* arr, resArrays) {
       arrays+=arr;
    }
    return resArrays.last();
}

void VarParser::addStruct(const QString &name, const QString &body, const QString &vars)
{
    // запрет на вложенные структуры
    if(body.contains("struct")) return;
    // Поиск полей с описаниями переменных одного типа
    QStringList varList = body.split(';');
    varList.removeAll("");
    int offset = 0;
    QVector<Field*> structFields;
    Structure* bufStr;
    int maxSize=0;  // размер максимального выравнивания полей для общего выравнивания структуры
    int structSize=0;   // размер структуры

    foreach (QString var, varList) {
       if(var.contains(QRegExp("\\w"))==false) continue;
       var.remove(QRegExp("=[\\s\\t]*\\d+"));   // удаление инициализации
       // определение базового типа
       var.replace(QRegExp("[\\s\\t]+")," ");   // удаление лишних пробелов и символов табуляции
       QVector<FundamentalType*> fTypes;
       // перебор всех стандартных типов данных
       for(int i=0;i<fundTypes.count();i++) {
           if(var.contains(fundTypes.at(i)->getName())) fTypes+=fundTypes.at(i);
       }
       // поиск типа данных с максимальной длиной строки
       if(fTypes.count()==0) return;
       int maxLengthTypeNum = 0;
       int length = fTypes.at(0)->getName().length();
       for(int i=1;i<fTypes.count();i++) {
           if(fTypes.at(i)->getName().length()>length) {
               maxLengthTypeNum = i;
               length = fTypes.at(i)->getName().length()>length;
           }
       }
       // удаление имени типа из строки
       var.remove(QRegExp(".*"+fTypes.at(maxLengthTypeNum)->getName()));
       // удаление пробелов
       var.remove(QRegExp("[\\s\\t]+"));
       // вычленение имён переменных
       QStringList varNames = var.split(',');
       foreach (QString curVarName, varNames) {
           Field* field = new Field();
           int size=0;
           // проверка на указатели
           if(curVarName.at(0)=='*') {
               for(int i=0;i<structFields.count();i++) delete structFields.at(i);
               delete field;
               return;
           }
           // массивы
           Array* ptr = checkArray(curVarName,fTypes.at(maxLengthTypeNum)->getId());
           if(ptr!=nullptr) {
               field->setType(ptr->getId());
               size = ptr->getSize();
               // смещение для массива определяется смещением базового элемента
               while(offset%fTypes.at(maxLengthTypeNum)->getSize()) offset++;
               if(fTypes.at(maxLengthTypeNum)->getSize()>maxSize) maxSize=fTypes.at(maxLengthTypeNum)->getSize();
           }else{
               field->setType(fTypes.at(maxLengthTypeNum)->getId());
               size = fTypes.at(maxLengthTypeNum)->getSize();
               while(offset%size!=0) offset++;
               if(size>maxSize) maxSize=size;
           }
           field->setOffset(offset);
           structSize = offset + size;
           offset+=size;
           field->setName(curVarName);
           field->setId(idNum++);
           structFields+=field;
       }
    }
    if(structFields.count()==0) return;
    bufStr = new Structure();
    QString structName = name;
    structName.remove(QRegExp("[\\s\\t]+"));
    bufStr->setName(structName);


    QVector<int> idOfFieldType;
    for(int i=0;i<structFields.count();i++) {
        idOfFieldType+=structFields.at(i)->getId();
        fields += structFields.at(i);
    }
    while(structSize%maxSize!=0) structSize++;
    bufStr->setSize(structSize);
    bufStr->setMembers(idOfFieldType);
    bufStr->setId(idNum++);
    // для безымянных структур в качестве имени используется идентификатор
    if(bufStr->getName().isEmpty()) bufStr->setName(QString::number(bufStr->getId()));
    structs += bufStr;


    QStringList varNames = vars.split(',');
    foreach (QString varName, varNames) {
       varName.remove(QRegExp("[\\s\\t]+"));
       if(!varName.isEmpty()) addStructVar(bufStr->getName(),varName);
    }
}

// добавление переменной типа структура
void VarParser::addStructVar(const QString &structName, const QString &varName)
{
    QString sName = structName;
    sName.remove(QRegExp("[\\s\\t]+"));
    if(sName.isEmpty()) return;
    QStringList varList = varName.split(',');
    for(int i=0;i<varList.count();i++) {
        varList[i].remove(QRegExp("=.*"));
        varList[i].remove(QRegExp("[\\s\\t]+"));
        if(varList[i].isEmpty()==false) {
            foreach (Structure* s, structs) {
               if(s->getName()==sName) {

                   Variable* v = new Variable();
                   v->setName(varList.at(i));

                   // проверка на массив
                   Array* ptr = checkArray(varList.at(i),s->getId());
                   if(ptr!=nullptr) {
                       v->setType(ptr->getId());
                   }else v->setType(s->getId());

                   v->setId(idNum++);
                   variables += v;
               }
            }
        }
    }
}

// конструктор фундаментальных типов
void VarParser::createFundTypes()
{
    // порядок должен отвечать требованию большая строка, меньшая строка
    // сортировка для облегчения разбора переменных
    struct sType{QString name;int size;}standTypes[] =
    {
        {VarItem::ucharType,1},
        {VarItem::charType,1},
        {VarItem::ushortType,2},
        {VarItem::shortType,2},
        {VarItem::uintType,4},
        {VarItem::intType,4},
        {VarItem::longLongType,8},
        {VarItem::ulongType,4},
        {VarItem::longType,4},
        {VarItem::floatType,4},
        {VarItem::doubleType,8}
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

VarParser::Array *VarParser::checkArray(const QString &varDef, int basetype)
{
    Array *ptr = nullptr;
    if(varDef.contains(QRegExp("[\\[\\]]"))){
        QRegExp arrayDimension("\\[\\s*(\\d+)\\s*\\]");
        int indexPos=0;
        QStringList dimensionStr;
        while(1) {
         indexPos = arrayDimension.indexIn(varDef,indexPos);
         if(indexPos==-1) break;
         dimensionStr += arrayDimension.cap(1);
         indexPos++;
        }
        if(dimensionStr.count()) {
            QVector<int> dimensionNum;
            foreach (QString dim, dimensionStr) {
               dimensionNum+=dim.toInt();
            }
            ptr = addArray(dimensionNum,basetype);
        }
    }
    return ptr;
}

void VarParser::clearVarTree()
{
    while (arrays.count()){
        Array* ptr = arrays.last();
        arrays.removeLast();
        delete ptr;
    }
    while (structs.count()) {
        Structure* ptr = structs.last();
        structs.removeLast();
        delete ptr;
    }
    while (fields.count()) {
        Field* ptr = fields.last();
        fields.removeLast();
        delete ptr;
    }
    while(variables.count()) {
        Variable* ptr = variables.last();
        variables.removeLast();
        delete ptr;
    }
}

int VarParser::idNum = 0;

VarParser::VarParser(const QString &fName)
{
    idNum = 0;
    inpFileName = fName;
    createFundTypes();
}

bool VarParser::createXML()
{
    clearVarTree();
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

bool VarParser::readSitNum(QVector<int> &addr, QVector<int> &prNum)
{
    QString fName = RCompiler::getMapFileName();
    QFile file(fName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;
    QTextStream in(&file);

    while (!in.atEnd()) {
       QString line = in.readLine();
       if(line.contains("OBJECT")) {
           QStringList fields = line.split(QRegExp("[\\s\\t]+"));
           fields.removeFirst();
           if(fields.count()==8) {
               bool convRes = false;
               int varAddress = fields[1].toInt(&convRes,16);
               if(convRes) {
                   QString vName = fields.last();
                   QRegExp pNumExpr("_Sys4x_p(\\d+)");
                   if(pNumExpr.indexIn(vName)!=-1) {
                       prNum += pNumExpr.cap(1).toInt();
                       addr += varAddress - 0x20000000;
                   }
               }
           }
       }
    }
    file.close();
    return true;
}

VarParser::~VarParser()
{
    for(int i=0;i<fundTypes.count();i++) {
        delete fundTypes.at(i);
    }
}

VarParser::FundamentalType::FundamentalType():id(0),name(""),size(0)
{

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

VarParser::Variable::Variable():id(0),name(""),type(1),address(0),memType("")
{

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

QString VarParser::Structure::getName() const
{
    return name;
}

void VarParser::Structure::setName(const QString &value)
{
    name = value;
}

int VarParser::Structure::getSize() const
{
    return size;
}

void VarParser::Structure::setSize(int value)
{
    size = value;
}

VarParser::Structure::Structure():id(0),name(""),size(0)
{

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

VarParser::Field::Field(): id(0), name(""), type(1), offset(0)
{

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


int VarParser::Array::getCnt() const
{
    return cnt;
}

void VarParser::Array::setCnt(int value)
{
    cnt = value;
}

VarParser::Array::Array():id(0),type(1),size(0),cnt(0)
{

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
