#include "lcdform.h"
#include "ui_lcdform.h"
#include <QGridLayout>
#include <QListWidget>
#include <QLabel>
#include "displaywidget.h"
#include "patterneditorwidget.h"

LCDForm::LCDForm(Display &d, QWidget *parent) :
    QWidget(parent),displ(d),
    ui(new Ui::LCDForm)
{
    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout(this);
    this->setLayout(layout);
    QListWidget* l1 = new QListWidget();
    QListWidget* l2 = new QListWidget();
    QListWidget* l3 = new QListWidget();
    QListWidget* l4 = new QListWidget();
    layout->addWidget(l1,1,0,1,1);
    layout->addWidget(l2,1,1,1,1);
    layout->addWidget(l3,1,2,1,1);
    layout->addWidget(l4,1,3,1,1);
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
