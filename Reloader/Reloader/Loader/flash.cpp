#include "flash.h"
#include "AutoSearch/detectedcontroller.h"
#include "Protocols/commandinterface.h"
#include "Protocols/rk.h"
#include <QSerialPort>
#include <Protocols/asciidecorator.h>

using namespace RkProtocol;

bool Flash::testControllerReady()
{
    DetectedController* plc = &DetectedController::Instance();
    // проверка результатов последнего поиска
    if(plc->getUartName().isEmpty()) {
        emit error("Не задано имя COM порта");
        return false;
    }
    if(plc->getBootMode()){
        emit error("Контроллер ожидает загрузки программы. Чтение/запись настроек невозможны.");
        return false;
    }
    return true;
}

Flash::Flash(QObject *parent):QObject(parent),stopCmd(false)
{

}

Flash::~Flash()
{

}

void Flash::startRead()
{
    bool errFlag = false;

    QByteArray rxData(248*1024,'\0');
    DetectedController* plc = &DetectedController::Instance();
    if(!testControllerReady()) return;

    QSerialPort port(plc->getUartName());
    port.setBaudRate(plc->getBaudrate());
    if(port.open(QSerialPort::ReadWrite)) {
        float curPercent = 0;
        float stepPercent = 0;
        int reqQuantity = rxData.count()/reqLength;
        if(rxData.count()%reqLength) reqQuantity++;

        stepPercent = 100/(float)reqQuantity;
        int currentLength=0;
        for(int i=0;i<reqQuantity;i++) {
            CommandInterface* cmd = new ReadFlash();
            if(plc->getAsciiMode()) cmd = new AsciiDecorator(cmd);
            Request req;
            req.setNetAddress(plc->getNetAddress());
            int offset = reqLength*i;
            if(rxData.count()<offset+reqLength) currentLength = rxData.count() - offset;
            else currentLength = reqLength;
            req.setDataNumber(currentLength);
            req.setMemAddress(0x2000 + offset);
            errFlag = true;
            for(int j=0;j<3;j++) {
                mutex.lock();
                if(stopCmd) {port.close();mutex.unlock();return;}
                mutex.unlock();
                if(cmd->execute(req,port)==true) {errFlag=false;break;}
            }
            if(errFlag){
                emit error("Ошибка чтения FRAM памяти контроллера");
                delete cmd;
                break;
            }
            rxData.replace(offset,reqLength,req.getRdData());
            delete cmd;
            curPercent+=stepPercent;
            emit percentUpdate(curPercent);
        }
    }else emit error("Ошибка открытия порта "+plc->getUartName());
    if(errFlag==false) emit readFinished(rxData);
}

void Flash::stopProcess()
{
    QMutexLocker locker(&mutex);
    stopCmd = true;
}

