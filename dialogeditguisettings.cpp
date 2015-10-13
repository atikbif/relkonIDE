#include "dialogeditguisettings.h"
#include "ui_dialogeditguisettings.h"
#include <QSettings>
#include <QFontDialog>

DialogEditGUISettings::DialogEditGUISettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditGUISettings)
{
    QSettings settings;
    sysFontName = settings.value("/Settings/sysFontName","Courier").toString();
    edFontName = settings.value("/Settings/edFontName","Verdana").toString();
    sysFontSize = settings.value("Settings/sysFontSize",10).toInt();
    edFontSize = settings.value("Settings/edFontSize",10).toInt();


    ui->setupUi(this);

    ui->lineEditEdFont->setText(edFontName + " " + QString::number(edFontSize));
    ui->lineEditSysFont->setText(sysFontName + " " + QString::number(sysFontSize));
}

DialogEditGUISettings::~DialogEditGUISettings()
{
    delete ui;
}

void DialogEditGUISettings::on_pushButtonSysFont_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                    &ok, QFont(sysFontName, sysFontSize), this);
    if (ok) {
        sysFontName = font.family();
        sysFontSize = font.pointSize();
        QSettings settings;
        settings.setValue("/Settings/sysFontName",sysFontName);
        settings.setValue("Settings/sysFontSize",sysFontSize);
        ui->lineEditSysFont->setText(sysFontName + " " + QString::number(sysFontSize));
    }
}

void DialogEditGUISettings::on_pushButtonEdFont_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                    &ok, QFont(edFontName, edFontSize), this);
    if (ok) {
        edFontName = font.family();
        edFontSize = font.pointSize();
        QSettings settings;
        settings.setValue("/Settings/edFontName",edFontName);
        settings.setValue("Settings/edFontSize",edFontSize);
        ui->lineEditEdFont->setText(edFontName + " " + QString::number(edFontSize));
    }
}
