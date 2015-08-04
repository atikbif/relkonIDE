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
    allData.remove(QRegExp("[\\r\\n]+"));
    allData.replace(QRegExp("[\\s\\t]+")," ");
    allData. remove(QRegExp("=[\\s\\t]*[\\d\\.]+"));

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
                        //curVarName.remove();
                        if(curVarName.isEmpty()) continue;
                        Variable* var = new Variable();
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
            //pos+=structVarExpr.matchedLength();
        }
    }
    dataBlock.clear();
    dataBlock += allData;
}

bool VarParser::buildXML()
{
    return true;
}

// добавление одномерного или многомерного массива
VarParser::Array *VarParser::addArray(const QVector<int> &dimension, int baseTypeID)
{
    Array* ptr = nullptr;
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
        ptr = new Array();
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
        {"unsigned char",1},
        {"char",1},
        {"unsigned short",2},
        {"short",2},
        {"unsigned int",4},
        {"int",4},
        {"long long",8},
        {"unsigned long",4},
        {"long",4},
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


int VarParser::Array::getCnt() const
{
    return cnt;
}

void VarParser::Array::setCnt(int value)
{
    cnt = value;
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
