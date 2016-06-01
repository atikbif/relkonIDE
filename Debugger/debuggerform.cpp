#include "debuggerform.h"
#include "ui_debuggerform.h"

#include "VarDef/namesortiterator.h"
#include <QMenu>
#include <QStringList>
#include <QLineEdit>
#include "vartomemconnector.h"
#include "varbytesvalueconverter.h"
#include "VarDef/varparser.h"
#include "RCompiler/rcompiler.h"
#include <QDateTime>
#include <QSerialPortInfo>
#include "AutoSearch/scangui.h"
#include <QMessageBox>
#include "debuggersettings.h"
#include <QDomDocument>
#include "dialogwritevar.h"

#include <QGridLayout>
#include <QTimer>
#include <QSlider>
#include <QProcess>
#include <QTextCodec>

#include <QFileDialog>
#include <QFileInfo>
#include <QDataStream>
#include "aninpslider.h"
#include "pathstorage.h"

#include "matchboxexistance.h"


void DebuggerForm::saveView()
{
    QDir dir(PathStorage::getBuildDir());
    if(!dir.exists()) dir.mkdir(".");
    QFile file(PathStorage::getDebugFileFullName());
    if(file.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Debugger");
        // сохранение переменных из дерева просмотра
        xmlWriter.writeStartElement("VarView");
        QList<QTreeWidgetItem*> actItems = idActiveWidgetItem.values();
        for(int i=0;i<actItems.count();i++) {
            QString curId = idActiveWidgetItem.key(actItems.at(i));
            QString curFullName = actItems.at(i)->toolTip(0);
                xmlWriter.writeStartElement("var");
                xmlWriter.writeAttribute("id",curId);
                xmlWriter.writeAttribute("name",curFullName);
                QString commentText="";
                QWidget* widget =  ui->treeWidgetWatch->itemWidget(actItems.at(i),5);
                QLineEdit* tEdit = dynamic_cast<QLineEdit*>(widget);
                if(tEdit!=nullptr) commentText = tEdit->text();
                xmlWriter.writeAttribute("comment",commentText);
                xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        // сохранение комментариев к закладке входов/выходов
        xmlWriter.writeStartElement("IOView");
        foreach (QString ioName, ioComments.keys()) {
           xmlWriter.writeStartElement("io");

           xmlWriter.writeAttribute("name",ioName);
           QString comment;
           QLineEdit* ptr = ioComments.value(ioName);
           if(ptr) {comment = ptr->text();}
           xmlWriter.writeAttribute("comment",comment);
           xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
        // состояние групп входов/выходов (свёрнуты-развёрнуты)
        foreach (QGroupBox *box, ioBoxes) {
            QString ioGrName = box->title();
            xmlWriter.writeStartElement("ioGrState");
            xmlWriter.writeAttribute("name",ioGrName);
            QString st = (box->isChecked())?"unfolded":"folded";
            xmlWriter.writeAttribute("state",st);
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement();
        file.close();
    }
}

void DebuggerForm::openView()
{
    idActiveWidgetItem.clear();
    ui->treeWidgetWatch->clear();
    scheduler.clear();

    QDomDocument doc("debug");
    QString fName = PathStorage::getDebugFileFullName();
    QFile file(fName);
    if (!file.open(QIODevice::ReadOnly)) return;
    if (!doc.setContent(&file)) {
        return;
    }
    // построение списка соответствий полного имени переменной в дереви и её идентификатора
    QHash<QString,QString> fullNames;
    foreach (QTreeWidgetItem* item, idWidgetItem.values()) {
       QString fName = item->toolTip(0);
       fullNames.insert(fName,idWidgetItem.key(item));
    }

    // поиск описания переменных для вывода в дереве просмотра
    QDomNodeList vars = doc.elementsByTagName("var");
    for(int i=0;i<vars.count();i++) {
        QDomNode n = vars.item(i);
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            QString fullName = e.attribute("name");
            QString newId = fullNames.value(fullName);
            // проверка на наличие в текущем проекте переменной с указанным именем
            if(!newId.isEmpty()) {
                VarItem var = varOwner.getVarByID(newId);
                QStringList sList;
                QString varName;

                QStringList fNameList = fullName.split('.');
                // Удаление из имени 2-х первых узлов (Переменные.(пользватель/система))
                fNameList.removeFirst();fNameList.removeFirst();
                foreach (QString s, fNameList) {
                  varName += "." + s;
                }
                varName.remove(0,1);// удаление стартовой "."

                QRegExp exp(".*\\.\\d+.*");
                if(exp.indexIn(varName)==-1) {
                    QStringList names = varName.split(".");
                    varName = names.last();
                }

                // список полей для отображения в дереве просмотра
                sList << varName << "" << "" << "0x"+QString::number(var.getMemAddress(),16).toUpper() << var.getDataType();
                QTreeWidgetItem* newItem = new QTreeWidgetItem(sList);
                idActiveWidgetItem.insert(newId,newItem);
                var.setPriority(1);
                newItem->setToolTip(0,fullName);
                ui->treeWidgetWatch->addTopLevelItem(newItem);
                ui->treeWidgetWatch->setItemWidget(newItem,5,new QLineEdit(e.attribute("comment"),ui->treeWidgetWatch));
                scheduler.addReadOperation(var);    // добавить переменную к заданию планировщика
            }
        }
    }
    scheduler.schedule();   // составить новый список запросов планировщика

    // разбор комментариев к вкладке входов/выходов
    QDomNodeList ios = doc.elementsByTagName("io");
    for(int i=0;i<ios.count();i++) {
        QDomNode n = ios.item(i);
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            QString name = e.attribute("name");
            QString comment = e.attribute("comment");
            if(ioComments.contains(name)) {
                QLineEdit *ptr = ioComments.value(name);
                if(ptr) {
                    ptr->setText(comment);
                }
            }
        }
    }

    // разбор свёрнутости групп входов/выходов
    QDomNodeList ioGrSt= doc.elementsByTagName("ioGrState");
    ioCheck.clear();
    for(int i=0;i<ioGrSt.count();i++) {
        QDomNode n = ioGrSt.item(i);
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            QString name = e.attribute("name");
            QString st = e.attribute("state");
            ioCheck.insert(name,st=="unfolded"?true:false);
        }
    }
}

void DebuggerForm::clearView()
{
    idActiveWidgetItem.clear();
    ui->treeWidgetWatch->clear();
    scheduler.clear();
    foreach (QLineEdit* ptr, ioComments.values()) {
       ptr->setText("");
    }
    ioCheck.clear();
    ioCheck.insert("IN0",true);
    ioCheck.insert("IN1",true);
    ioCheck.insert("IN2",true);
    ioCheck.insert("IN3",true);
    ioCheck.insert("OUT0",true);
    ioCheck.insert("OUT1",true);
    ioCheck.insert("OUT2",true);
    ioCheck.insert("OUT3",true);
    ioCheck.insert("ADC1",true);
    ioCheck.insert("ADC2",true);
    ioCheck.insert("ADC3",true);
    ioCheck.insert("ADC4",true);
    ioCheck.insert("ADC5",true);
    ioCheck.insert("ADC6",true);
    ioCheck.insert("ADC7",true);
    ioCheck.insert("ADC8",true);
}

