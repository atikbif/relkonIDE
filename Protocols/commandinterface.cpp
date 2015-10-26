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
        if(io.waitForReadyRead(1)) io.readAll();
        io.write(req.getBody());
        QIODevice *ptr = &io;
        QSerialPort *port = dynamic_cast<QSerialPort*>(ptr);
        if(port != nullptr) {
            port->flush();
            /*int waitWritePause = 0;
            int cnt = req.getBody().count();
            switch(port->baudRate()) {
                case QSerialPort::Baud4800 :waitWritePause = cnt*2;break;
                case QSerialPort::Baud9600 :waitWritePause = cnt;break;
                case QSerialPort::Baud19200 :waitWritePause = cnt/2;break;
                case QSerialPort::Baud38400 :waitWritePause = cnt/4;break;
                case QSerialPort::Baud57600 :waitWritePause = cnt/6;break;
                case QSerialPort::Baud115200 :waitWritePause = cnt/12;break;
                default: waitWritePause = cnt;break;
            }*/

            int waitWritePause = (req.getBody().count()*12000)/port->baudRate();
            waitWritePause+=10;
            QThread::msleep(waitWritePause);
        }
        if(waitAnAnswer(req,io)) {
            req.setAnswerData(req.getRdData());
            if(checkAnAnswer(req)) {
                getAnAnswer(req);
                return true;
            }
        }else req.setAnswerData(QByteArray());
    }
    return false;
}

CommandInterface::~CommandInterface()
{

}

