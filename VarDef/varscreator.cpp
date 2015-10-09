#include "varscreator.h"
#include <QThread>
#include <RCompiler/rcompiler.h>
#include <QDomDocument>
#include <QFile>
#include "varparser.h"
#include "Debugger/memstorage.h"

void VarsCreator::addVarToTree(const QDomElement &e, CompositeVar *var, CompositeVar *parent)
{
    if(parent == nullptr) return;
    if(e.tagName()=="FundamentalType") {
        var->setDataType(e.attribute("name"));
        parent->addChild(*var);
        ids.addVar(var);
    }else if(e.tagName()=="Variable") {
        bool res = false;
        int type = e.attribute("type").toInt(&res);
        if(res) {
            QDomElement ee = allData.at(elemByID.value(type)).toElement();
            addVarToTree(ee,var,parent);
        }
    }else if(e.tagName()=="Struct") {
        var->setDataType("структура");
        parent->addChild(*var);
        ids.addVar(var);
        QDomNodeList fields = e.childNodes();
        for(int i=0;i<fields.count();i++) {
            // fieldID
            QDomNode n = fields.item(i);
            QDomElement ee = n.toElement();
            if(!ee.isNull()) {
                bool res = false;
                int type = ee.attribute("type").toInt(&res);
                if(res) {
                    QDomElement eee = allData.at(elemByID.value(type)).toElement();
                    CompositeVar *v = new CompositeVar();
                    v->setMemType(var->getMemType());
                    v->setMemAddress(var->getMemAddress()+eee.attribute("offset").toInt());
                    addVarToTree(eee,v,var);
                }
            }
        }
    }else if(e.tagName()=="Field") {
        var->setName(e.attribute("name"));
        bool res = false;
        int type = e.attribute("type").toInt(&res);
        if(res) {
            QDomElement ee = allData.at(elemByID.value(type)).toElement();
            addVarToTree(ee,var,parent);
        }
    }else if(e.tagName()=="Array") {
        QString name = var->getName();
        name.remove(QRegExp("\\[\\d+\\]"));
        var->setName(name);
        var->setDataType("архив");

        parent->addChild(*var);
        ids.addVar(var);
        bool res = false;
        int type = e.attribute("type").toInt(&res);
        if(res) {
            QDomElement ee = allData.at(elemByID.value(type)).toElement();
            int cnt = e.attribute("count").toInt();
            int offset = e.attribute("size").toInt()/cnt;
            for(int i=0;i<cnt;i++) {
                CompositeVar* v = new CompositeVar();
                v->setName(QString::number(i));
                v->setMemType(var->getMemType());
                v->setMemAddress(var->getMemAddress()+offset*i);
                addVarToTree(ee,v,var);
            }
        }
    }
}

void VarsCreator::createSysVars(CompositeVar* parent)
{
    addDiscrInputs(parent);
    addDiscrOutputs(parent);
    addAnalogInputs(parent);
    addAnalogOutputs(parent);
    addFactorySettings(parent);
    addDispVar(parent);
    addSituationNum(parent);
    addTimeVars(parent);
}

void VarsCreator::addDiscrInputs(CompositeVar *parent)
{
    CompositeVar* diVar = new CompositeVar();
    diVar->setName("DI");
    for(int i=0;i<6;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName(((i>=4)?"DIN":"IN")+QString::number(i));
        for(int j=0;j<8;j++) {
            CompositeVar* bit = new CompositeVar();
            bit->setName(QString::number(j));
            bit->setBitNum(j);
            bit->setDataType(VarItem::ucharType);
            bit->setMemType("IO");
            bit->setMemAddress(i);
            var->addChild(*bit);
            ids.addVar(bit);
        }
        diVar->addChild(*var);
        ids.addVar(var);
    }

    CompositeVar* mmbVar = new CompositeVar();
    mmbVar->setName("MMB");
    mmbVar->setMemAddress(0);   // для различия с другими узлами MMB
    for(int i=0;i<32;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("IN"+QString::number(i+4));
        for(int j=0;j<4;j++) {
            CompositeVar* bit = new CompositeVar();
            bit->setName(QString::number(j));
            bit->setBitNum(j);
            bit->setDataType(VarItem::ucharType);
            bit->setMemType("IO");
            bit->setMemAddress(0x24+i);
            var->addChild(*bit);
            ids.addVar(bit);
        }
        mmbVar->addChild(*var);
        ids.addVar(var);
    }
    diVar->addChild(*mmbVar);
    ids.addVar(mmbVar);

    parent->addChild(*diVar);
    ids.addVar(diVar);
}