void DebuggerForm::tabChanged()
{
    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}

void DebuggerForm::setNetAddress(int value)
{
    ui->spinBoxNetAddress->setValue(value);
}

void DebuggerForm::closeQuickWatch()
{
    ui->checkBoxQuickWatch->setChecked(false);
}

void DebuggerForm::stopDebugger()
{
    on_stopButton_clicked();
}

void DebuggerForm::newPLCType(const QString &value)
{
    plcType = value;
}

void DebuggerForm::clearMemViewTable()
{
    disconnect(ui->tableWidgetMem,SIGNAL(cellChanged(int,int)),this,SLOT(memViewCellPressed(int,int)));
    for(int r=0;r<memViewRowCount;r++) {
        for(int c=0;c<memViewColumnCount;c++) {
            ui->tableWidgetMem->setItem(r,c,new QTableWidgetItem("   "));
        }
    }
    ui->tableWidgetMem->resizeColumnsToContents();
    connect(ui->tableWidgetMem,SIGNAL(cellChanged(int,int)),this,SLOT(memViewCellPressed(int,int)));
}

void DebuggerForm::updateMemViewRequests()
{
    scheduler.clear();
    QString startAddr = ui->lineEditMemStartAddr->text();
    startAddr = startAddr.toLower();
    startAddr.remove("0x");
    bool convRes = false;
    int addr = startAddr.toInt(&convRes,16);
    clearMemViewTable();
    if(convRes) {
        int maxAddr = addr + memViewColumnCount*memViewRowCount;
        QString memType;
        if(memView->getMemType()==MemViewDescription::FRAM) {
            memType = MemStorage::framMemName;
            if(!memView->checkAddress(maxAddr)) maxAddr = MemStorage::framMemSize;
        }
        if(memView->getMemType()==MemViewDescription::RAM) {
            memType = MemStorage::ramMemName;
            if(!memView->checkAddress(maxAddr)) maxAddr = MemStorage::ramMemSize;
        }
        for(int i=addr;i<maxAddr;i++) {
            VarItem var;
            var.setDataType(VarItem::ucharType);
            var.setMemType(memType);
            var.setPriority(1);
            var.setMemAddress(i);
            scheduler.addReadOperation(var);
            memStor.connectCellToID(memType,i,var.getID());
        }
    }
    if(ui->checkBoxQuickWatch->isChecked()) {
        foreach (QString id, idActiveWidgetItem.keys()) {
            VarItem var = varOwner.getVarByID(id);
            var.setPriority(1);
            scheduler.addReadOperation(var);
        }
    }
    scheduler.schedule();
}

void DebuggerForm::createTree()
{
    ui->treeWidgetMain->clear();
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidgetMain);

    if(varOwner.getIDList().count()) {
        iter->goToID(varOwner.getIDList().at(0));
        if(iter->topFirst()) {
            item->setText(0,varOwner.getVarByID(iter->currentID()).getName());
            treeBuilder(iter->currentID(),*item);
        }
    }

    QString style = "QTreeWidget::item:!selected "
       "{ border: 1px solid gainsboro; border-left: none; border-top: none; }";

    ui->treeWidgetMain->setStyleSheet(style);
    ui->treeWidgetWatch->setStyleSheet(style);

    ui->treeWidgetMain->setItemExpanded(item,true);
    ui->treeWidgetMain->header()->resizeSections(QHeaderView::ResizeToContents);

}

void DebuggerForm::treeBuilder(const QString &varID, QTreeWidgetItem &item)
{
    iter->goToID(varID);
    if(iter->isNode()) {
        if(iter->down()){
            for(int i=0;i<iter->getItemCount();i++) {
                QString curPos = iter->currentID();
                QString name = varOwner.getVarByID(curPos).getName();
                if(name!="TIME") {
                    QTreeWidgetItem* curItem = new QTreeWidgetItem(&item);
                    curItem->setText(0,name);
                    curItem->setText(1,varOwner.getVarByID(curPos).getDataType());
                    if(item.toolTip(0).isEmpty())
                    curItem->setToolTip(0,item.text(0)+"."+curItem->text(0));
                    else curItem->setToolTip(0,item.toolTip(0)+"."+curItem->text(0));
                    if(iter->isNode()) {
                        treeBuilder(curPos,*curItem);
                        iter->goToID(curPos);
                    }
                    else idWidgetItem.insert(curPos,curItem);
                }
                iter->next();
            }
        }
    }
}

DebuggerForm::DebuggerForm(VarsCreator &vCr, QWidget *parent) :
    QWidget(parent), varOwner(vCr), lastOpenInpFile(""),
    ui(new Ui::DebuggerForm)
{
    plcType = "PC365C";
    scan = nullptr;
    iter = nullptr;
    ui->setupUi(this);

    memView = new MemViewDescription(memViewRowCount,memViewColumnCount);
    memView->setMemType(MemViewDescription::FRAM);

    ui->tabWidget->tabBar()->setFont(QFont("Courier",12,QFont::Normal,false));
    iter = new NameSortIterator(varOwner.getIDStorage());
    ui->treeWidgetWatch->sortByColumn(0, Qt::AscendingOrder);
    connect(&memStor,SIGNAL(updateMemory(QStringList)),this,SLOT(updateMemory(QStringList)));
    scan = new ScanManager(&memStor,this);
    connect(scan,SIGNAL(updateAnswerCnt(int,bool)),this,SLOT(updateCorrErrAnswerCount(int,bool)));
    connect(scan,SIGNAL(addMessage(QString)),this,SLOT(getMessageFromDebugProcess(QString)));
    connect(scan,SIGNAL(updateTimeStr(QString)),this,SLOT(getTimeStr(QString)));
    ui->lcdNumberCorrect->setDigitCount(8);
    ui->lcdNumberError->setDigitCount(8);
    updateComPortList();
    ui->treeWidgetWatch->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->comboBoxSpeed->setCurrentText("115200");
    connect(ui->pushButtonOpenInp,SIGNAL(clicked(bool)),this,SLOT(openInputs()));
    connect(ui->pushButtonSaveInp,SIGNAL(clicked(bool)),this,SLOT(saveInputs()));

    buildIO();
    ui->lineEditTime->setInputMask("99:99:99    99.99.99");
    ui->lineEditTime->setText("00:00:00 01.01.00");

    ui->tableWidgetMem->setRowCount(memViewRowCount);
    ui->tableWidgetMem->setColumnCount(memViewColumnCount);
    clearMemViewTable();
    on_checkBoxLog_clicked();
    on_tabWidget_currentChanged(1);
    quick = new VarWatcherManager();
    connect(quick,SIGNAL(quickInfoRequest()),this,SLOT(getQuickWatchInfo()));
    connect(this,SIGNAL(quickInfo(QStringList,QStringList)),quick,SLOT(quickInfo(QStringList,QStringList)));
    connect(quick,SIGNAL(closeWatch()),this,SLOT(closeQuickWatchWindow()));
}

DebuggerForm::~DebuggerForm()
{
    delete ui;
    delete iter;
    delete scan;
    delete quick;
    foreach (BitIO* ptr, ioHash.values()) {
       delete ptr;
    }
    foreach (AnIO* ptr, anIoHash.values()) {
       delete ptr;
    }
}

