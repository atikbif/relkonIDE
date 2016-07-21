#ifndef DIALOGWORDCOLORS_H
#define DIALOGWORDCOLORS_H

#include <QDialog>
#include "ColTable/colorlist.h"

namespace Ui {
class DialogWordColors;
}

class DialogWordColors : public QDialog
{
    Q_OBJECT
    ColorList cList;
public:
    explicit DialogWordColors(QWidget *parent = 0);
    ~DialogWordColors();
    void setColorList(ColorList &list);
    ColorList getColorList() const {return cList;}

private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::DialogWordColors *ui;
};

#endif // DIALOGWORDCOLORS_H
