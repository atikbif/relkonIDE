#include "dialogspessymb.h"
#include "ui_dialogspessymb.h"

DialogSpesSymb::DialogSpesSymb(QWidget *parent) :
    QDialog(parent), code(-1),
    ui(new Ui::DialogSpesSymb)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_4,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_5,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_6,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_7,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_8,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_9,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_10,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_11,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_12,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_13,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_14,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
    connect(ui->pushButton_15,SIGNAL(clicked(bool)),this,SLOT(button_clicked()));
}

DialogSpesSymb::~DialogSpesSymb()
{
    delete ui;
}

void DialogSpesSymb::button_clicked()
{
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
    if(button != nullptr) {
        if(button==ui->pushButton) code = 0x2469;
        else if(button==ui->pushButton_2) code = 0x24EC;
        else if(button==ui->pushButton_3) code = 0x24EF;
        else if(button==ui->pushButton_4) code = 0x23CE;
        else if(button==ui->pushButton_5) code = 0xAB;
        else if(button==ui->pushButton_6) code = 0xBB;
        else if(button==ui->pushButton_7) code = 0x2A0D;
        else if(button==ui->pushButton_8) code = 0x2160;
        else if(button==ui->pushButton_9) code = 0x2161;
        else if(button==ui->pushButton_10) code = 0x2191;
        else if(button==ui->pushButton_11) code = 0x2193;
        else if(button==ui->pushButton_12) code = 0x260E;
        else if(button==ui->pushButton_13) code = 0xBD;
        else if(button==ui->pushButton_14) code = 0x2153;
        else if(button==ui->pushButton_15) code = 0xBC;
        close();
    }
}