void DebuggerForm::on_treeWidgetMain_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    // добавление элемента из основного дерева к дереву просмотра
    Q_UNUSED(column)
    if(idWidgetItem.values().contains(item)) {
        QString id = idWidgetItem.key(item);
        if(iter->goToID(id)) {
            VarItem var = varOwner.getVarByID(id);
            QStringList sList;
            QString varName;
            QString fullName = var.getName();
            if(iter->up()) {
                VarItem var = varOwner.getVarByID(iter->currentID());
                do{var = varOwner.getVarByID(iter->currentID());fullName = var.getName()+"."+fullName;}while (iter->up());
            }
            QStringList fNameList = fullName.split('.');
            fNameList.removeFirst();fNameList.removeFirst();
            foreach (QString s, fNameList) {
               varName += "." + s;
            }
            varName.remove(0,1);

            if(idActiveWidgetItem.contains(id)) return;

            QRegExp exp(".*\\.\\d+.*");
            if(exp.indexIn(varName)==-1) {
                QStringList names = varName.split(".");
                varName = names.last();
            }


            sList << varName << "" << "" << "0x"+QString::number(var.getMemAddress(),16).toUpper() << var.getDataType();
            QTreeWidgetItem* newItem = new QTreeWidgetItem(sList);
            idActiveWidgetItem.insert(id,newItem);
            var.setPriority(1);
            newItem->setToolTip(0,fullName);
            ui->treeWidgetWatch->addTopLevelItem(newItem);
            ui->treeWidgetWatch->setItemWidget(newItem,5,new QLineEdit("-",ui->treeWidgetWatch));

            scheduler.addReadOperation(var);
            scheduler.schedule();
        }
    }
}

void DebuggerForm::on_treeWidgetWatch_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    // редактирование переменной
    if(column==1) {
        if((item)&&(scan->isWorking())) {
            QString id = idActiveWidgetItem.key(item);
            if(!id.isEmpty()) {
                VarItem var = varOwner.getVarByID(id);
                wrVar = var;
                if(var.getBitNum()>=0) {
                    writeVar();
                }else {
                    wrVar.setValue(item->text(1));
                    writeVar();
                }
            }
        }
    }
    else {
        // удаление переменной из дерева просмотра
        QString id = idActiveWidgetItem.key(item);
        VarItem var = varOwner.getVarByID(id);
        var.setPriority(0);
        varOwner.updateVarByID(id,var);
        idActiveWidgetItem.remove(id);
        ui->treeWidgetWatch->removeItemWidget(item,5);
        delete item;

        scheduler.removeReadOperation(var); // удаление области памяти переменной из опроса
        // повторное сканирование переменных на случай их пересечения с удалённым участком
        QStringList idList = idActiveWidgetItem.keys();
        foreach (QString varID, idList) {
           var = varOwner.getVarByID(varID);
           var.setPriority(1);
           scheduler.addReadOperation(var);
        }
        scheduler.schedule();
    }
}

void DebuggerForm::on_startButton_clicked()
{
    DebuggerSettings settings;
    settings.setPortName(ui->comboBoxCOM->currentText());
    settings.setProtocol(ui->comboBoxProtocol->currentText());
    settings.setBaudrate(ui->comboBoxSpeed->currentText().toInt());
    settings.setNetAddress(ui->spinBoxNetAddress->value());
    settings.setIpAddress(ui->lineEditIP->text());
    settings.setUdpFlag(ui->radioButtonUDP->isChecked());
    scan->setDebSettings(settings);

    ui->tabWidgetCanal->setEnabled(false);
    ui->pushButtonTimeWrite->setEnabled(true);
    ui->radioButtonCOM->setEnabled(false);
    ui->radioButtonUDP->setEnabled(false);
    ui->spinBoxNetAddress->setEnabled(false);
    ui->stopButton->setEnabled(true);
    ui->startButton->setEnabled(false);

    scan->setScheduler(&scheduler);
    scan->startDebugger();
}

void DebuggerForm::on_stopButton_clicked()
{
    scan->stopDebugger();
    int cnt = 0;
    while(scan->isWorking()) {
        cnt++;
        QThread::msleep(1);
        if(cnt>=1000) break;
    }
    ui->tabWidgetCanal->setEnabled(true);
    ui->pushButtonTimeWrite->setEnabled(false);
    ui->radioButtonCOM->setEnabled(true);
    ui->radioButtonUDP->setEnabled(true);
    ui->spinBoxNetAddress->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->startButton->setEnabled(true);
}

void DebuggerForm::updateMemory(QStringList ids)
{
    foreach (QString id, ids) {
        // если активна вкладка входов/выходов
        if(ui->tabWidget->currentIndex()==1) {
            updateIOVarGUI(id);
            if(ui->checkBoxQuickWatch->isChecked()) updateVarGUI(id);
        }else if(ui->tabWidget->currentIndex()==0) {
            updateVarGUI(id);
        }else if(ui->tabWidget->currentIndex()==2) {
            updateMemVarGUI(id);
            if(ui->checkBoxQuickWatch->isChecked()) updateVarGUI(id);
        }
    }
}

void DebuggerForm::updateCorrErrAnswerCount(int cnt, bool correctFlag)
{
    if(correctFlag) ui->lcdNumberCorrect->display(cnt);
    else ui->lcdNumberError->display(cnt);
}

void DebuggerForm::getMessageFromDebugProcess(QString message)
{
    if(!ui->textBrowserRequests->isEnabled()) return;
    QString txt = ui->textBrowserRequests->toPlainText();
    QStringList sList = txt.split("\n");
    if(sList.count()>5) {
        sList.removeFirst();
        sList+=message;
    }else sList+=message;
    txt="";
    foreach (QString str, sList) {
        if(!str.isEmpty()) txt+=str+"\n";
    }
    ui->textBrowserRequests->setText(txt);
}

void DebuggerForm::getTimeStr(QString timeStr)
{
    if(!ui->lineEditTime->hasFocus())
    ui->lineEditTime->setText(timeStr);
}

void DebuggerForm::on_updateButton_clicked()
{
    idWidgetItem.clear();
    createTree();
    updateValuesTree();
    VarToMemConnector::updateConnection(memStor,varOwner.getIDStorage());
    update();
}

void DebuggerForm::openProject()
{
    updTree();
    updateIOFoldedState();
}

void DebuggerForm::saveProject()
{
    saveView();
}

void DebuggerForm::newProject()
{
    updTree();
    clearView();
    updateIOFoldedState();
}

void DebuggerForm::updTree()
{
    on_updateButton_clicked();
    openView();
    updateMatchboxVisibility();
    tabChanged();
}

void DebuggerForm::updateValuesTree()
{
    QHash<QString,QString> fullNames;
    foreach (QTreeWidgetItem* item, idWidgetItem.values()) {
       QString fName = item->toolTip(0);
       fullNames.insert(fName,idWidgetItem.key(item));
    }
    scheduler.clear();
    QList<QTreeWidgetItem*> actItems = idActiveWidgetItem.values();
    for(int i=0;i<actItems.count();i++) {
        QString curId = idActiveWidgetItem.key(actItems.at(i));
        QString curFullName = actItems.at(i)->toolTip(0);
        QString newId = fullNames.value(curFullName);
        if(!newId.isEmpty()) {
            if(curId != newId) {
                VarItem var = varOwner.getVarByID(newId);
                idActiveWidgetItem.remove(curId);
                idActiveWidgetItem.insert(newId,actItems.at(i));
                actItems[i]->setText(3,"0x"+QString::number(var.getMemAddress(),16).toUpper());
                actItems[i]->setText(4,var.getDataType());
            }
        }
    }
    foreach (QString id, idActiveWidgetItem.keys()) {
        VarItem var = varOwner.getVarByID(id);
        var.setPriority(1);
        scheduler.addReadOperation(var);
    }
    scheduler.schedule();
}

