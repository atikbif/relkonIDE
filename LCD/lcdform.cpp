#include "lcdform.h"
#include "ui_lcdform.h"
#include <QGridLayout>
#include <QListWidget>
#include <QLabel>
#include "displaywidget.h"
#include "patterneditorwidget.h"
#include "strlistwidget.h"
#include <QFile>
#include "RCompiler/rcompiler.h"
#include <QXmlStreamWriter>
#include <QDesktopWidget>
#include "pathstorage.h"

void LCDForm::createEmptyStrings(QDomDocument &doc)
{
    QDomNodeList subStrCounts = doc.elementsByTagName("SubstringsCount");
    for(int i=0;i<subStrCounts.count();i++) {
        QDomNode n = subStrCounts.item(i);
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            QString num = e.attribute("num");
            QString count = e.attribute("count");
            bool res = false;
            int numValue = num.toInt(&res);
            if(res) {
                int countValue = count.toInt(&res);
                if(res) {
                    if((numValue>=0)&&(numValue<displ.getStrCount())) {
                        if(countValue>0) {
                            while(displ.getSubStrCount(numValue)<countValue) {
                                displ.addEmptyStrBefore(numValue,0);
                            }
                        }
                    }
                }
            }
        }
    }
}

void LCDForm::insertSymbol(QDomElement &e, int strNum)
{
    QString num = e.attribute("num");
    QString symbData = e.attribute("data");
    int pos = num.toInt();
    int code = symbData.toInt();
    displ.setCursor(pos,strNum);
    displ.insertSymbol(code);
}

void LCDForm::insertVar(QDomElement &e, int strNum)
{
    QString pos = e.attribute("pos");
    QString vName = e.attribute("name");
    QString pattern = e.attribute("pattern");
    QString comment = e.attribute("comment");
    QString isEd = e.attribute("edit");
    QString isSign = e.attribute("sign");
    int posValue = pos.toInt();

    QString vID = varOwner.getSimilarID(vName);

    VarItem var = varOwner.getVarByID(vID);
    PultVarDefinition vp;

    if(!vID.isEmpty()) {
        var.setComment(comment);
        varOwner.updateVarByID(vID,var);
        vp.setDataType(var.getDataType());
        if(var.getBitNum()!=-1) {
            isEd="0";
            isSign="0";
        }
        vp.setExist(true);
    }else {
        vp.setDataType("неизвестен");
        vp.setExist(false);
    }

    vp.setId(vID);
    vp.setPattern(pattern);
    vp.setName(vName);
    vp.setEditable(isEd=="1"?true:false);
    vp.setForceSign(isSign=="1"?true:false);

    QRegExp eeExp("^EE(\\d+)");
    if(eeExp.indexIn(var.getName()) != -1) {
        int num = eeExp.cap(1).toInt();
        vp.setEEVar(true);
        vp.setEEposInSettingsTable(num);
    }else {
        vp.setEEVar(false);
    }

    displ.setCursor(posValue,strNum);
    for(int i=0;i<vp.getPattern().length();i++) {
        displ.deleteSymbol();
    }
    displ.addVar(vp);
}

void LCDForm::printStr(QDomNode &n, int strNum)
{
    QDomNodeList children = n.childNodes();
    for(int chNum=0;chNum<children.count();chNum++) {
       QDomNode child = children.item(chNum);
       QDomElement ce = child.toElement();
       if(!ce.isNull()) {
           if(ce.nodeName()=="symbol") {
               insertSymbol(ce,strNum);
           }else if(ce.nodeName()=="var") {
               insertVar(ce,strNum);
           }
       }
    }
}

LCDForm::LCDForm(Display &d, VarsCreator &vCr, QWidget *parent) :
    QWidget(parent),displ(d),varOwner(vCr),
    ui(new Ui::LCDForm)
{
    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout(this);
    this->setLayout(layout);

    StrListWidget* listWidget = new StrListWidget(displ);
    layout->addWidget(listWidget,1,0,1,8);
    connect(&displ,SIGNAL(strChanged(int,int)),listWidget,SLOT(strChanged(int,int)));
    connect(&displ,SIGNAL(strListChanged(int)),listWidget,SLOT(strListChanged(int)));
    connect(&displ,SIGNAL(curStrNumChanged(int,int)),listWidget,SLOT(curStrNumChanged(int,int)));
    connect(listWidget,SIGNAL(updFocus()),this,SLOT(updFocus()));

    dW = new DisplayWidget(displ);
    QDesktopWidget desk;
    int height = desk.availableGeometry().height()*0.15;



    //dW->setMinimumHeight(height);
    dW->setFixedHeight(height);
    dW->setFixedWidth(height*3);

    layout->addWidget(dW,0,0,1,8);
    PatternEditorWidget* pEd = new PatternEditorWidget(displ,varOwner,this);
    pEd->setFixedWidth((float)height*1.5);
    connect(this,SIGNAL(newProject()),pEd,SLOT(newProject()));
    connect(this,SIGNAL(openProject()),pEd,SLOT(openProject()));
    connect(this,SIGNAL(saveProject()),pEd,SLOT(saveProject()));
    connect(this,SIGNAL(updTree()),pEd,SLOT(updTree()));
    connect(pEd,SIGNAL(updFocus()),this,SLOT(updFocus()));
    connect(&displ,SIGNAL(cursorPosChanged(int,int)),pEd,SLOT(cursorPosChanged(int,int)));
    layout->addWidget(pEd,0,8,2,1);
    connect(&displ,SIGNAL(cursorPosChanged(int,int)),dW,SLOT(update()));
    connect(&displ,SIGNAL(curStrNumChanged(int,int)),dW,SLOT(update()));
    connect(&displ,SIGNAL(strChanged(int,int)),dW,SLOT(update()));

    connect(this,SIGNAL(newProject()),this,SLOT(newLCD()));
    connect(this,SIGNAL(openProject()),this,SLOT(openLCD()));
    connect(this,SIGNAL(saveProject()),this,SLOT(saveLCD()));
}

