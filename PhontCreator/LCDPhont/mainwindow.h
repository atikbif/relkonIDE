#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "symbollist.h"
#include "symboleditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    SymbolList *sModel;
    SymbolEditor* sEditor;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void newFile(void);
    void openFile(void);
    void saveFile(void);
};

#endif // MAINWINDOW_H
