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


void DebuggerForm::saveView()
{
    QFile file(RCompiler::getDebugFileName());
    if(file.open(QIODevice::WriteOnly)) {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();

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
}

void DebuggerForm::clearView()
{
    idActiveWidgetItem.clear();
    ui->treeWidgetWatch->clear();
    scheduler.clear();
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
}

DebuggerForm::~DebuggerForm()
{
    delete ui;
    delete iter;
    delete scan;
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
    if(sList.count()>=15) {
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
