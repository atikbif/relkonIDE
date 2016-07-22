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
#include <QDockWidget>
#include "Debugger/BackCleaner/cleanmanager.h"
#include <QAbstractItemModel>

class QPrinter;

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

    QDockWidget *dockDebugger;
    QDockWidget *dockDisplay;
    QDockWidget *dockSettings;

    const QString wTitle = "RelkonIDE ";
    const int maxAmountOfPrevProjects = 10;
    QString prDirPath;
    QString prFileName;

    CleanManager cleaner;

    QStringList getPrevProjects(void);
    void updatePrevProjects(const QStringList &prNames);
    int openFileByName(const QString &fName, bool importFlag = false);
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

    QAbstractItemModel *modelFromFile(const QString& fileName);

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
    //void wrSysFram(void);
    //void rdSysFram(void);
    void searchRes(const QStringList &sList);

private:
    Ui::MainWindow *ui;
    QAction* undoAct;
    QAction* redoAct;
    QAction* srchAct;
    QAction* buildAct;
    QAction* toPlcAct;
    QAction* progrAllAct;
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* closeProjectAct;
    QAction *importPultAct;
    QAction *importPrAction;
    QAction *editGUI;
    QAction *helpBrAct;
    QAction *openSysFramFromRelkon6;
    QAction *sysMessAction;
    QAction *foldAction;
    QAction *unfoldAction;
    QAction *toTableAction;
    QAction *fromTableAction;
    QAction *wrSettings;
    QAction *rdSettings;
    QAction *noEmuAct;
    QAction *emuInpAct;
    QAction *emuAct;
    QAction *rp6Act;
    QAction *printAct;
    QAction *previewAct;



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
    void unfoldStr(int strNum);
    void replaceTxt(const QString &newTxt);
    void replaceAll(const QString &inp, const QString &out);
    void buildPr(void);
    void projectToPlc(void);
    void progrAll(void);
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
    int importPult(const QString &fName);
    void importProject(void);
    void editIDESettings(void);
    void startReloader(void);
    void startMMBConfig(void);
    void loadSysFramRelk6(void);
    int loadSysFramRelk6(const QString &fName);
    void activateInfoPanel(void);
    void toggleInfoPanel(void);

    void wrSysFramSlot(void);
    void rdSysFramSlot(void);
    void emuModeChanged(SettingsBase::emuType value);

    void emuInpActSlot(void);
    void noEmuActSlot(void);
    void emuInpOutpActSlot(void);
    void createRPFile(void);

    void toggleDebugger();
    void togglePult();
    void toggleSettings();

    void cleanBackFiles();
    void printText();
    void previewText();
    void printPreview(QPrinter *printer);
    void checkUpdates(void);


public slots:
    void addMessageToInfoList(const QString &message);

protected:
     void closeEvent(QCloseEvent *event);

     // QWidget interface
protected:
     void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
