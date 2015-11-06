#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int modAddr;
    void listUpdate(int modAddr);
    bool testAddress(int addr) const;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonComUpd_clicked();

    void on_pushButtonSearch_clicked();

    void on_pushButtonWrite_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