void DebuggerForm::updateComPortList()
{
    QStringList portNames;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            portNames << info.portName();
    }
    ui->comboBoxCOM->clear();
    if(portNames.count()) {
        foreach (QString pName, portNames) {
           ui->comboBoxCOM->addItem(pName);
        }
    }
}

void DebuggerForm::buildIO()
{
    buildDIO(); // вывод дискретных датчиков
    buildAIO(); // вывод аналоговых датчиков
}

void DebuggerForm::buildDIO()
{
    // используется компоновщик по сетке, который помещается в виджет прокрутки
    QWidget *client = new QWidget(this);
    QGridLayout *grLayout= new QGridLayout(client);

    for(int i=0;i<6;i++) {
        QString name;
        if(i<4) name = "IN"+QString::number(i);
        else name = "DIN" + QString::number(i);
        QGroupBox *boxIn = addDIO(name,BitIO::inputStartAddress + i,8);
        boxIn->setStyleSheet(QString::fromUtf8("QGroupBox { background-color: rgb(230,240,240); border: 1px solid darkgray; border-radius: 5px; margin-top: 7px; margin-bottom: 7px; padding: 0px} QGroupBox::title {top:-7 ex;left: 10px; subcontrol-origin: border}"));
        ioBoxes+=boxIn;
        boxIn->setCheckable(true);
        boxIn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        connect(boxIn,SIGNAL(toggled(bool)),this,SLOT(boxToggled(bool)));
        grLayout->addWidget(boxIn,1,i+1);

        if(i<4) name = "OUT"+QString::number(i);
        else name = "DOUT" + QString::number(i);
        QGroupBox *boxOut = addDIO(name,BitIO::outputStartAddress + i,8);
        boxOut->setStyleSheet(QString::fromUtf8("QGroupBox { background-color: rgb(230,240,240); border: 1px solid darkgray; border-radius: 5px; margin-top: 7px; margin-bottom: 7px; padding: 0px} QGroupBox::title {top:-7 ex;left: 10px; subcontrol-origin: border}"));
        ioBoxes+=boxOut;
        boxOut->setCheckable(true);
        boxOut->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        connect(boxOut,SIGNAL(toggled(bool)),this,SLOT(boxToggled(bool)));
        grLayout->addWidget(boxOut,2,i+1);
    }
    MatchboxExistance mmb;
    QString mmbList = mmb.getMatchboxFile();
    // модули Matchbox
    for(int i=0;i<32;i++) {
        QString name;
        name = "IN"+QString::number(i+4);
        QGroupBox *boxIn = addDIO(name,BitIO::mmbInputStartAddress + i,4);
        if(!mmb.checkIO(name,mmbList)) boxIn->setVisible(false);
        ioBoxes+=boxIn;
        boxIn->setCheckable(true);
        boxIn->setStyleSheet(QString::fromUtf8("QGroupBox { background-color: rgb(230,240,240); border: 1px solid darkgray; border-radius: 5px; margin-top: 7px; margin-bottom: 7px; padding: 0px} QGroupBox::title {top:-7 ex;left: 10px; subcontrol-origin: border}"));
        connect(boxIn,SIGNAL(toggled(bool)),this,SLOT(boxToggled(bool)));
        grLayout->addWidget(boxIn,3+(i/6)*2,(i%6)+1);

        name = "OUT"+QString::number(i+4);

        QGroupBox *boxOut = addDIO(name,BitIO::mmbOutputStartAddress + i,4);
        if(!mmb.checkIO(name,mmbList)) boxOut->setVisible(false);
        ioBoxes+=boxOut;
        boxOut->setCheckable(true);
        boxOut->setStyleSheet(QString::fromUtf8("QGroupBox { background-color: rgb(230,240,240); border: 1px solid darkgray; border-radius: 5px; margin-top: 7px; margin-bottom: 7px; padding: 0px} QGroupBox::title {top:-7 ex;left: 10px; subcontrol-origin: border}"));
        connect(boxOut,SIGNAL(toggled(bool)),this,SLOT(boxToggled(bool)));
        grLayout->addWidget(boxOut,4+(i/6)*2,(i%6)+1);
    }
    client->setLayout(grLayout);
    ui->scrollArea->setWidget(client);
}

void DebuggerForm::updateIOFoldedState()
{
    foreach (QGroupBox *box, ioBoxes) {
       QString name = box->title();
       if(ioCheck.keys().contains(name)) {
           bool res = ioCheck.value(name);
           box->setChecked(res);
       }else box->setChecked(false);
    }
}

