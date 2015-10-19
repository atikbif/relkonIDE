#ifndef SCANGUI_H
#define SCANGUI_H

// диалог с выводом результата поиска контроллера на разных портах

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
    QString port;
public:
    explicit ScanGUI(int progAddr=0, const QString &comPort="", QWidget *parent = 0);
    ~ScanGUI();

private:
    Ui::ScanGUI *ui;
public slots:
    void percentUpdate(float percValue,const QString& pName);
    void plcHasBeenFound(DetectedController* plc,const QString& pName);
};

#endif // SCANGUI_H
