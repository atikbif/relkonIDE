#include "mainwindow.h"
#include <QApplication>
#include "codeeditor.h"
#include <QFont>
#include <QSettings>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Kontel");
    QCoreApplication::setApplicationName("Relkon 7.2");
    QSettings settings;

    QString systFontName = settings.value("/Settings/sysFontName","Verdana").toString();
    int systFontSize = settings.value("Settings/sysFontSize",10).toInt();

    QFont font(systFontName,systFontSize,QFont::Normal,false);
    //font.setFamily(font.defaultFamily());
    a.setFont(font);
    a.setApplicationVersion(APP_VERSION);

    MainWindow w;
    w.show();

    return a.exec();
}
