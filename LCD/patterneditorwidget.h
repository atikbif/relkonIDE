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
#include <QCheckBox>
#include <QPushButton>

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
    QCheckBox* isEditable;
    QCheckBox* isSigned;
    QPushButton* applyButton;

    PultVarDefinition curDef;
    QString curVarID;
    int currentX;
    int currentY;// текущие позиции курсора

    int startPosPat; // стартовая позиция паттерна переменной при вводе прямо с пульта

    void treeBuilder(const QString &varID, QTreeWidgetItem &item);
    bool checkVar(void);
    void bitVarState(void); // состояние элементов виджета при выборе битовой переменной
    void timeVarState(void);    // состояние элементов виджета при переменной времени
    void unexistVar(PultVarDefinition &vDef); // вывод данных по ненайденной в проекте переменной
    void showEditAndSign(PultVarDefinition &vDef);  // вывод параметров редактирования и прин. знаковости
    void showVar(PultVarDefinition &vDef, const QString &comment); // имя, тип, комментарий, шаблон
    void noVar(void);
    PultVarDefinition getVar(VarItem &var); // вернуть описание переменной по установленным параметрам
    void updVar(VarItem &var);  // обновить переменную
    void createWidgets(void);
    void fillVarsTree(void);    // заполнить дерево переменных

public:
    explicit PatternEditorWidget(Display& d, VarsCreator &vCr, QWidget *parent = 0);
    void updateVarsTree(void);
    ~PatternEditorWidget();

signals:
    void updFocus(void);
public slots:
    void newProject(void);
    void saveProject(void);
    void openProject(void);
    void updTree(void);
    void cursorPosChanged(int x,int y);
    // QWidget interface
protected:
private slots:
    void doubleClickedVar(QTreeWidgetItem *item, int column);
    void applyVar(void);
    void patternUpdate(const QString &varPatternText, int startPos);
};

#endif // PATTERNEDITORWIDGET_H
