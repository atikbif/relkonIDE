#include "ccodecreator.h"
#include "LCD/displaystr.h"
#include <QRegExp>
#include "VarDef/varitem.h"

void CCodeCreator::printData(const Display &d, QStringList &code)
{
    for(int i=0;i<d.getStrCount();i++) {
        code << "const unsigned char str" + QString::number(i+1) + "[][" + QString::number(d.getLength()) + "]={\n";
        int subStrCount = d.getSubStrCount(i);
        for(int j=0;j<subStrCount;j++) {
            if(d.getString(i,j).isActive()) {
                QString strData("{");
                QByteArray bytes = d.getString(i,j).getString();
                foreach (int symb, bytes) {
                    strData+="0x"+QString::number(quint8(symb),16) + ',';
                }
                strData.remove(strData.length()-1,1);   // remove last ','
                strData+="}";
                if(j!=d.getSubStrCount(i)-1) strData+=",\n";
                code << strData;
            }
        }
        code << "};\n";
    }
}

quint8 CCodeCreator::getVarType(const QString &vType)
{
    // коды типов данных обусловлены требованиями ПО нижнего уровня
    quint8 varTypeNum=0x01;
    if(vType==VarItem::ucharType) varTypeNum = 0x01;
    else if(vType==VarItem::ushortType) varTypeNum = 0x02;
    else if(vType==VarItem::uintType) varTypeNum = 0x03;
    else if(vType==VarItem::ulongType) varTypeNum = 0x03;
    else if(vType==VarItem::charType) varTypeNum = 0x81;
    else if(vType==VarItem::shortType) varTypeNum = 0x82;
    else if(vType==VarItem::intType) varTypeNum = 0x83;
    else if(vType==VarItem::longType) varTypeNum = 0x83;
    else if(vType==VarItem::longLongType) varTypeNum = 0x83;
    return varTypeNum;
}

void CCodeCreator::correctVarPos(const Display &d, QString &pattern, int &pos)
{
    // сдвиг положения переменной вправо если шаблон содержит + или -
    if(pattern.contains(QRegExp("^[+\\-]"))) {
        pos++;
        if(pos>=d.getLength()) pos--;
        pattern.remove(QRegExp("^[+\\-]"));
    }
}

int CCodeCreator::getFractionLength(const QString &pattern)
{
    int fractionLength = 0;  // число знакомест после запятой
    QRegExp frExp("\\.(\\d+)$");
    if(frExp.indexIn(pattern) != -1) fractionLength = frExp.cap(1).length();
    return fractionLength;
}

void CCodeCreator::removeComma(QString &pattern)
{
    pattern.remove(".");
    pattern.remove(",");
}

QString CCodeCreator::printFloatVar(const QString &name, int str, int pos, int length, int frLength)
{
    QString res = "\t\t\tprint_float("+name+"," +
            QString::number(str+1) + "," + QString::number(pos+1) +
            "," + QString::number(length) +
            "," + QString::number(frLength) + ");";
    return res;
}

QString CCodeCreator::printEditEEVar(int eePosInTable, int str, int pos, int length, int frLength, int vType)
{
    QString res = "\t\t\tprint_edit_ee(" + QString::number(eePosInTable) +
        "," + QString::number(str+1) + "," + QString::number(pos+1) +
        "," + QString::number(length) +
        "," + QString::number(frLength) + "," +
        QString::number(vType) + ");";
    return res;
}

QString CCodeCreator::printTimeVar(const QString &name, int str, int pos)
{
    int tCode = -1;
    if(name.contains("sec")) tCode=0;
    else if(name.contains("min")) tCode=1;
    else if(name.contains("hour")) tCode=2;
    else if(name.contains("date")) tCode=3;
    else if(name.contains("month")) tCode=4;
    else if(name.contains("year")) tCode=5;
    if(tCode != -1) {
        QString res = "\t\tprint_time(" +
            QString::number(str+1) + "," + QString::number(pos+1) +
            "," + QString::number(tCode) + ");";
        return res;
    }
    return QString();
}

QString CCodeCreator::printPlainEditVar(const QString &name, int str, int pos, int length, int frLength, int vType)
{
    QString res = "\t\t\tprint_edit(&" + name +"," +
            QString::number(str+1) + "," + QString::number(pos+1) +
            "," + QString::number(length) +
            "," + QString::number(frLength) + "," +
            QString::number(vType) + ");";
    return res;
}

QString CCodeCreator::printLongVar(const QString &name, int str, int pos, int length, int frLength)
{
    QString res = "\t\t\tprint_long("+name+"," +
       QString::number(str+1) + "," + QString::number(pos+1) +
       "," + QString::number(length) +
       "," + QString::number(frLength) + ");";
    return res;
}

QString CCodeCreator::printVar(const Display &d, const PultVarDefinition &vDef, int str)
{
    QString res;
    QString varTypeStr = vDef.getDataType();
    if(vDef.getForceSign()) varTypeStr.remove("unsigned ");
    quint8 varTypeNum=getVarType(varTypeStr);
    int pos = vDef.getPosInStr();
    QString varPat = vDef.getPattern();
    correctVarPos(d,varPat,pos);
    int fractionLength = getFractionLength(varPat);
    removeComma(varPat);
    if(varTypeStr.contains("float")||(varTypeStr.contains("double"))) {
        res = printFloatVar(vDef.getName(),str,pos,varPat.length(),fractionLength);
    }else {
        if(vDef.isEditable()) {
             if(vDef.isEEVar()) {
                 res = printEditEEVar(vDef.getEEposInSettingsTable(),
                     str,pos,varPat.length(),fractionLength,varTypeNum);
             }else {
                 if(vDef.getName().contains("sysTime_")) {
                     res = printTimeVar(vDef.getName(),str,pos);
                 }else {
                     res = printPlainEditVar(vDef.getName(),str,pos,varPat.length(),fractionLength,varTypeNum);
                 }
             }
        }else {
            res = printLongVar(vDef.getName(),str,pos,varPat.length(),fractionLength);
        }
    }
    return res;
}

CCodeCreator::CCodeCreator()
{

}

QStringList CCodeCreator::getText(const Display &d)
{
    QStringList code;

    printData(d,code);

    code << "\n";

    code << "void print_var(void)\n";
    code << "{\n";

    for(int i=0;i<d.getStrCount();i++) {
        code << "\tswitch(_Sys.S" + QString::number(i+1) + ")\n\t{\n";
        unsigned short invisVarCnt = 0;
        for(int j=0;j<d.getSubStrCount(i);j++) {
            if(d.getString(i,j).isActive()){
                QVector<PultVarDefinition> varList;
                d.getVarDefinitions(varList,i,j);
                QString prVarsStr;
                foreach (PultVarDefinition vDef, varList) {
                   if(!vDef.getName().isEmpty()) {
                       prVarsStr += printVar(d,vDef,i) + "// PULT " + QString::number(i+1) + ":" +QString::number(j-invisVarCnt) + "\n";
                   }
                }
                if(!prVarsStr.isEmpty()) {
                    prVarsStr = "\t\tcase " + QString::number(j-invisVarCnt) + ":\n" +
                            prVarsStr + "\t\tbreak;\n";
                    code << prVarsStr;
                }
            }else invisVarCnt++;
        }
        code << "\t\tdefault:break;\n\t}\n";
    }

    code << "}\n";

    return code;
}

CCodeCreator::~CCodeCreator()
{

}

