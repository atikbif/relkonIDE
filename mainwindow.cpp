#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"

#include <QLabel>
#include <QFileDialog>
#include <QTextStream>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QSpacerItem>
#include <QDateTime>
#include <QComboBox>
#include <QSettings>
#include <QFileInfo>
#include <QMessageBox>

#include "prbuilder.h"
#include "settingsform.h"
#include "AutoSearch/scangui.h"
#include "Loader/bootmodesetter.h"
#include "Loader/ymodemthread.h"
#include "AutoSearch/detectedcontroller.h"
#include <QSerialPort>
#include "RCompiler/rcompiler.h"

#include "Debugger/debuggerform.h"
#include <QFontDialog>
#include "dialogeditguisettings.h"
#include "Help/aboutdialog.h"
#include <QProcess>
#include "Search/searchdialog.h"



QStringList MainWindow::getPrevProjects()
{
    QStringList res;
    QSettings settings;//("Kontel","RIDE");
    res = settings.value("/Settings/PrevProjects",QStringList()).toStringList();
    res.removeDuplicates();
    if(res.count()>maxAmountOfPrevProjects) res = res.mid(0,maxAmountOfPrevProjects);
    settings.setValue("/Settings/PrevProjects",res);
    return res;
}

void MainWindow::updatePrevProjects(const QStringList &prNames)
{
    QSettings settings;//("Kontel","RIDE");
    settings.setValue("/Settings/PrevProjects",prNames);
    QStringList resList = getPrevProjects();
    ui->menuFile->clear();

    ui->menuFile->addAction(newAct);
    ui->menuFile->addAction(openAct);
    ui->menuFile->addAction(saveAct);
    ui->menuFile->addAction(saveAsAct);
    QMenu *impMenu = ui->menuFile->addMenu("Import");
    impMenu->addAction(importPultAct);
    impMenu->addAction(openSysFramFromRelkon6);
    QMenu* recPr = new QMenu("Недавние проекты");
    ui->menuFile->addMenu(recPr);
    foreach(QString name, resList) {
        //ui->menu->addAction(name,this,SLOT(openPrevProject()));
        recPr->addAction(name,this,SLOT(openPrevProject()));
    }
}

int MainWindow::openFileByName(const QString &fName)
{
    activateInfoPanel();
    addMessageToInfoList(QDateTime::currentDateTime().time().toString() + " :Открытие файла " + fName);

    QFile file(fName);
    if (file.open(QIODevice::ReadOnly)) {

        QFileInfo fInfo(fName);
        prDirPath = fInfo.absolutePath();
        prFileName = fInfo.fileName();

        QStringList prevPr = getPrevProjects();
        prevPr.insert(0,fName);
        updatePrevProjects(prevPr);

        editor->clear();
        QTextStream in(&file);
        in.setCodec("Windows-1251");
        editor->setDisabled(true);
        editor->appendPlainText(in.readAll());
        editor->setEnabled(true);
        editor->foldAll();

        QTextCursor tmpCursor = editor->textCursor();
        tmpCursor.setVisualNavigation(true);
        tmpCursor.setPosition(editor->document()->firstBlock().position());
        editor->setTextCursor(tmpCursor);
        file.close();
        addMessageToInfoList(QDateTime::currentDateTime().time().toString() + " :Файл успешно открыт");
        setWindowTitle(wTitle + " - " + fName);
        RCompiler::setInpDirName(fInfo.dir().path());
        RCompiler::setInpKonFileName(fInfo.fileName());
        if(settings!=nullptr) {
            settings->clearSettings();
            settings->setKonFileName(fName);
            settings->openSettings();
        }
        editor->document()->clearUndoRedoStacks();

        repaint();
        varOwner->generateVarsTree();
        emit openProject();

        //QThread::msleep(500);
        on_closeInfoListButton_clicked();

        return 1;
    }
    addMessageToInfoList(QDateTime::currentDateTime().time().toString() + " :error - Ошибка открытия файла");
    return 0;
}