QGroupBox *DebuggerForm::addDIO(const QString &name, int startAddress, int bitCnt)
{
    QGroupBox *box = new QGroupBox(name);
    QVBoxLayout *layout = new QVBoxLayout(box);
    for(int j=0;j<bitCnt;j++) {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QPushButton *b = new QPushButton();
        b->setStyleSheet("border: 2px solid #8f8f91;border-radius: 10px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
        b->setFixedSize(20,20);
        connect(b,SIGNAL(clicked()),this,SLOT(inOutClicked()));
        QLineEdit *e = new QLineEdit();
        hLayout->addWidget(b);
        hLayout->addWidget(e);
        layout->addLayout(hLayout);
        BitIO *bitDef = new BitIO();
        bitDef->setName(name+"."+QString::number(j));
        bitDef->setBitNum(j);
        bitDef->setButton(b);
        bitDef->setComment(e);
        bitDef->setAddress(startAddress);
        bitDef->setState(false);
        ioHash.insert(bitDef->getAddress(),bitDef);
        ioComments.insert(bitDef->getName(),e);
    }
    box->setLayout(layout);
    return box;
}

QVector<QGroupBox*> DebuggerForm::addAIO(const QString &grName, const QString &ioName, int addr, int startNum, int endNum)
{
    Q_UNUSED(grName)
    QVector<QGroupBox*> groups;
    for(int i=startNum;i<=endNum;i++) {
        QGroupBox *box = new QGroupBox(ioName+QString::number(i));
        QHBoxLayout *hLayout = new QHBoxLayout();
        AnInpSlider *slider = new AnInpSlider();
        slider->setOrientation(Qt::Horizontal);
        slider->setMaximum(65535);
        slider->setMinimum(0);
        connect(slider,SIGNAL(valueChanged(int)),this,SLOT(anInOutClicked()));

        QLineEdit *number = new QLineEdit();
        number->setStyleSheet("border: 2px solid gray;"
                              "border-radius: 5px;"
                              "padding: 0 8px;"
                              "background: rgb(230,240,240);");
        number->setReadOnly(true);
        QLineEdit *comment = new QLineEdit();

        hLayout->addWidget(slider,2);
        hLayout->addWidget(number,1);
        hLayout->addWidget(comment,2);
        box->setLayout(hLayout);
        box->setCheckable(true);
        box->setFlat(true);
        hLayout->setMargin(0);
        connect(box,SIGNAL(toggled(bool)),this,SLOT(boxToggled(bool)));
        groups+=box;
        AnIO *aDef = new AnIO();
        aDef->setName(ioName+QString::number(i));
        aDef->setAddress(addr+(i-startNum)*2);
        aDef->setComment(comment);
        aDef->setLcdNum(number);
        aDef->setSlider(slider);
        anIoHash.insert(aDef->getAddress(),aDef);
        ioComments.insert(aDef->getName(),comment);
    }
    return groups;
}

void DebuggerForm::buildAIO()
{
    QWidget *clientAn = new QWidget(this);
    QVBoxLayout *vLayoutAn= new QVBoxLayout(clientAn);

    adc8bit = new QCheckBox("  АЦП - 8 бит");
    adc8bit->setChecked(true);
    connect(adc8bit,SIGNAL(clicked(bool)),this,SLOT(adc8bitChanged()));
    vLayoutAn->addWidget(adc8bit);

    QVector<QGroupBox*> boxAdc = addAIO("ADC1..8","ADC",AnIO::inputStartAddress,1,8);
    ioBoxes+=boxAdc;
    foreach(QGroupBox* box, boxAdc) {vLayoutAn->addWidget(box);}

    QVector<QGroupBox*> boxAdcI2C = addAIO("ADC201..208","ADC",AnIO::i2cInputStartAddress,201,208);
    ioBoxes+=boxAdcI2C;
    foreach(QGroupBox* box, boxAdcI2C) {vLayoutAn->addWidget(box);}

    QVector<QGroupBox*> boxAdcMmb = addAIO("Matchbox ADC","ADC",AnIO::mmbInputStartAddress,9,136);
    ioBoxes += boxAdcMmb;
    foreach(QGroupBox* box, boxAdcMmb) vLayoutAn->addWidget(box);

    QVector<QGroupBox*> boxDac = addAIO("DAC1..4","DAC",AnIO::outputStartAddress,1,4);
    ioBoxes+=boxDac;
    foreach(QGroupBox* box, boxDac) vLayoutAn->addWidget(box);

    QVector<QGroupBox*> boxDacMmb = addAIO("Matchbox DAC","DAC",AnIO::mmbOutputStartAddress,5,68);
    ioBoxes += boxDacMmb;
    foreach(QGroupBox* box, boxDacMmb) vLayoutAn->addWidget(box);


    clientAn->setLayout(vLayoutAn);
    ui->scrollArea_2->setWidget(clientAn);
}

void DebuggerForm::updateIOVarGUI(const QString &id)
{
    if(idWidgetItem.contains(id)) { // проверка существования id в проекте
        VarItem var = varOwner.getVarByID(id);  // переменная, связанная с идентификатором
        if(var.getMemType()==MemStorage::ioMemName) {   // проверка типа памяти переменной
            if(ioHash.contains(var.getMemAddress())) {  // поиск переменной среди дискретных вх/вых
                QList<BitIO*> ptrList = ioHash.values(var.getMemAddress());
                QByteArray data = memStor.getData(var.getMemType(),var.getMemAddress(),1);
                foreach (BitIO* ptr, ptrList) {
                    bool state = data[0]&1<<ptr->getBitNum();
                    // обновлять GUI только по изменению состояния
                    if(state!=ptr->getState()) {
                        if(state) {
                            if(ptr->getName().contains("IN"))
                            ptr->getButton()->setStyleSheet("border: 2px solid #8f8f91;border-radius: 10px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #00ff00, stop: 1 #ffffff);");
                            else
                            ptr->getButton()->setStyleSheet("border: 2px solid #8f8f91;border-radius: 10px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #ff0000, stop: 1 #ffffff);");
                        }
                        else {
                            ptr->getButton()->setStyleSheet("border: 2px solid #8f8f91;border-radius: 10px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
                        }
                        ptr->setState(state);
                    }
                }
            }else if(anIoHash.contains(var.getMemAddress())) {
                AnIO* ptr = anIoHash.value(var.getMemAddress());
                QByteArray data = memStor.getData(var.getMemType(),var.getMemAddress(),2);
                quint16 value = (quint8)data[1];
                value = (value<<8) | ((quint8)data[0]);
                QString txtValue = QString::number(value);
                if(adc8bit->isChecked()) {
                   if(ptr->getName().contains("ADC")) txtValue = QString::number(value>>8);
                }
                ptr->getLcdNum()->setText(txtValue);
                if(!ptr->getSlider()->hasFocus()) ptr->getSlider()->setValue(value);
            }
        }
    }
}

void DebuggerForm::updateVarGUI(const QString &id)
{
    if(idActiveWidgetItem.contains(id)) {
        QTreeWidgetItem* item = idActiveWidgetItem.value(id);
        VarItem var = varOwner.getVarByID(id);
        int varSize=VarBytesValueConverter::getVarSize(var.getDataType());
        if(varSize) {
            QByteArray data = memStor.getData(var.getMemType(),var.getMemAddress(),varSize);
            if(data.count()==varSize) {
                QString value="";
                for(int i=0;i<varSize;i++) {
                    // формат значения - байты данных, разделённые двоеточием
                    value+=QString::number((quint8)(data.at(i)))+":";
                }
                var.setValue(value);
                varOwner.updateVarByID(id,var);
                item->setText(1,VarBytesValueConverter::getValue(var,data));
                item->setText(2,QDateTime::currentDateTime().time().toString());
            }
        }
    }
}

void DebuggerForm::updateMemVarGUI(const QString &id)
{
    if(VarItem::getVarTypeFromID(id)!=VarItem::ucharType) return;
    if(VarItem::getBitNumFromID(id)!=-1) return;
    QString memtype = VarItem::getMemTypeFromID(id);
    if(!memtype.toLower().contains(ui->comboBoxMemType->currentText().toLower())) return;

    int curAddr = VarItem::getMemAddressFromID(id);

    QString addrStr = ui->lineEditMemStartAddr->text();
    addrStr = addrStr.toLower();
    addrStr.remove("0x");
    bool res = false;
    int startAddr = ui->lineEditMemStartAddr->text().toInt(&res,16);
    if(res) {
        int tabLastAddress = startAddr + memViewRowCount*memViewColumnCount - 1;
        if((curAddr>=startAddr)&&(curAddr<=tabLastAddress)) {
            if(memView->checkAddress(curAddr)) {
                int num = curAddr - startAddr;
                int row = num/memViewColumnCount;
                int col = num%memViewColumnCount;
                if((row<memViewRowCount)&&(col<memViewColumnCount)) {
                    QByteArray data = memStor.getData(memtype,curAddr,1);
                    if(data.count()) {
                        int value = (unsigned char)data.at(0);

                        QTableWidgetItem *item = ui->tableWidgetMem->item(row,col);
                        if(item!=nullptr) {
                            disconnect(ui->tableWidgetMem,SIGNAL(cellChanged(int,int)),this,SLOT(memViewCellPressed(int,int)));
                            item->setText(QString::number(value));
                            item->setTextColor(Qt::darkBlue);
                            connect(ui->tableWidgetMem,SIGNAL(cellChanged(int,int)),this,SLOT(memViewCellPressed(int,int)));
                        }
                    }
                }
            }
        }
    }
}

void DebuggerForm::updateMatchboxVisibility()
{
    MatchboxExistance mmb(plcType);
    QString mmbList = mmb.getMatchboxFile();
    foreach (QGroupBox* gr, ioBoxes) {
        QString grName = gr->title();
        if(mmb.checkIO(grName,mmbList)) gr->setVisible(true);
        else gr->setVisible(false);
    }
}

int DebuggerForm::getIOAddrByName(const QString &name)
{
    foreach (BitIO *io, ioHash) {
        if(io->getName().contains(QRegExp("\\b" + name + "\\b"))) return ioHash.key(io);
    }
    foreach (AnIO *io, anIoHash) {
        if(io->getName() == name) return anIoHash.key(io);
    }
    return -1;
}

void DebuggerForm::memViewCellPressed(int r, int c)
{
    QTableWidgetItem *item = ui->tableWidgetMem->item(r,c);
    if(item!=nullptr) {
        QString addrStr = ui->lineEditMemStartAddr->text();
        addrStr = addrStr.toLower();
        addrStr.remove("0x");
        bool res = false;
        int startAddr = ui->lineEditMemStartAddr->text().toInt(&res,16);
        if(res) {
            int curAddr = startAddr + r*memViewColumnCount + c;
            QString memType;
            if(memView->getMemType()==MemViewDescription::FRAM) memType = MemStorage::framMemName;
            if(memView->getMemType()==MemViewDescription::RAM) memType = MemStorage::ramMemName;
            int value = item->text().toInt();
            VarItem var;
            var.setDataType(VarItem::ucharType);
            var.setMemType(memType);
            var.setMemAddress(curAddr);
            var.setValue(QString::number(value));
            scheduler.addWriteOperation(var);
            ui->treeWidgetWatch->setFocus();
        }

    }
}

void DebuggerForm::on_pushButtonCOMUpdate_clicked()
{
    updateComPortList();
}

void DebuggerForm::on_pushButtonAutoSearch_clicked()
{
    int progAddr = ui->spinBoxNetAddress->value();

    ScanGUI gui(progAddr,false, this);
    int ret = gui.exec();
    if(ret==QDialog::Accepted) {
        DetectedController* plc = &DetectedController::Instance();
        if(plc->getBootMode()) {
            QMessageBox::warning(this,"системные настройки контроллера","Контроллер ожидает загрузки программы.\n");
        }
        else{
            updateComPortList();
            ui->comboBoxCOM->setCurrentText(plc->getUartName());
            ui->comboBoxSpeed->setCurrentText(QString::number(plc->getBaudrate()));
            QString protocol = "BIN";
            if(plc->getAsciiMode()) protocol = "ASCII";
            ui->comboBoxProtocol->setCurrentText(protocol);
            ui->lineEditCanal->setText(plc->getCanName());
        }
    }
}

void DebuggerForm::on_checkBoxLog_clicked()
{
    if(ui->checkBoxLog->isChecked()) ui->textBrowserRequests->setEnabled(true);
    else {
        ui->textBrowserRequests->setEnabled(false);
    }
}

void DebuggerForm::on_pushButtonTimeWrite_clicked()
{
    // Синхронизация времени
    VarItem var;
    var.setMemAddress(0);
    var.setMemType(MemStorage::timeMemName);
    var.setDataType(VarItem::timeType);
    QByteArray timeData;
    QTime curtime = QDateTime::currentDateTime().time();
    QDate curdate = QDateTime::currentDateTime().date();
    timeData += curtime.second();
    timeData += curtime.minute();
    timeData += curtime.hour();
    timeData += curdate.dayOfWeek();
    timeData += curdate.day();
    timeData += curdate.month();
    timeData += curdate.year()%100;
    QString strData;
    for(int i=0;i<timeData.count();i++) {
       // приведение данных к формату ПЛК
       unsigned char tmp = timeData.at(i)%10 + ((timeData.at(i)/10)<<4);
       strData += QString::number(tmp) + " ";
    }
    var.setValue(strData);
    scheduler.addWriteOperation(var);
}

void DebuggerForm::on_treeWidgetWatch_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem* item =  ui->treeWidgetWatch->itemAt(pos);
    if((item)&&(scan->isWorking())) {
        QString id = idActiveWidgetItem.key(item);
        if(!id.isEmpty()) {
            VarItem var = varOwner.getVarByID(id);
            wrVar = var;
            QMenu *menu=new QMenu(this);
            if(var.getBitNum()>=0) {
                menu->addAction(QIcon("://write_32.ico"),"Переключить",this,SLOT(writeVar()));
            }else {
                wrVar.setValue(item->text(1));
                menu->addAction(QIcon("://write_32.ico"),"Изменить",this,SLOT(writeVar()));
            }
            menu->popup(ui->treeWidgetWatch->viewport()->mapToGlobal(pos));
        }
    }
}

void DebuggerForm::writeVar()
{
    // запись переменной
    if(wrVar.getBitNum()>=0) {  // битовая переменная
        // байты значения при формировании разделены двоеточием
        // в исходном значении инвертируется необходимый бит
        QStringList values = wrVar.getValue().split(":");
        if(values.count()) {
            quint8 byteValue = values.at(0).toInt();
            byteValue = byteValue ^ (1<<wrVar.getBitNum());
            wrVar.setValue(QString::number(byteValue));
            scheduler.addWriteOperation(wrVar);
        }
    }else {
        DialogWriteVar* dialog = new DialogWriteVar(wrVar.getValue(),this);
        dialog->setVar(wrVar);
        int ret = dialog->exec();
        if(ret==QDialog::Accepted) {
            if(dialog->checkResult()) {
                wrVar.setValue(dialog->getResult());
                scheduler.addWriteOperation(wrVar);
            }
            else QMessageBox::warning(this,"Изменение переменной","Некорректное значение");
        }
        delete dialog;
    }
}

void DebuggerForm::inOutClicked()
{
     QPushButton * b = qobject_cast<QPushButton *>(sender());
     if(b) {
         foreach (BitIO* ptr, ioHash.values()) {
            if(ptr->getButton()==b) {
                VarItem var;
                QByteArray data = memStor.getData(MemStorage::ioMemName,ptr->getAddress(),1);
                if(data.count()) {
                    quint8 byte = data[0] ^ (1<<ptr->getBitNum());
                    var.setValue(QString::number(byte));
                    var.setDataType(VarItem::ucharType);
                    var.setMemAddress(ptr->getAddress());
                    var.setMemType(MemStorage::ioMemName);
                    var.setPriority(1);
                    scheduler.addWriteOperation(var);
                }
                break;
            }
         }
     }
}

void DebuggerForm::anInOutClicked()
{
    QSlider  *sl = qobject_cast<QSlider *>(sender());
    if(sl) {
        foreach (AnIO* ptr, anIoHash.values()) {
           if(ptr->getSlider()==sl) {
               VarItem var;
               quint16 byte = sl->value();
               var.setValue(QString::number(byte));
               var.setDataType(VarItem::ushortType);
               var.setMemAddress(ptr->getAddress());
               var.setMemType(MemStorage::ioMemName);
               var.setPriority(1);
               scheduler.addWriteOperation(var);
               break;
           }
        }
    }
}


void DebuggerForm::on_tabWidget_currentChanged(int index)
{
    if(index==0) {  // вкладка просмотра переменных
        scheduler.clear();
        foreach (QString id, idActiveWidgetItem.keys()) {
            VarItem var = varOwner.getVarByID(id);
            var.setPriority(1);
            scheduler.addReadOperation(var);
        }
        scheduler.schedule();
    }else if(index==1) {    // вкладка входов/выходов
        scheduler.clear();
        // стандартные вх/вых
        for(int i=0;i<0x23;i++) {//MemStorage::ioMemSize;i++) {
            VarItem var;
            var.setDataType(VarItem::ucharType);
            var.setMemType(MemStorage::ioMemName);
            var.setPriority(1);
            var.setMemAddress(i);
            scheduler.addReadOperation(var);
        }
        for(int i=484;i<500;i++) {//MemStorage::ioMemSize;i++) {
            VarItem var;
            var.setDataType(VarItem::ucharType);
            var.setMemType(MemStorage::ioMemName);
            var.setPriority(1);
            var.setMemAddress(i);
            scheduler.addReadOperation(var);
        }
        // модули Matchbox
        foreach (QGroupBox *box, ioBoxes) {
            if(box->isVisible()) {
                QString ioName = box->title();
                int addr = getIOAddrByName(ioName);
                if(addr!=-1) {
                    VarItem var;
                    var.setDataType(VarItem::ushortType);
                    var.setMemType(MemStorage::ioMemName);
                    var.setPriority(1);
                    var.setMemAddress(addr);
                    scheduler.addReadOperation(var);
                }
            }
        }
        if(ui->checkBoxQuickWatch->isChecked()) {
            foreach (QString id, idActiveWidgetItem.keys()) {
                VarItem var = varOwner.getVarByID(id);
                var.setPriority(1);
                scheduler.addReadOperation(var);
            }
        }
        scheduler.schedule();
    }else if(index==2) {    // память
        updateMemViewRequests();
        clearMemViewTable();
    }
}

void DebuggerForm::adc8bitChanged()
{
    QList<AnIO*> aios = anIoHash.values();
    foreach(AnIO* aio, aios) {
        QSlider* sl = aio->getSlider();
        AnInpSlider* anSl = dynamic_cast<AnInpSlider*>(sl);
        if(anSl!=nullptr) anSl->setEightBit(adc8bit->isChecked());
    }
}

void DebuggerForm::getQuickWatchInfo()
{
    QStringList names,values;
    foreach (QTreeWidgetItem* item, idActiveWidgetItem.values()) {
        names += item->text(0);
        values += item->text(1);
    }
    emit quickInfo(names, values);
}


void DebuggerForm::on_pushButtonPing_clicked()
{
    QString ip = ui->lineEditIP->text();
    QRegExp exp("^(\\d{1,3})\\.(\\d{1,3}).(\\d{1,3}).(\\d{1,3})");
    if(exp.indexIn(ip)!=-1) {
        ip = QString::number(exp.cap(1).toInt()) +
            "." + QString::number(exp.cap(2).toInt()) +
            "." + QString::number(exp.cap(3).toInt()) +
            "." + QString::number(exp.cap(4).toInt());
    }else ip="";
    if(!ip.isEmpty()) {
        QProcess pingProcess;
        QString exec = "ping";
        QStringList params;
        params << "-n" << "1" << ip;
        pingProcess.start(exec,params,QIODevice::ReadOnly);
        pingProcess.waitForFinished(-1);

        QTextCodec *codec = QTextCodec::codecForName("CP866");
        QString p_stdout = codec->toUnicode(pingProcess.readAllStandardOutput());
        QString p_stderr = codec->toUnicode(pingProcess.readAllStandardError());


        QMessageBox::information(this,"PING",p_stdout + "\n" + p_stderr);
    }else {
        QMessageBox::warning(this,"Ошибка ввода","Некорректный IP адрес");
    }
}

void DebuggerForm::boxToggled(bool fl)
{
    QGroupBox *box = dynamic_cast<QGroupBox*>(sender());
    if(box!=nullptr) {
        QObjectList childs = box->children();
        foreach (QObject *ob, childs) {
           QWidget *w = dynamic_cast<QWidget*>(ob);
           if(w!=nullptr) {
               w->setVisible(fl);
           }
        }
    }
}

void DebuggerForm::openInputs()
{
    if(!scan->isWorking()) {
        QMessageBox::information(this,"сообщение","Необходимо предварительно запустить отладчик");
    }else {
        QString  konFileName = PathStorage::getKonFileFullName();
        QString path = QFileInfo(konFileName).absoluteDir().absolutePath();
        QString fName;
        fName = QFileDialog::getOpenFileName(this, tr("Загрузить состояния входов"),
                                                        path,
                                                        tr("SnapShot file (*.inp )"));
        openInputs(fName);
    }
}

void DebuggerForm::openInputs(const QString &fName)
{
    if(!fName.isEmpty()) {
        lastOpenInpFile = fName;
        ui->pushButtonOpenLastInp->setEnabled(true);
        QFile file(fName);
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&file);
            stream.setVersion(QDataStream::Qt_5_4);
            QByteArray diData,diDataCur;
            QByteArray aiData,aiDataCur;
            QByteArray mdiData,mdiDataCur;
            QByteArray maiData,maiDataCur;
            QByteArray i2cAiData, i2cAiDataCur;
            stream >> diData;
            stream >> aiData;
            stream >> mdiData;
            stream >> maiData;
            stream >> i2cAiData;

            diDataCur = memStor.getData(MemStorage::ioMemName,0x00,5);
            for(int i=0;i<diData.count();i++) {
                if(diDataCur.at(i)!=diData.at(i)) {
                    VarItem var;
                    var.setValue(QString::number(diData.at(i)));
                    var.setDataType(VarItem::ucharType);
                    var.setMemAddress(0x00 + i);
                    var.setMemType(MemStorage::ioMemName);
                    var.setPriority(1);
                    scheduler.addWriteOperation(var);
                }
            }
            aiDataCur = memStor.getData(MemStorage::ioMemName,0x0C,16);
            for(int i=0;i<aiData.count();i++) {
                if(aiDataCur.at(i)!=aiData.at(i)) {
                    VarItem var;
                    var.setValue(QString::number(aiData.at(i)));
                    var.setDataType(VarItem::ucharType);
                    var.setMemAddress(0x0C + i);
                    var.setMemType(MemStorage::ioMemName);
                    var.setPriority(1);
                    scheduler.addWriteOperation(var);
                }
            }
            i2cAiDataCur = memStor.getData(MemStorage::ioMemName,AnIO::i2cInputStartAddress,16);
            for(int i=0;i<i2cAiData.count();i++) {
                if(i2cAiDataCur.at(i)!=i2cAiData.at(i)) {
                    VarItem var;
                    var.setValue(QString::number(i2cAiData.at(i)));
                    var.setDataType(VarItem::ucharType);
                    var.setMemAddress(AnIO::i2cInputStartAddress + i);
                    var.setMemType(MemStorage::ioMemName);
                    var.setPriority(1);
                    scheduler.addWriteOperation(var);
                }
            }
            mdiDataCur = memStor.getData(MemStorage::ioMemName,0x24,32);
            MatchboxExistance mmb;
            QString mmbList = mmb.getMatchboxFile();

            for(int i=0;i<mdiData.count();i++) {
                if(mdiDataCur.at(i)!=mdiData.at(i)) {
                    if(mmb.checkIO("IN" +QString::number(4+i),mmbList)) {
                        VarItem var;
                        var.setValue(QString::number(mdiData.at(i)));
                        var.setDataType(VarItem::ucharType);
                        var.setMemAddress(0x24 + i);
                        var.setMemType(MemStorage::ioMemName);
                        var.setPriority(1);
                        scheduler.addWriteOperation(var);
                    }
                }
            }
            maiDataCur = memStor.getData(MemStorage::ioMemName,0x64,256);
            for(int i=0;i<maiData.count();i++) {
                if(maiDataCur.at(i)!=maiData.at(i)) {
                    if(mmb.checkIO("ADC" +QString::number(9+i/2),mmbList)) {
                        VarItem var;
                        var.setValue(QString::number(maiData.at(i)));
                        var.setDataType(VarItem::ucharType);
                        var.setMemAddress(0x64 + i);
                        var.setMemType(MemStorage::ioMemName);
                        var.setPriority(1);
                        scheduler.addWriteOperation(var);
                    }
                }
            }
            int vCnt = 0;
            stream >> vCnt;
            if(stream.status()==QDataStream::Ok) {
                QHash<QString,QString> fullNames;
                foreach (QTreeWidgetItem* item, idWidgetItem.values()) {
                   QString fName = item->toolTip(0);
                   fullNames.insert(fName,idWidgetItem.key(item));
                }
                for(int i=0;i<vCnt;i++) {
                    QString fullName;
                    stream >> fullName;
                    bool bitVar;
                    stream >> bitVar;
                    QString vValue;
                    stream >> vValue;
                    if((bitVar==false)&&(!vValue.isEmpty())) {
                        QString newId = fullNames.value(fullName);
                        if(!newId.isEmpty()) {
                            VarItem var = varOwner.getVarByID(newId);
                            var.setValue(vValue);
                            scheduler.addWriteOperation(var);
                        }
                    }
                }
            }
            file.close();
        }else QMessageBox::warning(this,"Предупреждение","Не удалось открыть файл");
    }
}

