#include "lcdform.h"
#include "ui_lcdform.h"
#include <QGridLayout>
#include <QListWidget>
#include <QLabel>
#include "displaywidget.h"
#include "patterneditorwidget.h"

LCDForm::LCDForm(QWidget *parent) :
    QWidget(parent),
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
    layout->addWidget(new DisplayWidget(),0,0,1,3);
    layout->addWidget(new PatternEditorWidget(),0,3,1,1);
}

LCDForm::~LCDForm()
{
    delete ui;
}
