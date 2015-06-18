#include "asciidecorator.h"

AsciiDecorator::AsciiDecorator(CommandInterface *cmd):CommandDecorator(cmd)
{

}

AsciiDecorator::~AsciiDecorator()
{

}

bool AsciiDecorator::form(Request &req)
{
    bool res = CommandDecorator::form(req);
    if(res) res = convertToAscii(req);
    return res;
}

bool AsciiDecorator::waitAnAnswer(Request &req, QIODevice &io)
{
    return CommandDecorator::waitAnAnswer(req,io);
}

bool AsciiDecorator::checkAnAnswer(Request &req)
{
    if(convertToBin(req)) {
        return CommandDecorator::checkAnAnswer(req);
    }
    return false;
}

bool AsciiDecorator::convertToAscii(Request &req)
{
    QByteArray binReq = req.getBody();
    req.getBody().clear();
    req.getBody()+='$';
    foreach (quint8 byteCode, binReq) {
        char hi = byteCode >> 4;
        char lo = byteCode & 0x0F;
        if(hi<10) hi=hi+0x30; else hi = hi - 10 + 0x41;
        if(lo<10) lo=lo+0x30; else lo = lo - 10 + 0x41;
        req.getBody()+=hi;
        req.getBody()+=lo;
    }
    req.getBody()+=0x0D;
    return true;
}

bool AsciiDecorator::convertToBin(Request &req)
{
    QByteArray answer = req.getRdData();
    int index = answer.indexOf('!');
    if(index>=0) {
        answer.remove(index,1);
        index = answer.indexOf(0x0d);
        if(index>=0) {
            answer.remove(index,1);
            answer = QByteArray::fromHex(answer);
            req.updateRdData(answer);
            return true;
        }
    }
    return false;
}

