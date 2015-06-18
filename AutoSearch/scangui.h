#ifndef SCANGUI_H
#define SCANGUI_H

#include <QDialog>

namespace Ui {
class ScanGUI;
}

class ScanGUI : public QDialog
{
    Q_OBJECT

public:
    explicit ScanGUI(QWidget *parent = 0);
    ~ScanGUI();

private:
    Ui::ScanGUI *ui;
};

#endif // SCANGUI_H