void VarsCreator::addDiscrOutputs(CompositeVar *parent)
{
    CompositeVar* doVar = new CompositeVar();
    doVar->setName("DO");
    for(int i=0;i<6;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName(((i>=4)?"DOUT":"OUT")+QString::number(i));
        for(int j=0;j<8;j++) {
            CompositeVar* bit = new CompositeVar();
            bit->setName(QString::number(j));
            bit->setBitNum(j);
            bit->setDataType(VarItem::ucharType);
            bit->setMemType("IO");
            bit->setMemAddress(0x06+i);
            var->addChild(*bit);
            ids.addVar(bit);
        }
        doVar->addChild(*var);
        ids.addVar(var);
    }

    CompositeVar* mmbVar = new CompositeVar();
    mmbVar->setName("MMB");
    mmbVar->setMemAddress(1);   // для различия с другими узлами MMB
    for(int i=0;i<32;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("OUT"+QString::number(i+4));
        for(int j=0;j<4;j++) {
            CompositeVar* bit = new CompositeVar();
            bit->setName(QString::number(j));
            bit->setBitNum(j);
            bit->setDataType(VarItem::ucharType);
            bit->setMemType("IO");
            bit->setMemAddress(0x44+i);
            var->addChild(*bit);
            ids.addVar(bit);
        }
        mmbVar->addChild(*var);
        ids.addVar(var);
    }
    doVar->addChild(*mmbVar);
    ids.addVar(mmbVar);

    parent->addChild(*doVar);
    ids.addVar(doVar);

}

void VarsCreator::addAnalogInputs(CompositeVar *parent)
{
    CompositeVar* aiVar = new CompositeVar();
    aiVar->setName("AI");
    for(int i=0;i<8;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("ADC"+QString::number(i+1));
        var->setDataType(VarItem::ushortType);
        var->setMemType("IO");
        var->setMemAddress(0x0C+i*2);

        aiVar->addChild(*var);
        ids.addVar(var);
    }

    CompositeVar* mmbVar = new CompositeVar();
    mmbVar->setName("MMB");
    mmbVar->setMemAddress(2);   // для различия с другими узлами MMB
    for(int i=0;i<32;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("ADC"+QString::number(9+i*4)+".."+QString::number(12+i*4));
        for(int j=0;j<4;j++) {
            CompositeVar* intVar = new CompositeVar();
            intVar->setName("ADC"+QString::number(9+i*4+j));
            intVar->setDataType(VarItem::ushortType);
            intVar->setMemType("IO");
            intVar->setMemAddress(0x64+i*8+j*2);
            var->addChild(*intVar);
            ids.addVar(intVar);
        }
        mmbVar->addChild(*var);
        ids.addVar(var);
    }
    aiVar->addChild(*mmbVar);
    ids.addVar(mmbVar);

    parent->addChild(*aiVar);
    ids.addVar(aiVar);
}