void DebuggerForm::saveInputs()
{
    QByteArray diData = memStor.getData(MemStorage::ioMemName,0x00,5);
    QByteArray aiData = memStor.getData(MemStorage::ioMemName,0x0C,16);
    QByteArray mdiData = memStor.getData(MemStorage::ioMemName,0x24,32);
    QByteArray maiData = memStor.getData(MemStorage::ioMemName,0x64,256);
    QByteArray i2cAiData = memStor.getData(MemStorage::ioMemName,AnIO::i2cInputStartAddress,16);
    QString  konFileName = PathStorage::getKonFileFullName();
    QString path = QFileInfo(konFileName).absoluteDir().absolutePath();
    QString fName;
    fName = QFileDialog::getSaveFileName(this, tr("Сохранение состояния входов"),
                                                    path,
                                                    tr("SnapShot file (*.inp )"));
    if(!fName.isEmpty()) {
        QFile file(fName);
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream stream(&file);
            stream.setVersion(QDataStream::Qt_5_4);
            stream << diData;
            stream << aiData;
            stream << mdiData;
            stream << maiData;
            stream << i2cAiData;
            stream << idActiveWidgetItem.count();   // количество переменных в окне просмотра
            foreach (QString id, idActiveWidgetItem.keys()) {
                VarItem var = varOwner.getVarByID(id);
                stream << idActiveWidgetItem.value(id)->toolTip(0);
                bool bitVar = (var.getBitNum()>=0)?true:false;
                stream << bitVar;
                QString vValue = idActiveWidgetItem.value(id)->text(1);
                stream << vValue;
            }

            file.close();
        }else QMessageBox::warning(this,"Предупреждение","Не удалось сохранить файл");
    }
}

