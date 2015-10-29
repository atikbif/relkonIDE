#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QClipboard>

int SearchDialog::cnt = 0;

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    ui->radioButtonForward->setChecked(true);
    cnt++;
    ui->listWidget->setFocus();
    QClipboard *clipboard = QApplication::clipboard();
    ui->lineEditSearch->setText(clipboard->text());
}

SearchDialog::~SearchDialog()
{
    cnt--;
    delete ui;
}

void SearchDialog::getResult(const QStringList &list)
{
    QStringList edList = list;
    edList.removeDuplicates();
    ui->listWidget->clear();
    foreach (QString str, edList) {
       ui->listWidget->addItem(str);
    }
    ui->listWidget->setCurrentRow(0);
}

void SearchDialog::on_pushButtonSearch_clicked()
{
    if(!ui->lineEditSearch->text().isEmpty()) {
        SearchData sData;
        sData.setSearchText(ui->lineEditSearch->text());
        sData.setReplaceText("");
        sData.setCaseSensivity(ui->checkBoxCaseSens->isChecked());
        sData.setWholeWord(ui->checkBoxWholeWord->isChecked());
        sData.setSearchRegion(ui->radioButtonForward->isChecked()?SearchData::FORWARD:SearchData::BACKWARD);
        emit startSearch(sData);
    }
}

void SearchDialog::on_pushButtonReplace_clicked()
{
    if(!ui->lineEditReplace->text().isEmpty()) {
        emit replace(ui->lineEditReplace->text());
    }
}

void SearchDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    SearchData sData;
    sData.setSearchText(ui->lineEditSearch->text());
    sData.setReplaceText("");
    sData.setCaseSensivity(ui->checkBoxCaseSens->isChecked());
    sData.setWholeWord(ui->checkBoxWholeWord->isChecked());
    sData.setSearchRegion(ui->radioButtonForward->isChecked()?SearchData::FORWARD:SearchData::BACKWARD);
    QRegExp exp("^(\\d+): ");
    if(exp.indexIn(item->text())!=-1) {
        int num = exp.cap(1).toInt();
        emit goToStr(num-1,sData);
    }
}

void SearchDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_H:
        if(event->modifiers()==Qt::ControlModifier)
            on_pushButtonReplace_clicked();
        break;
    case Qt::Key_F:
        if(event->modifiers()==Qt::ControlModifier)
            on_pushButtonSearch_clicked();
        break;
    case Qt::Key_Return:
        QListWidgetItem *item = ui->listWidget->currentItem();
        if(item!=nullptr) on_listWidget_itemDoubleClicked(item);
        break;
    }
    ui->listWidget->setFocus();
}
