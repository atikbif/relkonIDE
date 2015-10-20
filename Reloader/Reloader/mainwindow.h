#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString progrPath;
    QString sframPath;
    void createCOMPortList(void);
    unsigned int codeWord = 0x5280;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonUpd_clicked();

    void on_pushButtonLoadProgr_clicked();

    void on_pushButtonLoadSFRAM_clicked();

    void on_pushButtonReadProgr_clicked();

    void on_pushButtonReadSFRAM_clicked();

signals:
    void writeToPLC(QByteArray binData);    // запрос записи данных в ПЛК
    void readFromPLC(void); // запрос чтения данных их ПЛК (результат ожидается в слоте readFromBin)

public slots:
    void readFram(const QByteArray inpData);   // чтение настроек из бинарного массива
    void readFlash(const QByteArray inpData);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