void DebuggerForm::on_lineEditTime_returnPressed()
{
    VarItem var;
    var.setMemAddress(0);
    var.setMemType(MemStorage::timeMemName);
    var.setDataType(VarItem::timeType);

    QString timeStr = ui->lineEditTime->text();
    QRegExp exp("^(\\d\\d):(\\d\\d):(\\d\\d)[\\t\\s]+(\\d\\d)\\.(\\d\\d)\\.(\\d\\d)");
    if(exp.indexIn(timeStr)!=-1) {
        int hours = exp.cap(1).toInt();
        int mins = exp.cap(2).toInt();
        int secs = exp.cap(3).toInt();
        int date = exp.cap(4).toInt();
        int month = exp.cap(5).toInt();
        int year = exp.cap(6).toInt();
        if((hours<0)||(hours>23)) hours = 0;
        if((mins<0)||(mins>59)) mins = 0;
        if((secs<0)||(secs>59)) secs = 0;
        if((date<1)||(date>31)) date = 1;
        if((month<1)||(month>12)) month=1;
        if((year<0)||(year>99)) year=0;

        QByteArray timeData;

        timeData += secs;
        timeData += mins;
        timeData += hours;
        timeData += 1;// day of week
        timeData += date;
        timeData += month;
        timeData += year;

        QString strData;
        for(int i=0;i<timeData.count();i++) {
           // приведение данных к формату ПЛК
           unsigned char tmp = timeData.at(i)%10 + ((timeData.at(i)/10)<<4);
           strData += QString::number(tmp) + " ";
        }
        var.setValue(strData);
        scheduler.addWriteOperation(var);
        ui->treeWidgetWatch->setFocus();
    }
}