void VarsCreator::addAnalogOutputs(CompositeVar *parent)
{
    CompositeVar* aoVar = new CompositeVar();
    aoVar->setName("AO");
    for(int i=0;i<4;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("DAC"+QString::number(i+1));
        var->setDataType(VarItem::ushortType);
        var->setMemType("IO");
        var->setMemAddress(0x1C+i*2);

        aoVar->addChild(*var);
        ids.addVar(var);
    }

    CompositeVar* mmbVar = new CompositeVar();
    mmbVar->setName("MMB");
    mmbVar->setMemAddress(3);   // для различия с другими узлами MMB
    for(int i=0;i<32;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("DAC"+QString::number(5+i*2)+"_"+QString::number(6+i*2));
        for(int j=0;j<2;j++) {
            CompositeVar* intVar = new CompositeVar();
            intVar->setName("DAC"+QString::number(5+i*2+j));
            intVar->setDataType(VarItem::ushortType);
            intVar->setMemType("IO");
            intVar->setMemAddress(0x164+i*4+j*2);
            var->addChild(*intVar);
            ids.addVar(intVar);
        }
        mmbVar->addChild(*var);
        ids.addVar(var);
    }
    aoVar->addChild(*mmbVar);
    ids.addVar(mmbVar);

    parent->addChild(*aoVar);
    ids.addVar(aoVar);
}

void VarsCreator::addFactorySettings(CompositeVar *parent)
{
    CompositeVar* fsVar = new CompositeVar();
    fsVar->setName("Settings");

    CompositeVar* charVar = new CompositeVar();
    charVar->setName("char");
    charVar->setMemAddress(0);   // для различия с другими узлами char
    for(int i=0;i<1024;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("EE"+QString::number(i));
        var->setDataType(VarItem::ucharType);
        var->setMemAddress(0x7B00 + i);
        var->setMemType("FRAM");
        charVar->addChild(*var);
        ids.addVar(var);
    }
    fsVar->addChild(*charVar);
    ids.addVar(charVar);

    CompositeVar* shortVar = new CompositeVar();
    shortVar->setName("short");
    shortVar->setMemAddress(0);   // для различия с другими узлами short
    for(int i=0;i<512;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("EE"+QString::number(i*2)+"i");
        var->setDataType(VarItem::ushortType);
        var->setMemAddress(0x7B00 + i*2);
        var->setMemType("FRAM");
        shortVar->addChild(*var);
        ids.addVar(var);
    }
    fsVar->addChild(*shortVar);
    ids.addVar(shortVar);

    CompositeVar* longVar = new CompositeVar();
    longVar->setName("long");
    longVar->setMemAddress(0);   // для различия с другими узлами long
    for(int i=0;i<256;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("EE"+QString::number(i*4)+"l");
        var->setDataType(VarItem::ulongType);
        var->setMemAddress(0x7B00 + i*4);
        var->setMemType("FRAM");
        longVar->addChild(*var);
        ids.addVar(var);
    }
    fsVar->addChild(*longVar);
    ids.addVar(longVar);

    parent->addChild(*fsVar);
    ids.addVar(fsVar);
}

void VarsCreator::addDispVar(CompositeVar *parent)
{
    CompositeVar* dispVar = new CompositeVar();
    dispVar->setName("Disp");

    CompositeVar* charVar = new CompositeVar();
    charVar->setName("char");
    charVar->setMemAddress(1);   // для различия с другими узлами char
    for(int i=0;i<256;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("MEM"+QString::number(i));
        var->setDataType(VarItem::ucharType);
        var->setMemAddress(i);
        var->setMemType("USER");
        charVar->addChild(*var);
        ids.addVar(var);
    }
    dispVar->addChild(*charVar);
    ids.addVar(charVar);

    CompositeVar* shortVar = new CompositeVar();
    shortVar->setName("short");
    shortVar->setMemAddress(1);   // для различия с другими узлами short
    for(int i=0;i<128;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("MEM"+QString::number(i*2)+"i");
        var->setDataType(VarItem::ushortType);
        var->setMemAddress(i*2);
        var->setMemType("USER");
        shortVar->addChild(*var);
        ids.addVar(var);
    }
    dispVar->addChild(*shortVar);
    ids.addVar(shortVar);

    CompositeVar* longVar = new CompositeVar();
    longVar->setName("long");
    longVar->setMemAddress(1);   // для различия с другими узлами long
    for(int i=0;i<64;i++) {
        CompositeVar* var = new CompositeVar();
        var->setName("MEM"+QString::number(i*4)+"l");
        var->setDataType(VarItem::ulongType);
        var->setMemAddress(i*4);
        var->setMemType("USER");
        longVar->addChild(*var);
        ids.addVar(var);
    }
    dispVar->addChild(*longVar);
    ids.addVar(longVar);

    parent->addChild(*dispVar);
    ids.addVar(dispVar);
}

