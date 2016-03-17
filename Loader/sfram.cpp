#include "sfram.h"
#include "AutoSearch/detectedcontroller.h"
#include <QThread>
#include "Protocols/commandinterface.h"
#include "Protocols/asciidecorator.h"
#include "Protocols/rk.h"

using namespace RkProtocol;

void sFram::controllerReset(QSerialPort &port)
{
    CommandInterface* cmd = new ResetController();
    DetectedController* plc = &DetectedController::Instance();
    Request req;
    req.setNetAddress(plc->getNetAddress());
    if(plc->getAsciiMode()) cmd = new AsciiDecorator(cmd);
    if(port.open(QSerialPort::ReadWrite)){
        cmd->execute(req,port);
        port.close();
    }
    delete cmd;
}

bool sFram::testControllerReady()
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

sFram::sFram(QObject *parent) : QObject(parent),stopCmd(false)
{

}

sFram::~sFram()
{

}

void sFram::startWrite(QByteArray data)
{
    bool errFlag = false;
    DetectedController* plc = &DetectedController::Instance();
    if(!testControllerReady()) return;
    QSerialPort port(plc->getUartName());
    port.setBaudRate(plc->getBaudrate());
    if(port.open(QSerialPort::ReadWrite)) {
        float curPercent = 0;
        float stepPercent = 0;

        int reqQuantity = data.count()/reqLength;
        if(data.count()%reqLength) reqQuantity++;

        stepPercent = 100/(float)reqQuantity;
        int currentLength=0;
        for(int i=0;i<reqQuantity;i++) {
            CommandInterface* cmd = new WriteFram();
            if(plc->getAsciiMode()) cmd = new AsciiDecorator(cmd);
            Request req;
            req.setNetAddress(plc->getNetAddress());
            int offset = reqLength*i;
            if(data.count()<offset+reqLength) currentLength = data.count() - offset;
            else currentLength = reqLength;

            req.setDataNumber(currentLength);
            req.setMemAddress(0x7b00 + offset);
            QByteArray wrData = data.mid(offset,reqLength);
            req.setWrData(wrData);
            errFlag = true;
            for(int j=0;j<3;j++) {
                if(cmd->execute(req,port)==true) {errFlag=false;break;}
                mutex.lock();
                if(stopCmd) {port.close();mutex.unlock();return;}
                mutex.unlock();
            }
            if(errFlag){
                emit error("Ошибка записи FRAM памяти контроллера");
                delete cmd;
                break;
            }
            delete cmd;
            curPercent+=stepPercent;
            emit percentUpdate(curPercent);
        }
        port.close();
    }else emit error("Ошибка открытия порта "+plc->getUartName());
    if(errFlag==false) {
        // пересброс контроллера
        controllerReset(port);
        emit writeFinished();
    }
}

void sFram::startRead()
{
    bool errFlag = false;

    QByteArray rxData(2048,'\0');
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
            CommandInterface* cmd = new ReadFram();
            if(plc->getAsciiMode()) cmd = new AsciiDecorator(cmd);
            Request req;
            req.setNetAddress(plc->getNetAddress());
            int offset = reqLength*i;
            if(rxData.count()<offset+reqLength) currentLength = rxData.count() - offset;
            else currentLength = reqLength;
            req.setDataNumber(currentLength);
            req.setMemAddress(0x7b00 + offset);
            errFlag = true;
            for(int j=0;j<3;j++) {
                if(cmd->execute(req,port)==true) {errFlag=false;break;}
                mutex.lock();
                if(stopCmd) {mutex.unlock();return;}
                mutex.unlock();
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

void sFram::stopProcess()
{
    QMutexLocker locker(&mutex);
    stopCmd = true;
}

