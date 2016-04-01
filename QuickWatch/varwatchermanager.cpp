#include "varwatchermanager.h"
#include <QVBoxLayout>


VarWatcherManager::VarWatcherManager(QWidget *parent) : QWidget(parent)
{
    watcher = new VarWatcher();
    watcher->moveToThread(&watchThread);
    connect(&watchThread,SIGNAL(finished()),watcher,SLOT(deleteLater()));
    connect(this,SIGNAL(startProcess()),watcher,SLOT(updateProcess()));
    watchThread.start();

    setWindowTitle("быстрый просмотр");
    table = new QTableWidget(1,2);
    table->setHorizontalHeaderLabels(QStringList() << "имя" << "значение");
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(table);
    setLayout(layout);

    setWindowFlags(Qt::WindowStaysOnTopHint);
    emit startProcess();
}

VarWatcherManager::~VarWatcherManager()
{
    watcher->finishProcess();
    watchThread.quit();
    watchThread.wait();
}

void VarWatcherManager::setActive(bool value)
{
    if(value) {
        connect(watcher,SIGNAL(quickInfoRequest()),this,SIGNAL(quickInfoRequest()));
    }else {
        disconnect(watcher,SIGNAL(quickInfoRequest()),this,SIGNAL(quickInfoRequest()));
    }
}

void VarWatcherManager::quickInfo(QStringList names, QStringList values)
{
    //table->clear();
    //table->setHorizontalHeaderLabels(QStringList() << "имя" << "значение");
    table->setDisabled(true);
    table->setRowCount(names.count());
    for(int i=0;i<names.count();i++) {
        QTableWidgetItem *itemName = new QTableWidgetItem(names.at(i));
        //itemName->setFlags(Qt::NoItemFlags);
        QTableWidgetItem *itemValue = new QTableWidgetItem(values.at(i));
        //itemValue->setFlags(Qt::NoItemFlags);
        table->setItem(i,0,itemName);
        table->setItem(i,1,itemValue);
    }
    table->sortItems(0);
    table->resizeColumnsToContents();
    table->setEnabled(true);
}

void VarWatcherManager::closeEvent(QCloseEvent *)
{
    emit closeWatch();
}
