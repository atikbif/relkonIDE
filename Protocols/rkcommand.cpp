#include "rkcommand.h"
#include <QThread>
#include "checksum.h"

RkCommand::RkCommand()
{

}

bool RkCommand::send(Request &req, QIODevice &io)
{
    form(req);
    if(io.isOpen()) {
        io.write(req.getBody());
        io.waitForBytesWritten(100);
        if(waitAnAnswer(req,io)) {
            if(checkAnAnswer(req)) {
                getAnAnswer(req);
                return true;
            }
        }
    }
    return false;
}

RkCommand::~RkCommand()
{

}

bool RkCommand::waitAnAnswer(Request &req, QIODevice &io)
{
    static const int maxCnt = 5; // ограничение ожидания ответа при длительном входящем потоке данных
    if(io.isOpen()){
        QByteArray answer;
        int cnt=0;
        while(io.waitForReadyRead(100)) {
            answer+=io.readAll();
            cnt++;if(cnt>=maxCnt) break;
        }
        req.updateRdData(answer);
        if(answer.count()) return true;
    }
    return false;
}

bool RkCommand::checkAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    if(CheckSum::getCRC16(answer)==0) return true;
    return false;
}

bool RkCommand::getAnAnswer(Request &req)
{
    Q_UNUSED(req)
    return true;
}

