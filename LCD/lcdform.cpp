#include "lcdform.h"
#include "ui_lcdform.h"
#include <QGridLayout>
#include <QListWidget>
#include <QLabel>
#include "displaywidget.h"
#include "patterneditorwidget.h"
#include "strlistwidget.h"

LCDForm::LCDForm(Display &d, VarsCreator &vCr, QWidget *parent) :
    QWidget(parent),displ(d),varOwner(vCr),
    ui(new Ui::LCDForm)
{
    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout(this);
    this->setLayout(layout);

    StrListWidget* listWidget = new StrListWidget(displ);
    layout->addWidget(listWidget,1,0,1,4);
    connect(&displ,SIGNAL(strChanged(int,int)),listWidget,SLOT(strChanged(int,int)));
    connect(&displ,SIGNAL(strListChanged(int)),listWidget,SLOT(strListChanged(int)));
    connect(&displ,SIGNAL(curStrNumChanged(int,int)),listWidget,SLOT(curStrNumChanged(int,int)));

    dW = new DisplayWidget(displ);
    dW->setFixedHeight(dW->minimumHeight());
    layout->addWidget(dW,0,0,1,2);
    PatternEditorWidget* pEd = new PatternEditorWidget(displ,varOwner,this);
    pEd->setFixedHeight(dW->height()*1.2);
    connect(this,SIGNAL(newProject()),pEd,SLOT(newProject()));
    connect(this,SIGNAL(openProject()),pEd,SLOT(openProject()));
    connect(this,SIGNAL(saveProject()),pEd,SLOT(saveProject()));
    layout->addWidget(pEd,0,2,1,2);
    connect(&displ,SIGNAL(cursorPosChanged(int,int)),dW,SLOT(update()));
    connect(&displ,SIGNAL(curStrNumChanged(int,int)),dW,SLOT(update()));
    connect(&displ,SIGNAL(strChanged(int,int)),dW,SLOT(update()));
}

LCDForm::~LCDForm()
{
    delete ui;
}

void LCDForm::updFocus()
{
    dW->setFocus();
}
