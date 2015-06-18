#include "scanuart.h"
#include <QMutexLocker>
#include <QThread>
#include "Protocols/rk.h"
#include "Protocols/asciidecorator.h"

using namespace RkProtocol;


ScanUART::ScanUART(QObject *parent) : QObject(parent),pName(""),stopCmd(false),startCmd(false)
{

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
    float stepWidth = 100.0/(baudTable.count()*2);
    float currentPercent=0;

    DetectedController* contr = &DetectedController::Instance();
    if(contr->getBaudrate()) {
        // первой скоростью всегда должна быть 115200
        // связано с особенностями работы загрузчика контроллера
        baudTable.removeAll(contr->getBaudrate());
        if(contr->getBaudrate()!=115200) baudTable.insert(1,contr->getBaudrate());
        else baudTable.insert(0,contr->getBaudrate());
    }

    QSerialPort port(pName);
    port.open(QSerialPort::ReadWrite);

    for(int i=0;i<baudTable.count();i++) {

        Request req;
        req.setNetAddress(0x00);

        port.setBaudRate(baudTable.at(i));
        CommandInterface* cmdBin = new GetCoreVersion();
        CommandInterface* cmdAscii = new AsciiDecorator(cmdBin);
        QVector<CommandInterface*> cmdList {cmdBin, cmdAscii};
        bool foundFlag = false;
        foreach(CommandInterface* cmd, cmdList) {
            if(cmd->execute(req,port)){
                contr->setBaudrate(baudTable.at(i));
                if(QString(req.getRdData()).contains("Relkon")) contr->setBootMode(false);
                else contr->setBootMode(true);
                if(dynamic_cast<AsciiDecorator*>(cmd)) contr->setAsciiMode(true);
                else contr->setAsciiMode(false);
                GetCoreVersion* coreCmd = dynamic_cast<GetCoreVersion*>(cmdBin);
                if(coreCmd) contr->setNetAddress(coreCmd->getNetAddress());
                else contr->setNetAddress(0);
                contr->setUartName(pName);

                emit plcHasBeenFound(contr);
                foundFlag = true;
                break;
            }
            currentPercent+=stepWidth;
            emit percentUpdate(currentPercent);

        }
        if(foundFlag) break;
        delete cmdAscii; // cmdBin удаляется декоратором
        locker.relock();
        if(stopCmd) break;
        locker.unlock();
    }
    port.close();
}

void ScanUART::stopScan()
{
    QMutexLocker locker(&mutex);
    stopCmd = true;
}

