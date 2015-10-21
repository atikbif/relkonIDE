#include "udpdecorator.h"
#include <QThread>
#include <QUdpSocket>

UdpDecorator::UdpDecorator(CommandInterface *cmd):CommandDecorator(cmd)
{

}

bool UdpDecorator::waitAnAnswer(Request &req, QIODevice &io)
{
    return CommandDecorator::waitAnAnswer(req,io);
}

bool UdpDecorator::checkAnAnswer(Request &req)
{
    return CommandDecorator::checkAnAnswer(req);
}

bool UdpDecorator::getAnAnswer(Request &req)
{
    return CommandDecorator::getAnAnswer(req);
}

UdpDecorator::~UdpDecorator()
{

}

bool UdpDecorator::execute(Request &req, QIODevice &io)
{
    form(req);
    io.readAll();
    io.write(req.getBody());
    QByteArray rxData;
    int cnt = 0;
    while(1) {
        QThread::currentThread()->msleep(15);
        rxData = io.readAll();
        if(rxData.count()) {
            req.updateRdData(rxData);
            req.setAnswerData(rxData);
            if(checkAnAnswer(req)) {
                getAnAnswer(req);
                return true;
            }
        }else cnt++;
        if(cnt>=20) {
            req.setAnswerData(QByteArray());
            break;
        }
    }
    return false;
}