void MainWindow::saveFileByName(const QString &fName)
{
    QFile file(fName);
    if (file.open(QIODevice::WriteOnly)) {

        QFileInfo fInfo(fName);
        prDirPath = fInfo.absolutePath();
        prFileName = fInfo.fileName();

        QStringList prevPr = getPrevProjects();
        prevPr.insert(0,fName);
        updatePrevProjects(prevPr);

        QTextStream out(&file);
        out.setCodec("Windows-1251");
        for(int i=0;i<editor->blockCount();i++) {
            out << editor->document()->findBlockByNumber(i).text();
            out << "\r\n";
        }
        file.close();
        setWindowTitle(wTitle + " - " + fName);
        RCompiler::setInpDirName(fInfo.dir().path());
        RCompiler::setInpKonFileName(fInfo.fileName());
        prChangedFlag = false;
        if(settings!=nullptr) {
            settings->setKonFileName(fName);
            settings->saveSettings();
        }
        emit saveProject();
    }
}

void MainWindow::activateInfoPanel()
{
    //ui->listWidget->clear();
    ui->listWidget->setVisible(true);
    ui->closeInfoListButton->setVisible(true);
    ui->horizontalSpacer->changeSize(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->infoLabel->setVisible(true);
}

int MainWindow::saveWarning()
{
    if(prChangedFlag || displ->getChanged()) {
        QMessageBox msgBox(this);
        msgBox.setText("Проект был изменён");
        msgBox.setInformativeText("Вы хотите сохранить изменения?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
              saveFile();
              break;
          case QMessageBox::Discard:
              // Don't Save was clicked
              break;
          case QMessageBox::Cancel:
              return 0;
          default:
              // should never be reached
              break;
        }
    }
    return 1;
}

QString MainWindow::getFileNameForPultImport()
{
    QStringList prevProjects = getPrevProjects();
    QString path = "/";
    if(prevProjects.count()) {
        if(QFile::exists(prevProjects.at(0))) {
            QFileInfo fInfo(prevProjects.at(0));
            path = fInfo.absolutePath();
        }
    }
    QString fName = QFileDialog::getOpenFileName(this, tr("Импорт пульта"),
                                                    path,
                                                    tr("Relkon 6.x Pult (*.plt )"));
    return fName;
}

void MainWindow::insertVar(QDomElement &e, int strNum)
{
    if(!e.isNull()) {
        QString varName = e.attribute("Name");
        QString varSign = e.attribute("HasSign");
        QString varReadOnly = e.attribute("ReadOnly");
        QString varPos = e.attribute("Position");
        QString varPattern = e.attribute("Mask");
        if(!varName.isEmpty()) {
            PultVarDefinition vDef;
            varPattern.replace(',','.');
            vDef.setEditable(varReadOnly=="true"?false:true);
            vDef.setPattern(varPattern);
            vDef.setPosInStr(varPos.toInt());
            vDef.setForceSign(varSign=="true"?true:false);
            displ->setCursor(varPos.toInt(),strNum);

            if(varName=="DATE") varName="sysTime_date";
            if(varName=="MONTH") varName="sysTime_month";
            if(varName=="YEAR") varName="sysTime_year";
            if(varName=="HOUR") varName="sysTime_hour";
            if(varName=="MIN") varName="sysTime_min";
            if(varName=="SEC") varName="sysTime_sec";

            QRegExp eeExp("^EE(\\d+)");
            if(eeExp.indexIn(varName) != -1) {
                int num = eeExp.cap(1).toInt();
                vDef.setEEVar(true);
                vDef.setEEposInSettingsTable(num);
            }else {
                vDef.setEEVar(false);
            }

            vDef.setName(varName);

            displ->addVar(vDef);
        }
    }
}

void MainWindow::insertTextData(const QString &txt, int strNum, const LCDPhont &ph)
{
    displ->setCursor(0,strNum);
    for(int k=0;k<displ->getLength();k++) {

        if(k<txt.length()) {
            int unicodeValue = txt.at(k).unicode();
            displ->insertSymbol(ph.getSymbCodeinPhont(unicodeValue));
        }
    }
}

void MainWindow::insertStr(QDomNodeList &views, int strNum, int subStrNum, const LCDPhont &ph)
{
    displ->addEmptyStrAfter(strNum,displ->getSubStrCount(strNum)-1);
    QDomNode vn = views.item(subStrNum);
    QDomElement ve = vn.toElement();
    if(!ve.isNull()) {
        QString strText = ve.attribute("Text");
        QString enFlag = ve.attribute("Enabled");
        if((!strText.isEmpty())&&(!enFlag.isEmpty())) {
            insertTextData(strText,strNum,ph);
        }
        if(enFlag=="false") displ->toggleActive(strNum,subStrNum);
        QDomNodeList varsParent = vn.childNodes();
        if(varsParent.count()==1) {
            QDomNode vp = varsParent.item(0);
            QDomNodeList vars = vp.childNodes();

            if(vars.count()) {
                displ->setReplaceMode(true);
                for(int y=0;y<vars.count();y++) {
                    QDomNode varNode = vars.item(y);
                    QDomElement varElement = varNode.toElement();
                    insertVar(varElement,strNum);
                }
                displ->setReplaceMode(false);
            }
        }
    }
}

void MainWindow::createToolbar()
{
    newAct = new QAction(QIcon("://new_32.ico"), "Новый проект", this);
    openAct = new QAction(QIcon("://open_32.ico"), "Открыть", this);
    importPultAct = new QAction(QIcon("://import_pult.ico"), "Загрузить пульт версии 6.x",this);
    saveAct = new QAction(QIcon("://save_32.ico"), "Сохранить", this);
    saveAsAct = new QAction(QIcon("://save_32.ico"), "Сохранить как", this);
    undoAct = new QAction(QIcon("://undo_32.ico"), "Отменить операцию", this);
    redoAct = new QAction(QIcon("://redo_32.ico"), "Повторить отменённую операцию", this);
    srchAct = new QAction(QIcon("://srch_32.ico"), "Искать текст", this);
    buildAct = new QAction(QIcon("://build_32.ico"), "Собрать проект F5", this);
    toPlcAct = new QAction(QIcon("://toPLC_32.ico"), "Загрузить проект в контроллер F7", this);
    editGUI = new QAction(QIcon("://config.ico"), "Настройки среды", this);

    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));
    connect(srchAct, SIGNAL(triggered()), this, SLOT(searchText()));
    connect(buildAct, SIGNAL(triggered()), this, SLOT(buildPr()));
    connect(toPlcAct, SIGNAL(triggered()), this, SLOT(projectToPlc()));
    connect(saveAsAct,SIGNAL(triggered()), this, SLOT(saveAsFile()));
    connect(importPultAct,SIGNAL(triggered()), this, SLOT(importPult()));
    connect(editGUI,SIGNAL(triggered()),this,SLOT(editIDESettings()));

    ui->mainToolBar->addAction(newAct);
    ui->mainToolBar->addAction(openAct);
    ui->mainToolBar->addAction(saveAct);
    ui->mainToolBar->addAction(undoAct);
    ui->mainToolBar->addAction(redoAct);
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->mainToolBar->addAction(srchAct);

    QAction *toTableAction = new QAction(QIcon("://table.ico"), "пульт > настройки", this);
    //QAction *fromTableAction = new QAction(QIcon("://display.ico"), "настройки > пульт", this);

    //ui->menuCmd->addAction(fromTableAction);
    connect(toTableAction,SIGNAL(triggered()),this,SLOT(lcdToTable()));
    //connect(fromTableAction,SIGNAL(triggered()),this,SLOT(tableToLcd()));
    ui->menuCmd->addAction(buildAct);
    ui->menuCmd->addAction(toPlcAct);
    QAction *wrSettings = new QAction(QIcon("://writeData.png"),"Записать настройки F8",this);
    QAction *rdSettings = new QAction(QIcon("://readData.png"),"Прочитать настройки F9",this);
    connect(wrSettings,SIGNAL(triggered(bool)),this,SIGNAL(wrSysFram()));
    connect(rdSettings,SIGNAL(triggered(bool)),this,SIGNAL(rdSysFram()));
    ui->menuCmd->addAction(wrSettings);
    ui->menuCmd->addAction(rdSettings);
    ui->menuCmd->addAction(toTableAction);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(buildAct);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(toPlcAct);
    ui->mainToolBar->addWidget(spacer);
}

