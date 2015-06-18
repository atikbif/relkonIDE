#include "bootmodesetter.h"
#include "AutoSearch/detectedcontroller.h"
#include <QMessageBox>
#include "Protocols/rk.h"
#include "Protocols/asciidecorator.h"
#include <QSerialPort>

using namespace RkProtocol;

BootModeSetter::BootModeSetter(QObject *parent): QObject(parent)
{

}

bool BootModeSetter::setBootMode()
{
    DetectedController* plc = &DetectedController::Instance();
    // проверка результатов последнего поиска
    if(plc->getUartName().isEmpty()) {
        return false;
    }
    // выход если контроллер уже в режиме загрузчика
    if(plc->getBootMode()) return true;

    QSerialPort port(plc->getUartName());
    port.setBaudRate(plc->getBaudrate());
    if(port.open(QSerialPort::ReadWrite)) {
        // стирание кодового слова
        CommandInterface* cmd = new WriteFram();
        if(plc->getAsciiMode()) cmd = new AsciiDecorator(cmd);
        Request req;
        req.setNetAddress(plc->getNetAddress());
        req.setDataNumber(codeWordSize);
        req.setMemAddress(codeWordAddress);
        QByteArray wrData;
        wrData.fill(0,codeWordSize);
        req.setWrData(wrData);
        if(cmd->execute(req,port)) {
            delete cmd;
            // проверка правильного выбора канала
            cmd = new GetCanName();
            if(plc->getAsciiMode()) cmd = new AsciiDecorator(cmd);
            if(cmd->execute(req,port)) {
                QString answer =QString(req.getRdData());
                if(!answer.contains("PROG")) {
                    // неверный выбор канала
                    QMessageBox::warning(nullptr,QString("Переход в режим загрузчика"),answer + "\r\n" + "Вставьте программатор в канал PROG");
                    delete cmd;
                    port.close();
                    return false;
                }else
                {
                    // пересброс контроллера
                    cmd = new ResetController();
                    if(plc->getAsciiMode()) cmd = new AsciiDecorator(cmd);
                    cmd->execute(req,port);
                    delete cmd;
                    port.close();
                    return true;
                }
            }
        }
        QMessageBox::warning(nullptr,QString("Переход в режим загрузчика"),"Контроллер не отвечает на команды");
        delete cmd;
        return false;
    }
    QMessageBox::warning(nullptr,QString("Переход в режим загрузчика"),"Ошибка открытия порта " + port.portName());
    return false;
}

BootModeSetter::~BootModeSetter()
{

}

