#include "commandinterface.h"
#include <QThread>
#include <QSerialPort>

CommandInterface::CommandInterface()
{

}

bool CommandInterface::execute(Request &req, QIODevice &io)
{
    form(req);
    if(io.isOpen()) {
        io.readAll();
        io.write(req.getBody());
        QSerialPort &port = dynamic_cast<QSerialPort&>(io);
        if(&port != nullptr) {
            port.flush();
            int waitWritePause = (req.getBody().count()*12000.0)/port.baudRate();
            waitWritePause+=10;
            QThread::currentThread()->msleep(waitWritePause);
        }
        if(waitAnAnswer(req,io)) {
            if(checkAnAnswer(req)) {
                getAnAnswer(req);
                return true;
            }
        }
    }
    return false;
}

CommandInterface::~CommandInterface()
{

}

