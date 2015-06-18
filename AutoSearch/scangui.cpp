#include "scangui.h"
#include "ui_scangui.h"

ScanGUI::ScanGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScanGUI)
{
    ui->setupUi(this);
}

ScanGUI::~ScanGUI()
{
    delete ui;
}
