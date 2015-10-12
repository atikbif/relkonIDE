#include "ccodecreator.h"
#include "LCD/displaystr.h"
#include <QRegExp>

CCodeCreator::CCodeCreator()
{

}

QStringList CCodeCreator::getText(const Display &d)
{
    QStringList code;

    for(int i=0;i<d.getStrCount();i++) {
        code << "const unsigned char str" + QString::number(i+1) + "[][" + QString::number(d.getLength()) + "]={\n";
        for(int j=0;j<d.getSubStrCount(i);j++) {
            QString strData;
            strData="{";
            QByteArray bytes = d.getString(i,j).getString();
            foreach (int symb, bytes) {
                strData+="0x"+QString::number(quint8(symb),16) + ',';
            }
            strData.remove(strData.length()-1,1);
            strData+="}";
            if(j!=d.getSubStrCount(i)-1) strData+=",\n";
            code << strData;
        }
        code << "};\n";
    }

    code << "void print_var(void)\n";
    code << "{\n";


    for(int i=0;i<d.getStrCount();i++) {
        code << "\tswitch(_Sys.S" + QString::number(i+1) + ")\n\t{\n";

        for(int j=0;j<d.getSubStrCount(i);j++) {
            QVector<PultVarDefinition> varList;
            d.getVarDefinitions(varList,i,j);
            QString prVarsStr;
            foreach (PultVarDefinition vDef, varList) {
               //if(vDef.getSubStrNum()==j) {
                   if(!vDef.getName().isEmpty()) {
                       QString varTypeStr = vDef.getDataType();
                       if(vDef.getForceSign()) varTypeStr.remove("unsigned ");
                       quint8 varTypeNum=0x01;
                       if(varTypeStr=="unsigned char") varTypeNum = 0x01;
                       else if(varTypeStr=="unsigned short") varTypeNum = 0x02;
                       else if(varTypeStr=="unsigned int") varTypeNum = 0x03;
                       else if(varTypeStr=="unsigned long") varTypeNum = 0x03;
                       else if(varTypeStr=="char") varTypeNum = 0x81;
                       else if(varTypeStr=="short") varTypeNum = 0x82;
                       else if(varTypeStr=="int") varTypeNum = 0x83;
                       else if(varTypeStr=="long") varTypeNum = 0x83;
                       else if(varTypeStr=="long long") varTypeNum = 0x83;
                       int pos = vDef.getPosInStr();
                       QString varPat = vDef.getPattern();
                       if(varPat.contains(QRegExp("^[+\\-]"))) {
                           pos++;
                           if(pos>=d.getLength()) pos--;
                           varPat.remove(QRegExp("^[+\\-]"));
                       }
                       int fractionLength = 0;
                       QRegExp frExp("\\.(\\d+)$");
                       if(frExp.indexIn(varPat) != -1) fractionLength = frExp.cap(1).length();
                       varPat.remove(".");
                       varPat.remove(",");
                       if(varTypeStr.contains("float")||(varTypeStr.contains("double"))) {
                           prVarsStr += "\t\t\tprint_float("+vDef.getName()+"," +
                                   QString::number(i+1) + "," + QString::number(pos+1) +
                                   "," + QString::number(varPat.length()) +
                                   "," + QString::number(fractionLength) + ");\n";
                       }else {
                           if(vDef.getIsEditable()) {
                                if(vDef.getIsEEVar()) {
                                    prVarsStr += "\t\t\tprint_edit_ee(" + QString::number(vDef.getEEposInSettingsTable()) +
                                            "," + QString::number(i+1) + "," + QString::number(pos+1) +
                                            "," + QString::number(varPat.length()) +
                                            "," + QString::number(fractionLength) + "," +
                                            QString::number(varTypeNum) + ");\n";
                                }else {
                                    if(vDef.getName().contains("sysTime_")) {
                                        int tCode = -1;
                                        if(vDef.getName().contains("sec")) tCode=0;
                                        else if(vDef.getName().contains("min")) tCode=1;
                                        else if(vDef.getName().contains("hour")) tCode=2;
                                        else if(vDef.getName().contains("date")) tCode=3;
                                        else if(vDef.getName().contains("month")) tCode=4;
                                        else if(vDef.getName().contains("year")) tCode=5;
                                        if(tCode != -1) {
                                            prVarsStr += "\t\tprint_time(" +
                                                QString::number(i+1) + "," + QString::number(pos+1) +
                                                "," + QString::number(tCode) + ");\n";
                                        }
                                    }else {
                                        prVarsStr += "\t\t\tprint_edit(&" + vDef.getName()+"," +
                                                QString::number(i+1) + "," + QString::number(pos+1) +
                                                "," + QString::number(varPat.length()) +
                                                "," + QString::number(fractionLength) + "," +
                                                QString::number(varTypeNum) + ");\n";
                                    }
                                }
                           }else {
                               prVarsStr += "\t\t\tprint_long("+vDef.getName()+"," +
                                       QString::number(i+1) + "," + QString::number(pos+1) +
                                       "," + QString::number(varPat.length()) +
                                       "," + QString::number(fractionLength) + ");\n";
                           }

                       }
                   }
               //}
            }
            if(!prVarsStr.isEmpty()) {
                prVarsStr = "\t\tcase " + QString::number(j) + ":\n" + prVarsStr + "\t\tbreak;\n";
                code << prVarsStr;
            }
        }
        code << "\t\tdefault:break;\n\t}\n";
    }

    code << "}\n";

    return code;
}

CCodeCreator::~CCodeCreator()
{

}

