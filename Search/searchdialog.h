#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "searchdata.h"
#include <QStringList>
#include <QListWidgetItem>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT
    static int cnt;
    static QStringList hist;
public:
    static int getCnt(void) {return cnt;}
    explicit SearchDialog(QString inp="",QWidget *parent = 0);
    ~SearchDialog();
signals:
    void startSearch(const SearchData &sInfo);
    void replace(const QString &newText);
    void replaceAll(const QString &inpText, const QString &outText);
    void goToStr(int strNum, const SearchData &sInfo);
public slots:
    void getResult(const QStringList &list);
private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonReplace_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);


    void on_pushButtonReplaceAll_clicked();

private:
    Ui::SearchDialog *ui;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // SEARCHDIALOG_H