void VarsCreator::addSituationNum(CompositeVar *parent)
{
    QVector<int> memAddr;
    QVector<int> prNum;
    if(VarParser::readSitNum(memAddr,prNum)) {
        int offset = 4;
        CompositeVar* sitVar = new CompositeVar();
        sitVar->setName("SIT");
            for(int i=0;i<memAddr.count();i++) {
                CompositeVar* var = new CompositeVar();
                var->setName("Proc"+QString::number(prNum.at(i)));
                var->setDataType(VarItem::uintType);
                var->setMemAddress(memAddr.at(i)+offset);
                var->setMemType("RAM");
                var->setEditable(false);
                sitVar->addChild(*var);
                ids.addVar(var);
            }
        parent->addChild(*sitVar);
        ids.addVar(sitVar);
    }
}

void VarsCreator::addTimeVars(CompositeVar *parent)
{
    CompositeVar* tVar = new CompositeVar();
    tVar->setName("TIME");

    CompositeVar* secVar = new CompositeVar();
    secVar->setName("sec");
    secVar->setDataType(VarItem::ucharType);
    secVar->setMemType(MemStorage::timeMemName);
    secVar->setEditable(false);
    tVar->addChild(*secVar);
    ids.addVar(secVar);

    CompositeVar* minVar = new CompositeVar();
    minVar->setName("min");
    minVar->setDataType(VarItem::ucharType);
    minVar->setMemType(MemStorage::timeMemName);
    minVar->setEditable(false);
    tVar->addChild(*minVar);
    ids.addVar(minVar);

    CompositeVar* hourVar = new CompositeVar();
    hourVar->setName("hour");
    hourVar->setDataType(VarItem::ucharType);
    hourVar->setMemType(MemStorage::timeMemName);
    hourVar->setEditable(false);
    tVar->addChild(*hourVar);
    ids.addVar(hourVar);

    CompositeVar* dateVar = new CompositeVar();
    dateVar->setName("date");
    dateVar->setDataType(VarItem::ucharType);
    dateVar->setMemType(MemStorage::timeMemName);
    dateVar->setEditable(false);
    tVar->addChild(*dateVar);
    ids.addVar(dateVar);

    CompositeVar* monthVar = new CompositeVar();
    monthVar->setName("month");
    monthVar->setDataType(VarItem::ucharType);
    monthVar->setMemType(MemStorage::timeMemName);
    monthVar->setEditable(false);
    tVar->addChild(*monthVar);
    ids.addVar(monthVar);

    CompositeVar* yearVar = new CompositeVar();
    yearVar->setName("year");
    yearVar->setDataType(VarItem::ucharType);
    yearVar->setMemType(MemStorage::timeMemName);
    yearVar->setEditable(false);
    tVar->addChild(*yearVar);
    ids.addVar(yearVar);

    parent->addChild(*tVar);
    ids.addVar(tVar);
}

VarsCreator::VarsCreator(QObject *parent) : QObject(parent)
{
    iter = nullptr;
}

