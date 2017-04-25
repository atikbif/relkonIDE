#include "scanuart.h"
#include <QMutexLocker>
#include <QThread>
#include "Protocols/rk.h"
#include "Protocols/asciidecorator.h"
#include <QMessageBox>


using namespace RkProtocol;


bool ScanUART::scan(QSerialPort &port)
{
    bool foundFlag = false;
    SearchController contr;
    float stepWidth = 100.0/(baudTable.count()*2);
    float currentPercent=0;
    for(int i=0;i<baudTable.count();i++) {

        Request req;
        req.setNetAddress(progAddr);

        port.setBaudRate(baudTable.at(i));
        CommandInterface* cmdBin = new GetCoreVersion();
        CommandInterface* cmdAscii = new AsciiDecorator(cmdBin);
        QVector<CommandInterface*> cmdList {cmdBin, cmdAscii};
        foundFlag = false;
        foreach(CommandInterface* cmd, cmdList) {
            if(cmd->execute(req,port)){
                contr.setBaudrate(baudTable.at(i));
                if(QString(req.getRdData()).contains("Relkon")) contr.setBootMode(false);
                else contr.setBootMode(true);
                if(dynamic_cast<AsciiDecorator*>(cmd)) contr.setAsciiMode(true);
                else contr.setAsciiMode(false);
                GetCoreVersion* coreCmd = dynamic_cast<GetCoreVersion*>(cmdBin);
                if(coreCmd) contr.setNetAddress(coreCmd->getNetAddress());
                else contr.setNetAddress(0);
                contr.setUartName(pName);

                // get canal name
                if(contr.getBootMode()==false) {
                    CommandInterface* cmdGetName = new GetCanName();
                    if(contr.getAsciiMode()) cmdGetName = new AsciiDecorator(cmdGetName);
                    if(cmdGetName->execute(req,port)) {
                        contr.setCanName(QString(req.getRdData()).remove("Canal:"));
                    }
                    delete cmdGetName;
                }

                emit percentUpdate(100);
                emit plcHasBeenFound(contr);

                foundFlag = true;


                break;
            }
            currentPercent+=stepWidth;
            emit percentUpdate(currentPercent);

        }
        delete cmdAscii; // cmdBin удаляется декоратором
        mutex.lock();
        if(stopCmd) {mutex.unlock();break;}
        mutex.unlock();
        if(foundFlag) break;
    }
    if(foundFlag) return true;
    return false;
}

bool ScanUART::testBootMode(QSerialPort &port)
{
    bool foundFlag = false;
    SearchController contr;

    Request req;
    req.setNetAddress(0);

    port.setBaudRate(QSerialPort::Baud115200);
    CommandInterface* cmd = new GetCoreVersion();

    if(cmd->execute(req,port)){
        contr.setBaudrate(115200);
        if(QString(req.getRdData()).contains("boot")) contr.setBootMode(true);
        else contr.setBootMode(false);
        contr.setAsciiMode(false);
        contr.setNetAddress(0);
        contr.setUartName(pName);
        if(contr.getBootMode()) {
            emit plcHasBeenFound(contr);
            foundFlag = true;
        }
    }
    delete cmd;
    if(foundFlag) return true;
    return false;
}

void ScanUART::sendAbortCmd(QSerialPort &port)
{
    QByteArray abortCmd;
    abortCmd += 'a';
    port.setBaudRate(QSerialPort::Baud115200);
    port.write(abortCmd);
    port.waitForBytesWritten(100);
    int maxCnt = 20;
    int cnt=0;
    while(port.waitForReadyRead(100)) {
        port.readAll();
        cnt++;if(cnt>=maxCnt) break;
    }
}

ScanUART::ScanUART(QObject *parent) : QObject(parent),pName(""),stopCmd(false),startCmd(false)
{
    progAddr = 0;
}

ScanUART::~ScanUART()
{

}

void ScanUART::startScan(const QString &pName)
{
    baudTable = {115200,19200,9600,38400,57600,4800};
    QMutexLocker locker(&mutex);
    if(startCmd) return;
    if(!this->pName.isEmpty()) return;
    startCmd = true;
    this->pName = pName;
    locker.unlock();

    DetectedController* contr = &DetectedController::Instance();
    if(contr->getBaudrate()) {
        // первой скоростью всегда должна быть 115200
        // связано с особенностями работы загрузчика контроллера
        baudTable.removeAll(contr->getBaudrate());
        if(contr->getBaudrate()!=115200) baudTable.insert(1,contr->getBaudrate());
        else baudTable.insert(0,contr->getBaudrate());
    }

    QSerialPort port(pName);
    if(port.open(QSerialPort::ReadWrite)) {

        sendAbortCmd(port);
        if(testBootMode(port)==false) {
            scan(port);
        }
        port.close();
    }else {
        emit portIsBusy();
    }
}

void ScanUART::stopScan()
{
    QMutexLocker locker(&mutex);
    stopCmd = true;
}