void DebuggerForm::on_lineEditMemStartAddr_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    updateMemViewRequests();
    clearMemViewTable();
}

void DebuggerForm::on_comboBoxMemType_currentIndexChanged(const QString &arg1)
{
    if(arg1.toLower()=="fram") memView->setMemType(MemViewDescription::FRAM);
    if(arg1.toLower()=="ram") memView->setMemType(MemViewDescription::RAM);
    updateMemViewRequests();
    clearMemViewTable();
}

void DebuggerForm::on_pushButtonOpenLastInp_clicked()
{
    if(!scan->isWorking()) {
        QMessageBox::information(this,"сообщение","Необходимо предварительно запустить отладчик");
    }else {
        openInputs(lastOpenInpFile);
    }
}

void DebuggerForm::on_checkBoxQuickWatch_toggled(bool checked)
{
    quick->setActive(checked);
    if(checked) {
        quick->show();
    }else quick->close();
    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}

void DebuggerForm::closeQuickWatchWindow()
{
    if(ui->checkBoxQuickWatch->isChecked()) ui->checkBoxQuickWatch->setChecked(false);
}

void DebuggerForm::on_pushButtonClear_clicked()
{
    int ret = QMessageBox::question(this, tr("Отладчик"),
                                   tr("Вы действительно  хотите удалить все переменные из списка?"));
    if(ret==QMessageBox::Yes) {
        while(ui->treeWidgetWatch->topLevelItemCount()) {
            QTreeWidgetItem *item = ui->treeWidgetWatch->topLevelItem(0);
            on_treeWidgetWatch_itemDoubleClicked(item,2);
        }
    }
}
