#include "lcdform.h"
#include "ui_lcdform.h"
#include <QGridLayout>
#include <QListWidget>
#include <QLabel>
#include "displaywidget.h"
#include "patterneditorwidget.h"
#include "strlistwidget.h"

LCDForm::LCDForm(Display &d, QWidget *parent) :
    QWidget(parent),displ(d),
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
    layout->addWidget(dW,0,0,1,2);
    layout->addWidget(new PatternEditorWidget(),0,2,1,2);
    connect(&displ,SIGNAL(cursorPosChanged(int,int)),dW,SLOT(update()));
    connect(&displ,SIGNAL(curStrNumChanged(int,int)),dW,SLOT(update()));
    connect(&displ,SIGNAL(strChanged(int,int)),dW,SLOT(update()));
}

LCDForm::~LCDForm()
{
    delete ui;
}
