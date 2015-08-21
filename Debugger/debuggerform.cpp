#include "debuggerform.h"
#include "ui_debuggerform.h"

#include "namesortiterator.h"
#include <QMenu>
#include <QStringList>
#include <QLineEdit>
#include "vartomemconnector.h"
#include "varbytesvalueconverter.h"
#include "varparser.h"
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


void DebuggerForm::saveView()
{
    QFile file(RCompiler::getDebugFileName());
    if(file.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Debugger");

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
    QString fName = RCompiler::getDebugFileName();
    QFile file(fName);
    if (!file.open(QIODevice::ReadOnly)) return;
    if (!doc.setContent(&file)) {
        return;
    }

    QHash<QString,QString> fullNames;
    foreach (QTreeWidgetItem* item, idWidgetItem.values()) {
       QString fName = item->toolTip(0);
       fullNames.insert(fName,idWidgetItem.key(item));
    }

    QDomNodeList vars = doc.elementsByTagName("var");

    for(int i=0;i<vars.count();i++) {
        QDomNode n = vars.item(i);
        QDomElement e = n.toElement();
        if(!e.isNull()) {
            QString fullName = e.attribute("name");
            QString newId = fullNames.value(fullName);

            if(!newId.isEmpty()) {
                VarItem var = varOwner.getVarByID(newId);
                QStringList sList;
                QString varName;

                QStringList fNameList = fullName.split('.');
                fNameList.removeFirst();fNameList.removeFirst();
                foreach (QString s, fNameList) {
                  varName += "." + s;
                }
                varName.remove(0,1);

                sList << varName << "" << "" << "0x"+QString::number(var.getMemAddress(),16).toUpper() << var.getDataType();
                QTreeWidgetItem* newItem = new QTreeWidgetItem(sList);
                idActiveWidgetItem.insert(newId,newItem);
                var.setPriority(1);
                newItem->setToolTip(0,fullName);
                ui->treeWidgetWatch->addTopLevelItem(newItem);
                ui->treeWidgetWatch->setItemWidget(newItem,5,new QLineEdit(e.attribute("comment"),ui->treeWidgetWatch));
                scheduler.addReadOperation(var);
            }
        }
    }
    scheduler.schedule();

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
}

void DebuggerForm::clearView()
{
    idActiveWidgetItem.clear();
    ui->treeWidgetWatch->clear();
    scheduler.clear();
    foreach (QLineEdit* ptr, ioComments.values()) {
       ptr->setText("");
    }
}

void DebuggerForm::createTree()
{
    ui->treeWidgetMain->clear();
    varOwner.generateVarsTree();
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
                QTreeWidgetItem* curItem = new QTreeWidgetItem(&item);
                curItem->setText(0,varOwner.getVarByID(curPos).getName());
                curItem->setText(1,varOwner.getVarByID(curPos).getDataType());
                if(item.toolTip(0).isEmpty())
                curItem->setToolTip(0,item.text(0)+"."+curItem->text(0));
                else curItem->setToolTip(0,item.toolTip(0)+"."+curItem->text(0));
                if(iter->isNode()) {
                    treeBuilder(curPos,*curItem);
                    iter->goToID(curPos);
                }
                else idWidgetItem.insert(curPos,curItem);
                iter->next();
            }
        }
    }/*else {
        QTreeWidgetItem* singleItem = new QTreeWidgetItem(&item);
        singleItem->setText(0,varOwner.getVarByID(iter->currentID()).getName());
        singleItem->setText(1,varOwner.getVarByID(iter->currentID()).getDataType());
        idWidgetItem.insert(iter->currentID(),singleItem);
    }*/
}

DebuggerForm::DebuggerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebuggerForm)
{
    scan = nullptr;
    iter = nullptr;
    ui->setupUi(this);
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

    buildIO();

}