void MainWindow::setEditorPhont()
{
    QSettings sysSettings;
    QString edFontName = sysSettings.value("/Settings/edFontName","Courier").toString();
    int edFontSize = sysSettings.value("Settings/edFontSize",10).toInt();

    QFont font(edFontName,edFontSize,QFont::Normal,false);
    const int tabWidth = 4;  // 4 characters
    QFontMetrics metrics(font);
    editor->setTabStopWidth(tabWidth * metrics.width(' '));
    editor->setFont(font);
}

void MainWindow::createDebugger()
{
    debugger = new DebuggerForm(*varOwner);
    connect(this,SIGNAL(openProject()),debugger,SLOT(openProject()));
    connect(this,SIGNAL(newProject()),debugger,SLOT(newProject()));
    connect(this,SIGNAL(saveProject()),debugger,SLOT(saveProject()));
    connect(this,SIGNAL(updTree()),debugger,SLOT(updTree()));
    ui->tabWidget->addTab(debugger,"Отладчик");
}

void MainWindow::createDisplay()
{
    displ = new Display();
    lcd = new LCDForm(*displ,*varOwner);
    connect(this,SIGNAL(newProject()),lcd,SIGNAL(newProject()));
    connect(this,SIGNAL(openProject()),lcd,SIGNAL(openProject()));
    connect(this,SIGNAL(saveProject()),lcd,SIGNAL(saveProject()));
    connect(this,SIGNAL(updTree()),lcd,SIGNAL(updTree()));
    ui->tabWidget->addTab(lcd,"Пульт");
}

