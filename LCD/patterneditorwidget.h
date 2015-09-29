#ifndef PATTERNEDITORWIDGET_H
#define PATTERNEDITORWIDGET_H

#include <QWidget>
#include "VarDef/namesortiterator.h"
#include "VarDef/varscreator.h"
#include <QTreeWidget>
#include <QHash>
#include <QLineEdit>
#include "display.h"
#include <QString>

class PatternEditorWidget : public QWidget
{
    Q_OBJECT
    NameSortIterator* iter;
    VarsCreator& varOwner;
    Display& displ;
    QTreeWidget* tree;
    QHash<QString,QTreeWidgetItem*> idWidgetItem;   // переменные в GUI дереве

    QLineEdit* nameEdit;
    QLineEdit* typeEdit;
    QLineEdit* commentEdit;
    QLineEdit* patternEdit;

    QString curVarID;

    void treeBuilder(const QString& varID, QTreeWidgetItem &item);
    bool checkVar(void);

public:
    explicit PatternEditorWidget(Display& d, VarsCreator &vCr, QWidget *parent = 0);
    void updateVarsTree(void);
    ~PatternEditorWidget();

signals:

public slots:
    void newProject(void);
    void saveProject(void);
    void openProject(void);
    // QWidget interface
protected:
private slots:
    void doubleClickedVar(QTreeWidgetItem *item, int column);
    void applyVar(void);
};

#endif // PATTERNEDITORWIDGET_H