LCDForm::~LCDForm()
{
    delete ui;
    delete dW;
}

void LCDForm::updFocus()
{
    dW->setFocus();
}

void LCDForm::saveLCD()
{
    QString fName = PathStorage::getKonFileFullName();
    fName.remove(QRegExp("\\.kon$"));
    fName+=".lcd";
    QFile file(fName);
    if(file.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Display");

        for(int i=0;i<displ.getStrCount();i++) {
            xmlWriter.writeStartElement("SubstringsCount");
            xmlWriter.writeAttribute("num",QString::number(i));
            xmlWriter.writeAttribute("count",QString::number(displ.getSubStrCount(i)));
            xmlWriter.writeEndElement();
        }

        for(int i=0;i<displ.getStrCount();i++) {
            for(int j=0;j<displ.getSubStrCount(i);j++) {
                xmlWriter.writeStartElement("string");
                xmlWriter.writeAttribute("num",QString::number(i));
                xmlWriter.writeAttribute("substring",QString::number(j));

                DisplayStr str = displ.getString(i,j);
                xmlWriter.writeAttribute("active",(str.isActive())?"1":"0");
                for(int n=0;n<str.getLength();n++) {
                    xmlWriter.writeStartElement("symbol");
                    xmlWriter.writeAttribute("num",QString::number(n));
                    xmlWriter.writeAttribute("data",QString::number(str.getSymbol(n)));
                    xmlWriter.writeEndElement();
                }
                for(int n=0;n<str.getVarsCount();n++) {
                    PultVarDefinition vp;
                    str.getVar(n,vp);
                    xmlWriter.writeStartElement("var");
                    xmlWriter.writeAttribute("pos",QString::number(vp.getPosInStr()));
                    xmlWriter.writeAttribute("name",vp.getName());
                    xmlWriter.writeAttribute("pattern",vp.getPattern());
                    VarItem var = varOwner.getVarByID(vp.getId());
                    xmlWriter.writeAttribute("comment",var.getComment());
                    xmlWriter.writeAttribute("sign",vp.getForceSign()?"1":"0");
                    xmlWriter.writeAttribute("edit",vp.isEditable()?"1":"0");
                    xmlWriter.writeEndElement();
                }

                xmlWriter.writeEndElement();
            }
        }
        xmlWriter.writeEndElement();
        file.close();
        displ.setChanged(false);
    }
}

void LCDForm::openLCD()
{
    displ.clearDisplay();
    QDomDocument doc("lcd");
    QString fName = PathStorage::getKonFileFullName();
    fName.remove(QRegExp("\\.kon$"));
    fName+=".lcd";
    QFile file(fName);
    if (!file.open(QIODevice::ReadOnly)) return;
    if (!doc.setContent(&file)) {
        return;
    }

    createEmptyStrings(doc);

    QDomNodeList strings = doc.elementsByTagName("string");
    for(int i=0;i<strings.count();i++) {
        QDomNode n = strings.item(i);
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            QString strNum = e.attribute("num");
            QString subStrNum = e.attribute("substring");
            QString act = e.attribute("active");
            int strNumValue = strNum.toInt();
            int subStrNumValue = subStrNum.toInt();
            bool isActive = (act.toInt()!=0)?true:false;
            if((strNumValue>=0)&&(strNumValue<displ.getStrCount())) {
                if((subStrNumValue>=0)&&(subStrNumValue<displ.getSubStrCount(strNumValue))) {
                    bool actFl = displ.getString(strNumValue,subStrNumValue).isActive();
                    if(actFl!=isActive) displ.toggleActive(strNumValue,subStrNumValue);
                    displ.goToStr(strNumValue,subStrNumValue);
                    printStr(n,strNumValue);
                }
            }
        }
    }
    for(int i=0;i<displ.getStrCount();i++) {
        displ.goToStr(i,0);
    }
    displ.setCursor(0,0);
    displ.setChanged(false);
}

void LCDForm::newLCD()
{
    displ.clearDisplay();
    displ.setChanged(false);
}
