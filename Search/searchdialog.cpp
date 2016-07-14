#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QClipboard>

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
        ui->pushButtonSearch->setFocus();
    }else {
        QClipboard *clipboard = QApplication::clipboard();
        QString bufData = clipboard->text();
        if(!bufData.isEmpty()) {
            ui->comboBoxSearch->setCurrentText(bufData);
        }
        ui->comboBoxSearch->setFocus();
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
    //ui->listWidget->setCurrentRow(0);
}

void SearchDialog::on_pushButtonSearch_clicked()
{
    if(!ui->comboBoxSearch->currentText().isEmpty()) {
        hist.removeAll(ui->comboBoxSearch->currentText());
        hist.append(ui->comboBoxSearch->currentText());
        //ui->comboBoxSearch->insertItem(0,ui->comboBoxSearch->currentText());
        SearchData sData;
        sData.setRoundcondition(ui->checkBoxRound->isChecked());
        sData.setSearchText(ui->comboBoxSearch->currentText());
        sData.setReplaceText("");
        sData.setCaseSensivity(ui->checkBoxCaseSens->isChecked());
        sData.setWholeWord(ui->checkBoxWholeWord->isChecked());
        sData.setSearchRegion(ui->radioButtonForward->isChecked()?SearchData::FORWARD:SearchData::BACKWARD);
        emit startSearch(sData);

        QListWidgetItem *item = ui->listWidget->currentItem();
        if(item!=nullptr) { //on_listWidget_itemDoubleClicked(item);
            QRegExp exp("^(\\d+): ");
            if(exp.indexIn(item->text())!=-1) {
                int num = exp.cap(1).toInt();
                emit unfoldStr(num-1);
            }
        }

        //ui->listWidget->setFocus();
    }
}

void SearchDialog::on_pushButtonReplace_clicked()
{
    if(!ui->lineEditReplace->text().isEmpty()) {
        emit replace(ui->lineEditReplace->text());
        on_pushButtonSearch_clicked();
    }
    //ui->listWidget->setFocus();
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
    case Qt::Key_Escape:
        close();
        break;
    case Qt::Key_H:
        if(event->modifiers()==Qt::ControlModifier)
            on_pushButtonReplace_clicked();
        ui->listWidget->setFocus();
        break;
    case Qt::Key_F:
        if(event->modifiers()==Qt::ControlModifier)
            on_pushButtonSearch_clicked();
        //ui->listWidget->setFocus();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        if(ui->listWidget->hasFocus()) {
            QListWidgetItem *item = ui->listWidget->currentItem();
            if(item!=nullptr) on_listWidget_itemDoubleClicked(item);
        }else {on_pushButtonSearch_clicked();}
        break;
    }

}


void SearchDialog::on_pushButtonReplaceAll_clicked()
{
    if(!ui->lineEditReplace->text().isEmpty()) {
        emit replaceAll(ui->comboBoxSearch->currentText(), ui->lineEditReplace->text());
    }
}
