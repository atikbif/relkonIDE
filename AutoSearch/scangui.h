#ifndef SCANGUI_H
#define SCANGUI_H

#include <QDialog>
#include "scancontroller.h"
#include <QVector>
#include <QProgressBar>
#include <QLabel>

namespace Ui {
class ScanGUI;
}

class ScanGUI : public QDialog
{
    Q_OBJECT
    QVector<ScanController*> ports;
    QVector<QProgressBar*> prBar;
    QLabel message;
public:
    explicit ScanGUI(QWidget *parent = 0);
    ~ScanGUI();

private:
    Ui::ScanGUI *ui;
public slots:
    void percentUpdate(float percValue,const QString& pName);
    void plcHasBeenFound(DetectedController* plc,const QString& pName);
};

#endif // SCANGUI_H