void VarsCreator::generateVarsTree()
{
    ids.clear();
    CompositeVar* mainVar = new CompositeVar();
    mainVar->setName("Переменные");
    CompositeVar* sysVars = new CompositeVar();
    sysVars->setName("Система");
    sysVars->setDataType("-");
    CompositeVar* userVars = new CompositeVar();
    userVars->setName("Пользователь");
    userVars->setDataType("-");
    mainVar->addChild(*sysVars);
    mainVar->addChild(*userVars);

    ids.addVar(mainVar);
    ids.addVar(sysVars);
    ids.addVar(userVars);

    QDomDocument doc("variables");
    QString fName = RCompiler::getBuildDirName() + "/variables.xml";
    QFile file(fName);
    if (!file.open(QIODevice::ReadOnly)) return;
    if (!doc.setContent(&file)) {
        return;
    }

    elemByID.clear();

    QDomNodeList vars = doc.elementsByTagName("Variable");
    allData = doc.elementsByTagName("mapForDebug").at(0).childNodes();

    for(int i=0;i<allData.count();i++) {
        QDomNode n = allData.item(i);
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            if(!e.attribute("id").isEmpty()) elemByID.insert(e.attribute("id").toInt(),i);
        }
    }



    for(int i=0;i<vars.count();i++) {
        QDomNode n = vars.item(i);
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            CompositeVar *var = new CompositeVar();
            var->setName(e.attribute("name"));
            var->setMemType(e.attribute("memory"));
            bool res;
            var->setMemAddress(e.attribute("address").remove(0,2).toInt(&res,16));
            addVarToTree(e,var,userVars);
        }
    }
    createSysVars(sysVars);
}

QStringList VarsCreator::getIDList()
{
    return ids.getIDs();
}

bool VarsCreator::checkID(QString id)
{
    CompositeVar var;
    return ids.getVarByID(id,var);
}

VarItem VarsCreator::getVarByID(QString idValue)
{
    CompositeVar var;
    ids.getVarByID(idValue,var);
    return var;
}

bool VarsCreator::updateVarByID(QString idValue, VarItem &var)
{
    CompositeVar cVar;
    ids.getVarByID(idValue,cVar);
    cVar.setValue(var.getValue());
    cVar.setComment(var.getComment());
    cVar.setEditable(var.isEditable());
    cVar.setSigned(var.isSigned());
    ids.setVarByID(idValue,cVar);
    return true;
}

QString VarsCreator::getFullNameOfVar(const QString &idValue)
{
    QString fName;
    CompositeVar var;
    ids.getVarByID(idValue,var);
    fName = var.getName();
    while(1) {
        QString parID = var.getParentID();
        if(parID.isEmpty()) break;
        ids.getVarByID(parID,var);
        fName = var.getName()+"."+fName;
    }
    return fName;
}

