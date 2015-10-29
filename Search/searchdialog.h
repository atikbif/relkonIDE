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
public:
    static int getCnt(void) {return cnt;}
    explicit SearchDialog(QWidget *parent = 0);
    ~SearchDialog();
signals:
    void startSearch(const SearchData &sInfo);
    void replace(const QString &newText);
    void goToStr(int strNum, const SearchData &sInfo);
public slots:
    void getResult(const QStringList &list);
private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonReplace_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::SearchDialog *ui;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // SEARCHDIALOG_H
