#ifndef SCANGUI_H
#define SCANGUI_H

// диалог с выводом результата поиска контроллера на разных портах

#include <QDialog>
#include "scancontroller.h"
#include <QVector>
#include <QProgressBar>
#include <QLabel>
#include "searchcontroller.h"

namespace Ui {
class ScanGUI;
}

class ScanGUI : public QDialog
{
    Q_OBJECT
    QVector<ScanController*> ports;
    QVector<QProgressBar*> prBar;
    QLabel message;
    bool progMode;      // если необходимо найти порт PROG - true
    bool plcFound;
public:
    explicit ScanGUI(int progAddr=0, bool mode=false, const QString &portName="AUTO", QWidget *parent = 0);
    ~ScanGUI();
private:
    Ui::ScanGUI *ui;
public slots:
    void percentUpdate(float percValue,const QString& pName);
    void plcHasBeenFound(SearchController plc,const QString& pName);
};

#endif // SCANGUI_H
