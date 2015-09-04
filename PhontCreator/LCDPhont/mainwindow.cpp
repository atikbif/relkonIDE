#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "symboleditor.h"
#include "symbollist.h"
#include "symboldelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SymbolEditor* s = new SymbolEditor();
    SymbolData d(10,7,0);
    s->setData(d);
    ui->horizontalLayout->addWidget(s,1);

    SymbolList *sModel = new SymbolList(this);
    ui->listView->setModel(sModel);
    SymbolDelegate *sDelegate = new SymbolDelegate(this);
    ui->listView->setItemDelegate(sDelegate);
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),s,SLOT(newSymbol(QModelIndex)));
    connect(s,SIGNAL(dataChanged(int,SymbolData*)),sModel,SLOT(updateSymbol(int,SymbolData*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
