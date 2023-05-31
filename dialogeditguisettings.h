#ifndef DIALOGEDITGUISETTINGS_H
#define DIALOGEDITGUISETTINGS_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogEditGUISettings;
}

class DialogEditGUISettings : public QDialog
{
    Q_OBJECT

    int edFontSize;
    int sysFontSize;
    QString edFontName;
    QString sysFontName;
public:
    explicit DialogEditGUISettings(QWidget *parent = 0);
    ~DialogEditGUISettings();

private slots:
    void on_pushButtonSysFont_clicked();

    void on_pushButtonEdFont_clicked();

    void on_pushButtonColors_clicked();

private:
    Ui::DialogEditGUISettings *ui;
signals:
    void font_update();
};

#endif // DIALOGEDITGUISETTINGS_H
