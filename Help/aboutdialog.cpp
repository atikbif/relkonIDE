#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include "pathstorage.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QString relkVers="-";
    QFile file(PathStorage::getCoreVersionFileFullName());
    if(file.open(QFile::ReadOnly)) {
        QTextStream in(&file);
        relkVers = in.readAll();
        file.close();
    }

    ui->textBrowser->setOpenExternalLinks(true);
    this->setWindowTitle("О программе");
    ui->textBrowser->insertPlainText("RIDE (Relkon7) Version: "+ QCoreApplication::applicationVersion() +"\n");
    ui->textBrowser->insertPlainText("Relkon Version: " + relkVers + "\n");
    ui->textBrowser->insertHtml("<p>Авторские права: ООО \"Контэл\"   <a href='http://www.kontel.ru/'>www.kontel.ru</a></p>");

}

AboutDialog::~AboutDialog()
{
    delete ui;
}
