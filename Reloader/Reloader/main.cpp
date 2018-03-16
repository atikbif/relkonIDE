#include "mainwindow.h"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QString path_str;
    if(argc>=2) path_str = argv[1];
    QApplication a(argc, argv);
    MainWindow w;
    if(!path_str.isEmpty())w.setPath(path_str);
    w.show();

    return a.exec();
}
