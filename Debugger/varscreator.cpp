#include "varscreator.h"
#include <QThread>
#include <RCompiler/rcompiler.h>
#include <QDomDocument>
#include <QFile>

void VarsCreator::addVarToTree(const QDomElement &e, CompositeVar *var, CompositeVar *parent)
{
    if(parent == nullptr) return;
    if(e.tagName()=="FundamentalType") {
        var->setDataType(e.attribute("name"));//+" :0x" + QString::number(var->getMemAddress(),16));
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

    /*
    CompositeVar* var1 = new CompositeVar();
    CompositeVar* var2 = new CompositeVar();
    CompositeVar* var3 = new CompositeVar();
    var1->setName("a");var1->setDataType("unsigned int");
    var2->setName("b");var2->setDataType("float");
    var3->setName("c");var3->setDataType("char");
    var1->setMemType("RAM");var1->setMemAddress(0);
    var2->setMemType("RAM");var2->setMemAddress(4);
    var3->setMemType("RAM");var3->setMemAddress(8);
    userVars->addChild(*var1);
    userVars->addChild(*var2);
    userVars->addChild(*var3);
    mainVar->addChild(*sysVars);
    mainVar->addChild(*userVars);

    ids.addVar(mainVar);
    ids.addVar(sysVars);
    ids.addVar(userVars);
    ids.addVar(var1);
    ids.addVar(var2);
    ids.addVar(var3);

    CompositeVar* inoutVars = new CompositeVar();
    inoutVars->setName("входы_выходы");
    ids.addVar(inoutVars);
    sysVars->addChild(*inoutVars);
    CompositeVar* in0 = new CompositeVar();
    in0->setName("IN0");
    ids.addVar(in0);
    CompositeVar* in1 = new CompositeVar();
    in1->setName("IN1");
    ids.addVar(in1);
    inoutVars->addChild(*in1);
    inoutVars->addChild(*in0);
    for(int i=0;i<8;i++) {
        CompositeVar* ptr1 = new CompositeVar();
        ptr1->setName("bit"+QString::number(i));
        ptr1->setDataType("bit");
        ptr1->setMemType("io");ptr1->setMemAddress(0);ptr1->setBitNum(i);
        in0->addChild(*ptr1);
        ids.addVar(ptr1);
        CompositeVar* ptr2 = new CompositeVar();
        ptr2->setName("bit"+QString::number(i));
        ptr2->setDataType("bit");
        ptr2->setMemType("io");ptr2->setMemAddress(1);ptr2->setBitNum(i);
        in1->addChild(*ptr2);
        ids.addVar(ptr2);
    }
    CompositeVar* out0 = new CompositeVar();
    out0->setName("OUT0");ids.addVar(out0);inoutVars->addChild(*out0);
    CompositeVar* out1 = new CompositeVar();
    out1->setName("OUT1");ids.addVar(out1);inoutVars->addChild(*out1);
    CompositeVar* out2 = new CompositeVar();
    out2->setName("OUT2");ids.addVar(out2);inoutVars->addChild(*out2);



    for(int i=0;i<8;i++) {
        CompositeVar* ptr1 = new CompositeVar();
        ptr1->setName("bit"+QString::number(i));
        ptr1->setDataType("bit");
        ptr1->setMemType("io");ptr1->setMemAddress(2);ptr1->setBitNum(i);
        out0->addChild(*ptr1);ids.addVar(ptr1);
        CompositeVar* ptr2 = new CompositeVar();
        ptr2->setName("bit"+QString::number(i));
        ptr2->setDataType("bit");
        ptr2->setMemType("io");ptr2->setMemAddress(3);ptr2->setBitNum(i);
        out1->addChild(*ptr2);ids.addVar(ptr2);
        CompositeVar* ptr3 = new CompositeVar();
        ptr3->setName("bit"+QString::number(i));
        ptr3->setDataType("bit");
        ptr3->setMemType("io");ptr3->setMemAddress(4);ptr3->setBitNum(i);
        out2->addChild(*ptr3);ids.addVar(ptr3);


    }*/
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
    if(ids.getVarByID(idValue,cVar)){
        cVar.setValue(var.getValue());
        return true;
    }
    return false;
}


VarsCreator::~VarsCreator()
{

}