void MainWindow::createBuilder()
{
    PrBuilder *buildProc = new PrBuilder(*displ);
    buildProc->moveToThread(&builderThread);
    connect(&builderThread, SIGNAL(finished()), buildProc, SLOT(deleteLater()));
    connect(this, SIGNAL(startBuild(QString,QString)), buildProc, SLOT(buildRequest(QString,QString)));
    connect(this,SIGNAL(updateKonFileForBuilder(QStringList)), buildProc, SLOT(setFileText(QStringList)));
    connect(buildProc, SIGNAL(printMessage(QString)), this, SLOT(addMessageToInfoList(QString)));
    connect(buildProc, SIGNAL(buildIsOk()),this,SLOT(buildWithoutErrors()));
    builderThread.start();
}

void MainWindow::createHelp()
{
    helpBrAct = new QAction(QIcon("://help.ico"), "Меню", this);
    ui->menuHelp->addAction(helpBrAct);
    QAction *aboutAction = new QAction(QIcon("://about.ico"), "О программе", this);
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(viewAboutWindow()));
    ui->menuHelp->addAction(aboutAction);

    helpBr = new HelpBrowser(QApplication::applicationDirPath()+"/Doc","index.html");
    connect(helpBrAct,SIGNAL(triggered()),this,SLOT(viewHelp()));
}

