#include "mainwindow.h"
#include <QApplication>
#include "codeeditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //CodeEditor editor;
    //editor.setWindowTitle("Relkon Editor");
    //editor.show();

    return a.exec();
}