QString VarsCreator::getPultNameOfVar(const QString &idValue)
{
    QString pultVarName;
    CompositeVar var;
    ids.getVarByID(idValue,var);
    while(1) {
        QString fName = var.getName();
        QString parID = var.getParentID();
        if(parID.isEmpty()) {
            pultVarName = fName + pultVarName;
            break;
        }
        ids.getVarByID(parID,var);

        QString parName = var.getName();
        if(parName.contains(QRegExp("^AI$"))) {
            QRegExp numExp("\\d+$");
            if(numExp.indexIn(fName) != -1) {
                int adcNum = numExp.cap().toInt();
                if((adcNum>=1)&&(adcNum<=8)) {
                    return "_Sys_ADC["+QString::number(adcNum-1)+"]";
                }
            }

        }else if(parName.contains(QRegExp("^AO$"))) {
            QRegExp numExp("\\d+$");
            if(numExp.indexIn(fName) != -1) {
                int dacNum = numExp.cap().toInt();
                if((dacNum>=1)&&(dacNum<=4)) {
                    return "_Sys_DAC["+QString::number(dacNum-1)+"]";
                }
            }
        }else if(parName.contains(QRegExp("^IN"))) {
            QRegExp numExp("\\d+$");
            if(numExp.indexIn(parName) != -1) {
                int bitNum = fName.toInt();
                int inNum = numExp.cap().toInt();
                if((inNum>=0)&&(inNum<=3)) {
                    return "(*(iostruct*)&_Sys_IN["+QString::number(inNum)+"]).bit"+QString::number(bitNum);
                }else if(inNum>=4) {
                    return "(*(iostruct*)&IN["+QString::number(inNum-4)+"]).bit"+QString::number(bitNum);
                }
            }
        }else if(parName.contains(QRegExp("^DIN"))) {
            QRegExp numExp("\\d+$");
            if(numExp.indexIn(parName) != -1) {
                int bitNum = fName.toInt();
                int dinNum = numExp.cap().toInt();
                if((dinNum>=4)&&(dinNum<=5)) {
                    return "(*(iostruct*)&_Sys_IN["+QString::number(dinNum)+"]).bit"+QString::number(bitNum);
                }
            }
        }else if(parName.contains(QRegExp("^OUT"))) {
            QRegExp numExp("\\d+$");
            if(numExp.indexIn(parName) != -1) {
                int bitNum = fName.toInt();
                int outNum = numExp.cap().toInt();
                if((outNum>=0)&&(outNum<=3)) {
                    return "(*(iostruct*)&_Sys_OUT["+QString::number(outNum)+"]).bit"+QString::number(bitNum);
                }else if(outNum>=4)
                    return "(*(iostruct*)&OUT["+QString::number(outNum-4)+"]).bit"+QString::number(bitNum);
                }
        }else if(parName.contains(QRegExp("^DOUT"))) {
            QRegExp numExp("\\d+$");
            if(numExp.indexIn(parName) != -1) {
                int bitNum = fName.toInt();
                int doutNum = numExp.cap().toInt();
                if((doutNum>=0)&&(doutNum<=3)) {
                    return "(*(iostruct*)&_Sys_OUT["+QString::number(doutNum)+"]).bit"+QString::number(bitNum);
                }
            }
        }else if(parName.contains(QRegExp("^ADC"))) {
            QRegExp numExp("\\d+$");
            if(numExp.indexIn(fName) != -1) {
                return fName;
            }
        }else if(parName.contains(QRegExp("^DAC"))) {
            QRegExp numExp("\\d+$");
            if(numExp.indexIn(fName) != -1) {
                return fName;
            }
        }else if(parName.contains(QRegExp("^char$"))) {
            QRegExp memExp("^MEM(\\d+)$");
            QRegExp eeExp("^EE(\\d+)$");
            if(memExp.indexIn(fName) != -1) {
                return "mem" + memExp.cap(1);
            }else if(eeExp.indexIn(fName) != -1) {
                return fName;
            }
        }else if(parName.contains(QRegExp("^short$"))) {
            QRegExp memExp("^MEM(\\d+)i$");
            QRegExp eeExp("^EE(\\d+)i$");
            if(memExp.indexIn(fName) != -1) {
                return "mem" + memExp.cap(1)+"i";
            }else if(eeExp.indexIn(fName) != -1) {
                return fName;
            }
        }else if(parName.contains(QRegExp("^long$"))) {
            QRegExp memExp("^MEM(\\d+)l$");
            QRegExp eeExp("^EE(\\d+)l$");
            if(memExp.indexIn(fName) != -1) {
                return "mem" + memExp.cap(1)+"l";
            }else if(eeExp.indexIn(fName) != -1) {
                return fName;
            }
        }else if(parName.contains(QRegExp("^SIT$"))) {
            QRegExp sitExp("^Proc(\\d+)$");
            if(sitExp.indexIn(fName) != -1) {
                QString sNum = sitExp.cap(1);
                return "_Sys4x_p"+sNum+".SIT";
            }
        }else if(parName.contains(QRegExp("^TIME$"))) {
            return "sysTime_"+fName;
        }

        if(var.getDataType()=="архив") {
            fName = "[" + fName + "]";
        }else if(var.getDataType()=="структура") {
            fName = "." + fName;
        }else {
            pultVarName = fName + pultVarName;
            break;
        }
        pultVarName = fName + pultVarName;
    }
    return pultVarName;
}

QString VarsCreator::getSimilarID(const QString &pultNameOfVar)
{
    QString resID="";
    QStringList varsID = getIDList();
    foreach (QString id, varsID) {
       QString curVarPultName = getPultNameOfVar(id);
       if(curVarPultName==pultNameOfVar) {
           resID = id;
           break;
       }
    }
    return resID;
}


VarsCreator::~VarsCreator()
{

}

