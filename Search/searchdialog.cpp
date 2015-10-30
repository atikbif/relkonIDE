#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>
#include <QKeyEvent>

int SearchDialog::cnt = 0;
QStringList SearchDialog::hist = QStringList();

SearchDialog::SearchDialog(QString inp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    ui->radioButtonForward->setChecked(true);
    cnt++;
    ui->listWidget->setFocus();

    QListIterator<QString> itr (hist);
    itr.toBack();
    while(itr.hasPrevious()) {
        QString current = itr.previous();
        ui->comboBoxSearch->addItem(current);
    }
    if(!inp.isEmpty()) {
        ui->comboBoxSearch->setCurrentText(inp);
    }
    ui->comboBoxSearch->setInsertPolicy(QComboBox::InsertAtTop);
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
    if(!ui->comboBoxSearch->currentText().isEmpty()) {
        hist.removeAll(ui->comboBoxSearch->currentText());
        hist.append(ui->comboBoxSearch->currentText());
        //ui->comboBoxSearch->insertItem(0,ui->comboBoxSearch->currentText());
        SearchData sData;
        sData.setSearchText(ui->comboBoxSearch->currentText());
        sData.setReplaceText("");
        sData.setCaseSensivity(ui->checkBoxCaseSens->isChecked());
        sData.setWholeWord(ui->checkBoxWholeWord->isChecked());
        sData.setSearchRegion(ui->radioButtonForward->isChecked()?SearchData::FORWARD:SearchData::BACKWARD);
        emit startSearch(sData);
        QListWidgetItem *item = ui->listWidget->currentItem();
        if(item!=nullptr) on_listWidget_itemDoubleClicked(item);
        ui->listWidget->setFocus();
    }
}

void SearchDialog::on_pushButtonReplace_clicked()
{
    if(!ui->lineEditReplace->text().isEmpty()) {
        emit replace(ui->lineEditReplace->text());
    }
    ui->listWidget->setFocus();
}

void SearchDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    SearchData sData;
    sData.setSearchText(ui->comboBoxSearch->currentText());
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
        ui->listWidget->setFocus();
        break;
    case Qt::Key_F:
        if(event->modifiers()==Qt::ControlModifier)
            on_pushButtonSearch_clicked();
        ui->listWidget->setFocus();
        break;
    case Qt::Key_Return:
        if(ui->comboBoxSearch->hasFocus()) {
            on_pushButtonSearch_clicked();
            ui->listWidget->setFocus();
        }
        QListWidgetItem *item = ui->listWidget->currentItem();
        if(item!=nullptr) on_listWidget_itemDoubleClicked(item);
        ui->listWidget->setFocus();
        break;
    }

}

