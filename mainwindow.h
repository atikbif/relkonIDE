#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "codeeditor.h"
#include <QLineEdit>
#include <QThread>
#include "settingsbase.h"
#include "Debugger/debuggerform.h"
#include "LCD/display.h"
#include "VarDef/varscreator.h"
#include "LCD/lcdform.h"
#include "Help/helpbrowser.h"
#include "Search/searchdata.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    CodeEditor *editor;
    SettingsBase *settings;
    DebuggerForm *debugger;
    Display *displ;
    LCDForm* lcd;
    VarsCreator *varOwner;
    HelpBrowser *helpBr;
    QThread builderThread;

    const QString wTitle = "RelkonIDE ";
    const int maxAmountOfPrevProjects = 10;
    QString prDirPath;
    QString prFileName;

    QStringList getPrevProjects(void);
    void updatePrevProjects(const QStringList &prNames);
    int openFileByName(const QString &fName);
    void saveFileByName(const QString &fName);

    int saveWarning(void);

    bool prChangedFlag = false;
    bool noProject = true;

    QString getFileNameForPultImport(void);
    void insertVar(QDomElement &e, int strNum);
    void insertTextData(const QString &txt, int strNum, const LCDPhont &ph);
    void insertStr(QDomNodeList &views, int strNum, int subStrNum, const LCDPhont &ph);
    void createToolbar(void);
    void setEditorPhont(void);
    void createDebugger(void);
    void createDisplay(void);
    void createBuilder(void);
    void createHelp(void);
    void createUtilities(void);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void startBuild(QString prPath, QString prName);
    void updateKonFileForBuilder(QStringList str);
    void newProject(void);
    void openProject(void);
    void saveProject(void);
    void updTree(void);
    void wrSysFram(void);
    void rdSysFram(void);
    void searchRes(const QStringList &sList);

private:
    Ui::MainWindow *ui;
    QAction* undoAct;
    QAction* redoAct;
    QAction* srchAct;
    QAction* buildAct;
    QAction* toPlcAct;
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* closeProjectAct;
    QAction *importPultAct;
    QAction *editGUI;
    QAction *helpBrAct;
    QAction *openSysFramFromRelkon6;
    QAction *foldAction;
    QAction *unfoldAction;
    QAction *toTableAction;
    QAction *wrSettings;
    QAction *rdSettings;

    void disableActionWithoutProject(void);
    void enableActionWithProject(void);


private slots:
    void newFile(void);
    void openFile(void);
    void saveFile(void);
    void saveAsFile(void);
    void closeProject(void);
    void undo(void);
    void redo(void);
    void searchText(void);
    void searchCmd(const SearchData &sData);
    void goToStr(int strNum, const SearchData &sData);
    void replaceTxt(const QString &newTxt);
    void buildPr(void);
    void projectToPlc(void);
    void on_closeInfoListButton_clicked();
    void viewHelp(void);
    void viewAboutWindow(void);

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_tabWidget_currentChanged(int index);
    void openPrevProject(void);
    void prWasChanged(void);
    void buildWithoutErrors(void);

    void lcdToTable(void);
    void tableToLcd(void);
    void importPult(void);
    void editIDESettings(void);
    void startReloader(void);
    void startMMBConfig(void);
    void loadSysFramRelk6(void);
    void activateInfoPanel(void);


public slots:
    void addMessageToInfoList(const QString &message);

protected:
     void closeEvent(QCloseEvent *event);

     // QWidget interface
protected:
     void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