void MainWindow::createUtilities()
{
    QAction *actR = new QAction(QIcon("://reloader.ico"), "Загрузчик", this);
    ui->menuUtil->addAction(actR);
    connect(actR,SIGNAL(triggered()),this,SLOT(startReloader()));
    QAction *actMMB = new QAction(QIcon("://mmb.ico"), "Настройка Matchbox", this);
    ui->menuUtil->addAction(actMMB);
    connect(actMMB,SIGNAL(triggered()),this,SLOT(startMMBConfig()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->setVisible(false);
    ui->closeInfoListButton->setVisible(false);
    ui->infoLabel->setVisible(false);
    ui->horizontalSpacer->changeSize(0,0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    setWindowTitle(wTitle + " - несохранённый проект");
    prDirPath="";
    prFileName="";

    editor = new CodeEditor(this);
    Highlighter* highlighter = new Highlighter(editor->document());
    Q_UNUSED(highlighter);
    setEditorPhont();

    createToolbar();

    openSysFramFromRelkon6 = new QAction(QIcon("://database.ico"), "Загрузить зав. установки из Relkon 6.x", this);
    connect(openSysFramFromRelkon6,SIGNAL(triggered(bool)),this,SLOT(loadSysFramRelk6()));

    QAction *foldAction = new QAction(QIcon("://contract.ico"),"свернуть всё",this);
    connect(foldAction,SIGNAL(triggered(bool)),editor,SLOT(foldAll()));
    QAction *unfoldAction = new QAction(QIcon("://expand.ico"),"развернуть всё",this);
    connect(unfoldAction,SIGNAL(triggered(bool)),editor,SLOT(unfoldAll()));
    ui->menuEdit->addAction(srchAct);
    ui->menuEdit->addAction(foldAction);
    ui->menuEdit->addAction(unfoldAction);
    QAction *sysMessAction = new QAction(QIcon("://info.ico"),"Системные сообщения", this);
    connect(sysMessAction,SIGNAL(triggered(bool)),this,SLOT(activateInfoPanel()));
    ui->menuEdit->addAction(sysMessAction);
    ui->menuEdit->addAction(editGUI);

    QStringList prNames = getPrevProjects();
    if(prNames.count()) {
        updatePrevProjects(prNames);
    }

    ui->tabWidget->clear();
    ui->tabWidget->tabBar()->setFont(QFont("Courier",12,QFont::Normal,false));
    ui->tabWidget->addTab(editor,"Редактор");
    editor->setFocus();


    varOwner = new VarsCreator();
    settings = new SettingsForm();
    connect(this,SIGNAL(wrSysFram()),settings,SLOT(writeSysFram()));
    connect(this,SIGNAL(rdSysFram()),settings,SLOT(readSysFram()));
    ui->tabWidget->addTab(settings,"Настройки");

    createDebugger();

    createDisplay();

    /*ui->mdiArea->addSubWindow(editor);
    ui->mdiArea->addSubWindow(debugger);
    ui->mdiArea->addSubWindow(settings);
    ui->mdiArea->tileSubWindows();//setViewMode(QMdiArea::TabbedView);
    */

    setWindowState(Qt::WindowMaximized);
    createBuilder();
    createHelp();
    createUtilities();
    newFile();
    //QThread::msleep(1000);
    prChangedFlag = false;
    connect(editor,SIGNAL(textChanged()),this,SLOT(prWasChanged()));
}

MainWindow::~MainWindow()
{
    builderThread.quit();
    builderThread.wait();
    delete ui;
    delete displ;
    delete varOwner;
    delete helpBr;
}

void MainWindow::newFile()
{
    if(saveWarning()==0) return;

    addMessageToInfoList(QDateTime::currentDateTime().time().toString() + " :Новый проект");

    editor->clear();
    editor->appendPlainText("#DATA //-----Присвоение переменных программы.");
    editor->appendPlainText("    ");
    editor->appendPlainText("#INIT //-----Инициализация данных.");
    editor->appendPlainText("    ");
    editor->appendPlainText("#STARTp0;");
    editor->appendPlainText("    ");
    editor->appendPlainText("//-----Начало программы.");
    editor->appendPlainText("#PROCESS 0");
    editor->appendPlainText("#SIT1(0.1)");
    editor->appendPlainText("    ");
    editor->appendPlainText("#/R;");

    // - путь по умолчанию
    QDir dir(QApplication::applicationDirPath()+"/newProject");
    dir.removeRecursively();

    if(!dir.exists()) {
        dir.mkdir(".");
    }
    saveFileByName(dir.absolutePath()+"/project.kon");
    //

    prChangedFlag = false;
    if(settings!=nullptr) {
        //settings->setKonFileName("");
        settings->clearSettings();
    }
    editor->document()->clearUndoRedoStacks();
    varOwner->generateVarsTree();
    emit newProject();

    //RCompiler::setInpDirName("");
    //RCompiler::setInpKonFileName("");


}

void MainWindow::openFile()
{
    if(saveWarning()==0) return;

    QStringList prevProjects = getPrevProjects();
    QString path = "/";
    if(prevProjects.count()) {
        if(QFile::exists(prevProjects.at(0))) {
            QFileInfo fInfo(prevProjects.at(0));
            path = fInfo.absolutePath();
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    path,
                                                    tr("Relkon Files (*.kon )"));
    if(fileName.isEmpty()) return;
    openFileByName(fileName);
    //QThread::msleep(1000);
    prChangedFlag = false;
    //editor->document()->clearUndoRedoStacks();
}

void MainWindow::saveFile()
{
    QStringList prevProjects = getPrevProjects();
    QString path = "/";
    if(prevProjects.count()) {
        if(QFile::exists(prevProjects.at(0))) {
            QFileInfo fInfo(prevProjects.at(0));
            path = fInfo.absolutePath();
        }
    }
    QString fileName;
    if(prFileName.isEmpty())
    fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    path,
                                                    tr("Relkon Files (*.kon )"));
    else {
        fileName = RCompiler::getKonFileName();

        QFile file(fileName);
        QFileInfo fInfo(file);
        QDir dir(fInfo.dir().path()+ "/back");
        if(!dir.exists()) {
            dir.mkdir(".");
        }
        QString backName = QDateTime::currentDateTime().toString();
        backName.replace(QRegExp("[\\s\\t\\.:]"),"_");
        backName=fInfo.dir().path() + "/back/" +backName+".kon";
        QFile::copy(fileName,backName);
    }
    saveFileByName(fileName);
}

void MainWindow::saveAsFile()
{
    QStringList prevProjects = getPrevProjects();
    QString path = "/";
    if(prevProjects.count()) {
        if(QFile::exists(prevProjects.at(0))) {
            QFileInfo fInfo(prevProjects.at(0));
            path = fInfo.absolutePath();
        }
    }
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    path,
                                                    tr("Relkon Files (*.kon )"));
    saveFileByName(fileName);
}

void MainWindow::undo()
{
    editor->undo();
}

void MainWindow::redo()
{
    editor->redo();
}

void MainWindow::searchText()
{
    if(SearchDialog::getCnt()==0) {
        SearchDialog *dialog = new SearchDialog(editor->getSelectedText(),this);
        connect(dialog,SIGNAL(finished(int)),dialog,SLOT(deleteLater()));
        connect(dialog,SIGNAL(startSearch(SearchData)),this,SLOT(searchCmd(SearchData)));
        connect(this,SIGNAL(searchRes(QStringList)),dialog,SLOT(getResult(QStringList)));
        connect(dialog,SIGNAL(goToStr(int,SearchData)),this,SLOT(goToStr(int,SearchData)));
        connect(dialog,SIGNAL(replace(QString)),this,SLOT(replaceTxt(QString)));
        dialog->show();
    }
}

void MainWindow::searchCmd(const SearchData &sData)
{
    QStringList sList;
    QTextDocument::FindFlags flags;
    if(sData.getCaseSensivity()) flags |= QTextDocument::FindCaseSensitively;
    if(sData.getWholeWord()) flags |= QTextDocument::FindWholeWords;
    if(sData.getSearchRegion()==SearchData::BACKWARD) flags |= QTextDocument::FindBackward;

    QTextCursor highlightCursor = editor->textCursor();
    highlightCursor = editor->document()->find(sData.getSearchText() , highlightCursor, flags);
    while(!highlightCursor.isNull()) {
        int blNum = highlightCursor.blockNumber();
        QString strText = editor->document()->findBlockByNumber(blNum).text();
        if(sData.getWholeWord()) {
            QString exprStr = strText;
            QString searchText = sData.getSearchText();
            if(!sData.getCaseSensivity()) {
                exprStr = exprStr.toLower();
                searchText = searchText.toLower();
            }
            QRegExp exp("\\b"+ searchText + "\\b");
            if(exp.indexIn(exprStr)==-1) strText="";
        }
        if(!strText.isEmpty()) {
            strText = QString::number(blNum+1) + ": " + strText;
            sList << strText;
        }
        highlightCursor = editor->document()->find(sData.getSearchText(), highlightCursor, flags);
    }
    emit searchRes(sList);
}

void MainWindow::goToStr(int strNum, const SearchData &sData)
{
    QTextBlock bl = editor->document()->findBlockByNumber(strNum);
    QTextBlock block = bl;
    if(!block.isVisible()) {
        while(!block.isVisible()) {
            block = block.previous();
            if(block.isValid()) {
                if(block.isVisible()) {
                    editor->toggleFolding(block);
                    break;
                }
            }
        }
    }
    QTextCursor highlightCursor(bl);
    editor->setTextCursor(highlightCursor);
    QTextDocument::FindFlags flags;
    if(sData.getCaseSensivity()) flags |= QTextDocument::FindCaseSensitively;
    if(sData.getWholeWord()) flags |= QTextDocument::FindWholeWords;
    highlightCursor = editor->document()->find(sData.getSearchText(), highlightCursor, flags);
    if (!highlightCursor.isNull()) {
        int blNum = highlightCursor.blockNumber();
        if(blNum==strNum) {
            QTextCursor startPosCursor = highlightCursor;
            highlightCursor.movePosition(QTextCursor::WordRight,
                                QTextCursor::KeepAnchor);
            editor->setTextCursor(startPosCursor);
        }
    }

}

void MainWindow::replaceTxt(const QString &newTxt)
{
    QTextCursor curs = editor->textCursor();
    if(!curs.selectedText().isEmpty()) {
        curs.insertText(newTxt);
    }
}

void MainWindow::buildPr()
{
    saveFile();
    ui->listWidget->clear();
    activateInfoPanel();

    if(ui->listWidget->isVisible()) {
        QStringList conFile;
        for(int i=0;i<editor->blockCount();i++) {
            conFile << editor->document()->findBlockByNumber(i).text() + " ";
        }
        emit updateKonFileForBuilder(conFile);
        emit startBuild(prDirPath,prFileName);
    }
}

void MainWindow::projectToPlc()
{
    if(QFile::exists(RCompiler::getBinFileName())) {
        ScanGUI gui(settings->getProgAddr(),this);
        int ret = gui.exec();
        if(ret==QDialog::Accepted) {
            BootModeSetter bootSetter(this);
            if(bootSetter.setBootMode()) {
                DetectedController* plc = &DetectedController::Instance();
                YmodemThread loader(plc->getUartName(),this);
                loader.exec();
            }
        }
    }else QMessageBox::warning(this,"Загрузка","Ошибка открытия файла "+RCompiler::getBinFileName());
}

void MainWindow::addMessageToInfoList(const QString &message)
{
    ui->listWidget->addItem(message);
    if(message.contains("error")) {
        ui->listWidget->item(ui->listWidget->count()-1)->setTextColor(Qt::darkRed);
        ui->listWidget->item(ui->listWidget->count()-1)->setFont (QFont ("Courier", 10,QFont::DemiBold));
    }else if(message.contains("warning")||message.contains("note")) {
        ui->listWidget->item(ui->listWidget->count()-1)->setTextColor(QColor(139,69,19));
        ui->listWidget->item(ui->listWidget->count()-1)->setFont (QFont ("Courier", 10,QFont::Normal));
    }else {
        ui->listWidget->item(ui->listWidget->count()-1)->setTextColor(QColor(0,50,0));
        ui->listWidget->item(ui->listWidget->count()-1)->setFont (QFont ("Courier", 10,QFont::Normal));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(saveWarning()==0) event->ignore();
    else event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_F:
        if (QApplication::keyboardModifiers() && Qt::ControlModifier) searchText();
        break;
    case Qt::Key_F5:
        if(buildAct->isEnabled()) {
            buildPr();
        }
        break;
    case Qt::Key_F7:
        if(toPlcAct->isEnabled()) {
            projectToPlc();
        }
        break;
    case Qt::Key_F8:
        emit wrSysFram();
        break;
    case Qt::Key_F9:
        emit rdSysFram();
        break;
    }

}

void MainWindow::on_closeInfoListButton_clicked()
{
    ui->listWidget->setVisible(false);
    ui->closeInfoListButton->setVisible(false);
    ui->infoLabel->setVisible(false);
    ui->horizontalSpacer->changeSize(0,0, QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void MainWindow::viewHelp()
{
    helpBr->show();
    helpBr->goHome();
}

void MainWindow::viewAboutWindow()
{
    AboutDialog dialog;
    dialog.exec();
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QString str = index.data().toString();
    QRegExp pattern("строка:(\\d+)");
    if(pattern.indexIn(str)!=-1) {
        int strNum = pattern.cap(1).toInt();
        if((strNum>0)&&(strNum<=editor->blockCount())) {
            QTextBlock block = editor->document()->findBlockByNumber(strNum-1);
            QTextCursor cursor(block);
            if(!block.isVisible()) {
                while(!block.isVisible()) {
                    block = block.previous();
                    if(block.isValid()) {
                        if(block.isVisible()) {
                            editor->toggleFolding(block);
                            break;
                        }
                    }
                }
            }
            editor->setTextCursor(cursor);
        }
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index!=0) {
        undoAct->setEnabled(false);
        redoAct->setEnabled(false);
        srchAct->setEnabled(false);
        //buildAct->setEnabled(false);
        if(index==2) {
            debugger->tabChanged();
        }
        if(index==3) {
            lcd->updFocus();
            buildAct->setEnabled(true);
        }
    }else {
        undoAct->setEnabled(true);
        redoAct->setEnabled(true);
        srchAct->setEnabled(true);
        buildAct->setEnabled(true);
    }
}

void MainWindow::openPrevProject()
{
    QAction *a = qobject_cast<QAction *>(sender());
    if(a!=nullptr) {
        QString fName = a->text();
        if(saveWarning()==0) return;
        openFileByName(fName);
        //QThread::msleep(1000);
        prChangedFlag = false;
    }
}

void MainWindow::prWasChanged()
{
    prChangedFlag = true;
}

void MainWindow::buildWithoutErrors()
{
    varOwner->generateVarsTree();

    emit updTree();
    displ->updateDefinitions(*varOwner);
    displ->cursorPosChanged(displ->getXPosition(),displ->getYPosition());
    //QThread::msleep(1000);
    on_closeInfoListButton_clicked();
}

void MainWindow::lcdToTable()
{

    const int startSettingsAddress = 0x7B00;
    const int stopSettingsEndAddress = 0x7EFF;

    QVector<PultVarDefinition> vars;
    displ->getVars(vars);

    if(vars.count()>0) {
        for(int i=0;i<vars.count();i++) {
            QString vID = vars.at(i).getId();
            QString vP = vars.at(i).getPattern();
            VarItem var = varOwner->getVarByID(vID);
            QString memType = var.getMemType();
            if(memType==MemStorage::framMemName) {
                int byteCount = var.getByteCount();
                if(byteCount) {
                    vP.remove(".");
                    vP.remove(",");
                    qulonglong value = (qulonglong)vP.toLongLong();
                    int addr = var.getMemAddress();
                    for(int j=0;j<byteCount;j++) {
                        quint8 vByte = value & 0xFF;
                        value = value >> 8;
                        if((addr>=startSettingsAddress)&&(addr<=stopSettingsEndAddress)) {
                            settings->updateOnyByte(addr-startSettingsAddress,vByte);
                        }
                        addr++;
                    }
                }
            }
        }
        settings->updateTable();
    }
}

void MainWindow::tableToLcd()
{

}

void MainWindow::importPult()
{
    QString fName = getFileNameForPultImport();
    if(!fName.isEmpty()) {
        QDomDocument doc("pult");
        QFile file(fName);
        if (!file.open(QIODevice::ReadOnly)) return;
        if (!doc.setContent(&file)) {
            return;
        }
        QDomNodeList rows = doc.elementsByTagName("Views");
        if(rows.count()==4) {
            displ->clearDisplay();
            LCDPhont ph = lcd->getPhont();
            for(int i=0;i<rows.count();i++) {
                QDomNode n = rows.item(i);
                if(!n.toElement().isNull()) {
                    QDomNodeList views = n.childNodes();
                    for(int j=0;j<views.count();j++) {
                        insertStr(views,i,j,ph);
                    }
                }
                displ->deleteStr(i,0);
            }
            displ->setCursor(0,0);
        }else {
            QMessageBox::warning(this,"Импортирование пульта","Некорректный формат файла.\n");
        }
    }
}

void MainWindow::editIDESettings()
{
    DialogEditGUISettings dialog;
    dialog.exec();
}

void MainWindow::startReloader()
{

    QString path = QApplication::applicationDirPath() + "/Reloader.exe";
    if(QFile::exists(path)) {
        QProcess* loader = new QProcess;
        connect(loader, SIGNAL(finished(int)), loader, SLOT(deleteLater()));
        loader->start(path);
    }else {
        activateInfoPanel();
        addMessageToInfoList("error: Ошибка открытия файла " + path);
    }

}

void MainWindow::startMMBConfig()
{
    QString path = QApplication::applicationDirPath() + "/mmbSettings.exe";
    if(QFile::exists(path)) {
        QProcess* mmb = new QProcess;
        connect(mmb, SIGNAL(finished(int)), mmb, SLOT(deleteLater()));
        mmb->start(path);
    }else {
        activateInfoPanel();
        addMessageToInfoList("error: Ошибка открытия файла " + path);
    }
}

void MainWindow::loadSysFramRelk6()
{
    QStringList prevProjects = getPrevProjects();
    QString path = "/";
    if(prevProjects.count()) {
        if(QFile::exists(prevProjects.at(0))) {
            QFileInfo fInfo(prevProjects.at(0));
            path = fInfo.absolutePath();
        }
    }
    QString fName = QFileDialog::getOpenFileName(this, tr("Импорт зав. установок"),
                                                    path,
                                                    tr("Relkon 6.x project (*.rp6 )"));
    if(!fName.isEmpty()) {
        QDomDocument doc;
        QFile file(fName);
        if(file.open(QIODevice::ReadOnly)) {

            if(doc.setContent(&file)) {
                bool updFlag = false;
                QDomNodeList vars = doc.elementsByTagName("ControllerVar");
                for(int i=0;i<vars.count();i++) {
                    QDomNode n = vars.item(i);
                    QDomElement e = n.toElement();
                    if(!e.isNull()) {
                        QString name = e.attribute("Name");
                        QString value = e.attribute("Value");
                        QRegExp exp("^EE(\\d+)$");
                        if(exp.indexIn(name)!=-1) {
                            int num = exp.cap(1).toInt();
                            unsigned char ucValue = value.toUInt();
                            if(num<SettingsBase::getCount()) {
                                settings->updateOnyByte(num,ucValue);
                                updFlag = true;
                            }
                        }
                    }
                }
                if(updFlag) settings->updateTable();
                else QMessageBox::information(this,"Сообщение","Не найдено данных для обновления");
            }
            file.close();
        }else QMessageBox::information(this,"Ошибка","Не удалось открыть файл");
    }
}
