#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "symboleditor.h"
#include "symboldelegate.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sEditor = new SymbolEditor();
    SymbolData d(0);
    sEditor->setData(d);
    ui->horizontalLayout->addWidget(sEditor,1);

    sModel = new SymbolList(this);
    ui->listView->setModel(sModel);
    SymbolDelegate *sDelegate = new SymbolDelegate(this);
    ui->listView->setItemDelegate(sDelegate);
    ui->actionNew->setIcon(QIcon("://new_32.ico"));
    ui->actionOpen->setIcon(QIcon("://open_32.ico"));
    ui->actionSave->setIcon(QIcon("://save_32.ico"));
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),sEditor,SLOT(newSymbol(QModelIndex)));
    connect(sEditor,SIGNAL(dataChanged(int,SymbolData*)),sModel,SLOT(updateSymbol(int,SymbolData*)));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFile()));
    ui->mainToolBar->addAction(ui->actionNew);
    ui->mainToolBar->addAction(ui->actionOpen);
    ui->mainToolBar->addAction(ui->actionSave);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    for(int i=0;i<256;i++) {
        SymbolData* s = new SymbolData(i);
        sModel->updateSymbol(i,s);
    }
    sEditor->newSymbol(sModel->index(0));
    ui->listView->setCurrentIndex(sModel->index(0));
}

void MainWindow::openFile()
{
    QString fName = QFileDialog::getOpenFileName(this, tr("Open File"),
                               "lcd_phont.rph",
                               tr("LCD phonts (*.rph)"));
    if(!fName.isEmpty()) {
        QFile file(fName);
        if (!file.open(QIODevice::ReadOnly))
            return;
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_4);
        int height = 0;
        int width = 0;
        int cnt = 0;
        in >> height;
        in >> width;
        in >> cnt;
        if((height==SymbolData::getHeight())&&(width==SymbolData::getWidth())) {
            for(int i=0;i<cnt;i++) {
                int code=0;
                QList<QBitArray> data;
                in >> code;
                in >> data;

                SymbolData* s = new SymbolData(code);
                s->setData(data);
                sModel->updateSymbol(code,s);
            }
        }
        sEditor->newSymbol(sModel->index(0));
        ui->listView->setCurrentIndex(sModel->index(0));
        file.close();
    }
}

void MainWindow::saveFile()
{
    QString fName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "lcd_phont.rph",
                               tr("LCD phonts (*.rph)"));
    if(!fName.isEmpty()) {
        QFile file(fName);
        if (!file.open(QIODevice::WriteOnly))
            return;
            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_5_4);
            out << SymbolData::getHeight();
            out << SymbolData::getWidth();
            out << sModel->rowCount();
            for(int i=0;i<sModel->rowCount();i++) {
                QModelIndex idx = sModel->index(i);
                QVariant v = sModel->data(idx);
                SymbolData* ptr = (SymbolData*)(v.value<void*>());
                out << ptr->getCode();
                out << ptr->getData();
            }
            file.close();
    }
}
