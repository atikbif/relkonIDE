#include "rp6creator.h"
#include "pathstorage.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>

RP6Creator::RP6Creator()
{

}

bool RP6Creator::createRelkon6ProjectFile(VarsCreator * varOwner)
{
    bool res =false;
    QFile inpFile(":/empty.rp6");
    if(inpFile.open(QFile::ReadOnly)) {
        QTextStream input(&inpFile);
        QString body = input.readAll();
        inpFile.close();
        // формирование содержимого
        // поиск стартового адреса заводских настроек в XRAM
        QFile mapFile(PathStorage::getMapFileFullName());
        if(mapFile.open(QFile::ReadOnly)) {
            QTextStream inputMap(&mapFile);
            QString mapBody = inputMap.readAll();
            QRegExp exp("[\\d]+:\\s+([\\dabcdef]+)\\s+\\d+\\s+OBJECT\\s+GLOBAL\\s+DEFAULT\\s+[\\d]+\\s+_Sys[\\n\\r]");
            int pos = exp.indexIn(mapBody);
            if(pos!=-1) {
                int addr = exp.cap(1).toInt(&res,16);
                if(res) {
                    addr-=0x20000000;
                    res = false;
                    QRegExp eeExpr("<EEStart>[\\r\\n]");
                    pos = eeExpr.indexIn(body);
                    if(pos!=-1) {
                        res = true;
                        body.remove(pos,eeExpr.matchedLength());
                        for(int i=0;i<1024;i++) {
                            QString eeStr;
                            if(i!=0) eeStr +="    ";
                            eeStr += "<ControllerVar xsi:type=\"ControllerEmbeddedVar\" Name=\"EE";
                            eeStr += QString::number(i) + "\" Address=\"";
                            eeStr += QString::number(addr+i) + "\" Size=\"1\" Memory=\"XRAM\" HasSign=\"false\" Real=\"false\" Value=\"0\" />\n";
                            body.insert(pos,eeStr);
                            pos+=eeStr.length();
                        }
                        for(int i=0;i<512;i++) {
                            QString eeStr;
                            eeStr +="    ";
                            eeStr += "<ControllerVar xsi:type=\"ControllerEmbeddedVar\" Name=\"EE";
                            eeStr += QString::number(i*2) + "i\" Address=\"";
                            eeStr += QString::number(addr+i*2) + "\" Size=\"2\" Memory=\"XRAM\" HasSign=\"false\" Real=\"false\" Value=\"0\" />\n";
                            body.insert(pos,eeStr);
                            pos+=eeStr.length();
                        }
                        for(int i=0;i<256;i++) {
                            QString eeStr;
                            eeStr +="    ";
                            eeStr += "<ControllerVar xsi:type=\"ControllerEmbeddedVar\" Name=\"EE";
                            eeStr += QString::number(i*4) + "l\" Address=\"";
                            eeStr += QString::number(addr+i*4) + "\" Size=\"4\" Memory=\"XRAM\" HasSign=\"false\" Real=\"false\" Value=\"0\" />\n";
                            body.insert(pos,eeStr);
                            pos+=eeStr.length();
                        }
                        IDStorage& st = varOwner->getIDStorage();
                        QStringList idList = st.getIDs();
                        foreach (QString id, idList) {
                            CompositeVar var;
                            if(st.getVarByID(id,var)) {
                                if((var.getChildrenCount()==0)&&(var.getMemType()=="RAM")) {
                                    if(var.getName().contains(QRegExp("\\D"))) {
                                        QString eeStr;
                                        eeStr +="    ";
                                        eeStr += "<ControllerVar xsi:type=\"ControllerUserVar\" Name=\"" + var.getName() +"\"";
                                        eeStr += " Address=\"";
                                        eeStr += QString::number(var.getMemAddress()) + "\" Size=\"";
                                        eeStr += QString::number(var.getByteCount()) +"\" Memory=\"";
                                        eeStr += "XRAM\" HasSign=\"false\" Real=\"false\" Array=\"false\" />\n";
                                        body.insert(pos,eeStr);
                                        pos+=eeStr.length();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            mapFile.close();
        }
        if(res) {
            res = false;
            // сохранение результата
            QFile outFile(PathStorage::getBuildDir() + "/project.rp6");
            if(outFile.open(QFile::WriteOnly)) {
                QTextStream output(&outFile);
                output << body;
                outFile.close();
                res = true;
            }
        }
    }
    return res;
}