DebuggerForm::~DebuggerForm()
{
    delete ui;
    delete iter;
    delete scan;
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
    // удаление переменной из дерева просмотра
    Q_UNUSED(column)
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
void DebuggerForm::on_startButton_clicked()
{

    if(ui->radioButtonUDP->isChecked()) {
        QMessageBox::warning(this,"Ограничение отладчика","В данный момент работа по протоколу UDP не доступна.\n");
    }else {
        DebuggerSettings settings;
        settings.setPortName(ui->comboBoxCOM->currentText());
        settings.setProtocol(ui->comboBoxProtocol->currentText());
        settings.setBaudrate(ui->comboBoxSpeed->currentText().toInt());
        settings.setNetAddress(ui->spinBoxNetAddress->value());
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
}

void DebuggerForm::on_stopButton_clicked()
{
    scan->stopDebugger();
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
        if(ui->tabWidget->currentIndex()==1) {
            if(idWidgetItem.contains(id)) {
                VarItem var = varOwner.getVarByID(id);
                if(var.getMemType()=="IO") {
                    if(ioHash.contains(var.getMemAddress())) {
                        QList<BitIO*> ptrList = ioHash.values(var.getMemAddress());
                        QByteArray data = memStor.getData(var.getMemType(),var.getMemAddress(),1);
                        foreach (BitIO* ptr, ptrList) {
                            bool state = data[0]&1<<ptr->getBitNum();
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
                        if(ptr->getName().contains("ADC")) txtValue+=":"+QString::number(value>>8);
                        ptr->getLcdNum()->setText(txtValue);

                        if(!ptr->getSlider()->hasFocus()) ptr->getSlider()->setValue(value);
                    }
                }
            }
        }else if(ui->tabWidget->currentIndex()==0) {

            if(idActiveWidgetItem.contains(id)) {
                QTreeWidgetItem* item = idActiveWidgetItem.value(id);
                VarItem var = varOwner.getVarByID(id);
                int varSize=VarBytesValueConverter::getVarSize(var.getDataType());
                if(varSize) {
                    QByteArray data = memStor.getData(var.getMemType(),var.getMemAddress(),varSize);
                    if(data.count()==varSize) {
                        QString value="";
                        for(int i=0;i<varSize;i++) {
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
    }
}

void DebuggerForm::updateCorrErrAnswerCount(int cnt, bool correctFlag)
{
    if(correctFlag) ui->lcdNumberCorrect->display(cnt);
    else ui->lcdNumberError->display(cnt);
    //ui->textBrowserRequests->setText(QString::number(cnt)+"\r\n");
}

void DebuggerForm::getMessageFromDebugProcess(QString message)
{
    QString txt = ui->textBrowserRequests->toPlainText();
    QStringList sList = txt.split("\n");
    //sList.removeDuplicates();
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
    QWidget *client = new QWidget(this);
    QGridLayout *grLayout= new QGridLayout(client);

    for(int i=0;i<6;i++) {
        QString name;
        if(i<4) name = "IN"+QString::number(i);
        else name = "DIN" + QString::number(i);
        QGroupBox *boxIn = new QGroupBox(name);
        QVBoxLayout *vLayoutIn = new QVBoxLayout(boxIn);
        for(int j=0;j<8;j++) {
            QHBoxLayout *hLayout = new QHBoxLayout();
            QPushButton *b = new QPushButton();
            b->setStyleSheet("border: 2px solid #8f8f91;border-radius: 10px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
            b->setFixedSize(20,20);
            connect(b,SIGNAL(clicked()),this,SLOT(inOutClicked()));
            QLineEdit *e = new QLineEdit();
            hLayout->addWidget(b);
            hLayout->addWidget(e);
            vLayoutIn->addLayout(hLayout);
            BitIO *bitDef = new BitIO();
            bitDef->setName(name+"."+QString::number(j));
            bitDef->setBitNum(j);
            bitDef->setButton(b);
            bitDef->setComment(e);
            bitDef->setAddress(i);
            bitDef->setState(false);
            ioHash.insert(bitDef->getAddress(),bitDef);
            ioComments.insert(bitDef->getName(),e);
        }
        boxIn->setLayout(vLayoutIn);
        grLayout->addWidget(boxIn,1,i+1);

        if(i<4) name = "OUT"+QString::number(i);
        else name = "DOUT" + QString::number(i);
        QGroupBox *boxOut = new QGroupBox(name);
        QVBoxLayout *vLayoutOut = new QVBoxLayout(boxOut);
        for(int j=0;j<8;j++) {
            QHBoxLayout *hLayout = new QHBoxLayout();
            QPushButton *b = new QPushButton();
            b->setStyleSheet("border: 2px solid #8f8f91;border-radius: 10px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
            b->setFixedSize(20,20);
            connect(b,SIGNAL(clicked()),this,SLOT(inOutClicked()));
            QLineEdit *e = new QLineEdit();
            hLayout->addWidget(b);
            hLayout->addWidget(e);
            vLayoutOut->addLayout(hLayout);
            BitIO *bitDef = new BitIO();
            bitDef->setName(name+"."+QString::number(j));
            bitDef->setBitNum(j);
            bitDef->setButton(b);
            bitDef->setComment(e);
            bitDef->setAddress(i+0x06);
            bitDef->setState(false);
            ioHash.insert(bitDef->getAddress(),bitDef);
            ioComments.insert(bitDef->getName(),e);
        }
        boxOut->setLayout(vLayoutOut);
        grLayout->addWidget(boxOut,2,i+1);
    }

    for(int i=0;i<32;i++) {
        QString name;
        name = "IN"+QString::number(i+4);
        QGroupBox *boxIn = new QGroupBox(name);
        QVBoxLayout *vLayoutIn = new QVBoxLayout(boxIn);
        for(int j=0;j<4;j++) {
            QHBoxLayout *hLayout = new QHBoxLayout();
            QPushButton *b = new QPushButton();
            b->setStyleSheet("border: 2px solid #8f8f91;border-radius: 10px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
            b->setFixedSize(20,20);
            connect(b,SIGNAL(clicked()),this,SLOT(inOutClicked()));
            QLineEdit *e = new QLineEdit();
            hLayout->addWidget(b);
            hLayout->addWidget(e);
            vLayoutIn->addLayout(hLayout);
            BitIO *bitDef = new BitIO();
            bitDef->setName(name+"."+QString::number(j));
            bitDef->setBitNum(j);
            bitDef->setButton(b);
            bitDef->setComment(e);
            bitDef->setAddress(0x24+i);
            bitDef->setState(false);
            ioHash.insert(bitDef->getAddress(),bitDef);
            ioComments.insert(bitDef->getName(),e);
        }
        boxIn->setLayout(vLayoutIn);
        grLayout->addWidget(boxIn,3+(i/6)*2,(i%6)+1);

        name = "OUT"+QString::number(i+4);
        QGroupBox *boxOut = new QGroupBox(name);
        QVBoxLayout *vLayoutOut = new QVBoxLayout(boxOut);
        for(int j=0;j<4;j++) {
            QHBoxLayout *hLayout = new QHBoxLayout();
            QPushButton *b = new QPushButton();
            b->setStyleSheet("border: 2px solid #8f8f91;border-radius: 10px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
            b->setFixedSize(20,20);
            connect(b,SIGNAL(clicked()),this,SLOT(inOutClicked()));
            QLineEdit *e = new QLineEdit();
            hLayout->addWidget(b);
            hLayout->addWidget(e);
            vLayoutOut->addLayout(hLayout);
            BitIO *bitDef = new BitIO();
            bitDef->setName(name+"."+QString::number(j));
            bitDef->setBitNum(j);
            bitDef->setButton(b);
            bitDef->setComment(e);
            bitDef->setAddress(i+0x44);
            bitDef->setState(false);
            ioHash.insert(bitDef->getAddress(),bitDef);
            ioComments.insert(bitDef->getName(),e);
        }
        boxOut->setLayout(vLayoutOut);
        grLayout->addWidget(boxOut,4+(i/6)*2,(i%6)+1);
    }
    client->setLayout(grLayout);
    ui->scrollArea->setWidget(client);

    QWidget *clientAn = new QWidget(this);
    QVBoxLayout *vLayoutAn= new QVBoxLayout(clientAn);

    QGroupBox *boxAdc = new QGroupBox("ADC1..8");
    QVBoxLayout *vLayoutAdc = new QVBoxLayout(boxAdc);
    for(int i=1;i<9;i++) {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *name = new QLabel("ADC"+QString::number(i)+":");
        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setMaximum(65535);
        slider->setMinimum(0);
        connect(slider,SIGNAL(sliderReleased()),this,SLOT(anInOutClicked()));
        QLineEdit *number = new QLineEdit();
        number->setStyleSheet("border: 2px solid gray;"
                              "border-radius: 10px;"
                              "padding: 0 8px;"
                              "background: #e0e0f0;");
        number->setReadOnly(true);
        QLineEdit *comment = new QLineEdit();
        hLayout->addWidget(name,0);
        hLayout->addWidget(slider,1);
        hLayout->addWidget(number,1);
        hLayout->addWidget(comment,1);
        vLayoutAdc->addLayout(hLayout);
        AnIO *aDef = new AnIO();
        aDef->setName("ADC"+QString::number(i));
        aDef->setAddress(0x0C+(i-1)*2);
        aDef->setComment(comment);
        aDef->setLcdNum(number);
        aDef->setSlider(slider);
        anIoHash.insert(aDef->getAddress(),aDef);
        ioComments.insert(aDef->getName(),comment);
    }
    boxAdc->setLayout(vLayoutAdc);
    vLayoutAn->addWidget(boxAdc);

    QGroupBox *boxDac = new QGroupBox("DAC1..4");
    QVBoxLayout *vLayoutDac = new QVBoxLayout(boxDac);
    for(int i=1;i<5;i++) {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *name = new QLabel("DAC"+QString::number(i)+":");
        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setMaximum(65535);
        slider->setMinimum(0);
        connect(slider,SIGNAL(sliderReleased()),this,SLOT(anInOutClicked()));
        QLineEdit *number = new QLineEdit();
        number->setStyleSheet("border: 2px solid gray;"
                              "border-radius: 10px;"
                              "padding: 0 8px;"
                              "background: #e0e0f0;");
        number->setReadOnly(true);
        QLineEdit *comment = new QLineEdit();
        hLayout->addWidget(name,0);
        hLayout->addWidget(slider,1);
        hLayout->addWidget(number,1);
        hLayout->addWidget(comment,1);
        vLayoutDac->addLayout(hLayout);
        AnIO *aDef = new AnIO();
        aDef->setName("DAC"+QString::number(i));
        aDef->setAddress(0x1C+(i-1)*2);
        aDef->setComment(comment);
        aDef->setLcdNum(number);
        aDef->setSlider(slider);
        anIoHash.insert(aDef->getAddress(),aDef);
        ioComments.insert(aDef->getName(),comment);
    }
    boxDac->setLayout(vLayoutDac);
    vLayoutAn->addWidget(boxDac);

    QGroupBox *boxAdcMmb = new QGroupBox("Matchbox ADC");
    QVBoxLayout *vLayoutAdcMmb = new QVBoxLayout(boxAdcMmb);
    for(int i=9;i<137;i++) {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *name = new QLabel("ADC"+QString::number(i)+":");
        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setMaximum(65535);
        slider->setMinimum(0);
        connect(slider,SIGNAL(sliderReleased()),this,SLOT(anInOutClicked()));
        //QLCDNumber *number = new QLCDNumber(6);
        //number->setPalette(Qt::darkGray);
        QLineEdit *number = new QLineEdit();
        number->setStyleSheet("border: 2px solid gray;"
                              "border-radius: 10px;"
                              "padding: 0 8px;"
                              "background: #e0e0f0;");
        number->setReadOnly(true);
        QLineEdit *comment = new QLineEdit();
        hLayout->addWidget(name,0);
        hLayout->addWidget(slider,1);
        hLayout->addWidget(number,1);
        hLayout->addWidget(comment,1);
        vLayoutAdcMmb->addLayout(hLayout);
        AnIO *aDef = new AnIO();
        aDef->setName("ADC"+QString::number(i));
        aDef->setAddress(0x64+(i-9)*2);
        aDef->setComment(comment);
        aDef->setLcdNum(number);
        aDef->setSlider(slider);
        anIoHash.insert(aDef->getAddress(),aDef);
        ioComments.insert(aDef->getName(),comment);
    }
    boxAdcMmb->setLayout(vLayoutAdcMmb);
    vLayoutAn->addWidget(boxAdcMmb);

    QGroupBox *boxDacMmb = new QGroupBox("Matchbox DAC");
    QVBoxLayout *vLayoutDacMmb = new QVBoxLayout(boxDacMmb);
    for(int i=5;i<69;i++) {
        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *name = new QLabel("DAC"+QString::number(i)+":");
        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setMaximum(65535);
        slider->setMinimum(0);
        connect(slider,SIGNAL(sliderReleased()),this,SLOT(anInOutClicked()));
        QLineEdit *number = new QLineEdit();
        number->setStyleSheet("border: 2px solid gray;"
                              "border-radius: 10px;"
                              "padding: 0 8px;"
                              "background: #e0e0f0;");
        number->setReadOnly(true);
        QLineEdit *comment = new QLineEdit();
        hLayout->addWidget(name,0);
        hLayout->addWidget(slider,1);
        hLayout->addWidget(number,1);
        hLayout->addWidget(comment,1);
        vLayoutDacMmb->addLayout(hLayout);
        AnIO *aDef = new AnIO();
        aDef->setName("DAC"+QString::number(i));
        aDef->setAddress(0x164+(i-5)*2);
        aDef->setComment(comment);
        aDef->setLcdNum(number);
        aDef->setSlider(slider);
        anIoHash.insert(aDef->getAddress(),aDef);
        ioComments.insert(aDef->getName(),comment);
    }
    boxDacMmb->setLayout(vLayoutDacMmb);
    vLayoutAn->addWidget(boxDacMmb);



    clientAn->setLayout(vLayoutAn);
    ui->scrollArea_2->setWidget(clientAn);
}

void DebuggerForm::on_pushButtonCOMUpdate_clicked()
{
    updateComPortList();
}

void DebuggerForm::on_pushButtonAutoSearch_clicked()
{
    int progAddr = ui->spinBoxNetAddress->value();
    ScanGUI gui(progAddr,this);
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
    if(ui->checkBoxLog->isChecked()) ui->textBrowserRequests->setVisible(true);
    else ui->textBrowserRequests->setVisible(false);
}

void DebuggerForm::on_pushButtonTimeWrite_clicked()
{
    // Синхронизация времени
    VarItem var;
    var.setMemAddress(0);
    var.setMemType("TIME");
    var.setDataType("time");
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
            if(var.getReadOnly()==false) {
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

}

void DebuggerForm::writeVar()
{
    // запись переменной
    if(wrVar.getBitNum()>=0) {
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
                QByteArray data = memStor.getData("IO",ptr->getAddress(),1);
                if(data.count()) {
                    quint8 byte = data[0] ^ (1<<ptr->getBitNum());
                    var.setValue(QString::number(byte));
                    var.setDataType("unsigned char");
                    var.setMemAddress(ptr->getAddress());
                    var.setMemType("IO");
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
               // поменять старший младший байт местами
               //quint8 hByte = byte >> 8;
               //byte = (byte << 8) | hByte;

               var.setValue(QString::number(byte));
               var.setDataType("unsigned short");
               var.setMemAddress(ptr->getAddress());
               var.setMemType("IO");
               var.setPriority(1);
               scheduler.addWriteOperation(var);

               break;
           }
        }
    }
}


void DebuggerForm::on_tabWidget_currentChanged(int index)
{
    if(index==0) {
        scheduler.clear();
        foreach (QString id, idActiveWidgetItem.keys()) {
            VarItem var = varOwner.getVarByID(id);
            var.setPriority(1);
            scheduler.addReadOperation(var);
        }
        scheduler.schedule();
    }else if(index==1) {
        scheduler.clear();
        for(int i=0;i<484;i++) {
            VarItem var;
            var.setDataType("unsigned char");
            var.setMemType("IO");
            var.setPriority(1);
            var.setMemAddress(i);
            scheduler.addReadOperation(var);
        }
        scheduler.schedule();
    }else if(index==2) {
        scheduler.clear();
        scheduler.schedule();
    }

}
