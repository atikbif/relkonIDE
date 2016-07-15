#ifndef LCDFORM_H
#define LCDFORM_H

#include <QWidget>
#include "displaywidget.h"
#include "display.h"
#include "VarDef/varscreator.h"
#include "strlistwidget.h"

namespace Ui {
class LCDForm;
}

class LCDForm : public QWidget
{
    Q_OBJECT
    DisplayWidget* dW;
    Display& displ;
    VarsCreator& varOwner;
    StrListWidget* listWidget;

    void createEmptyStrings(QDomDocument &doc);
    void insertSymbol(QDomElement &e, int strNum);
    void insertVar(QDomElement &e, int strNum);
    void printStr(QDomNode &n, int strNum);

public:
    explicit LCDForm(Display& d,VarsCreator& vCr, QWidget *parent = 0);
    const LCDPhont& getPhont(void) const {return dW->getPhont();}
    ~LCDForm();

private:
    Ui::LCDForm *ui;
signals:
    void newProject(void);
    void openProject(void);
    void saveProject(void);
    void updTree(void);
public slots:
    void updFocus(void);
private slots:
    void saveLCD(void);
    void openLCD(void);
    void newLCD(void);
};

#endif // LCDFORM_H
