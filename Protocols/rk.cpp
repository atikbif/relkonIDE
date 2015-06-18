#include "rk.h"
#include "checksum.h"

using namespace RkProtocol;

//-------------------------------------------------

GetCoreVersion::GetCoreVersion()
{

}

bool GetCoreVersion::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xA0;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    return true;
}

bool GetCoreVersion::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    answer.chop(2);
    netAddress = answer.at(0);
    answer.remove(0,1);
    req.updateRdData(answer);
    return true;
}

GetCoreVersion::~GetCoreVersion()
{

}

//-------------------------------------------------

GetCpu::GetCpu()
{

}

bool GetCpu::form(Request &req)
{
    Q_UNUSED(req)
    return true;
}

GetCpu::~GetCpu()
{

}

//-------------------------------------------------

WriteFram::WriteFram()
{

}

bool WriteFram::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xE3;
    reqBody += req.getMemAddress() >> 8;
    reqBody += req.getMemAddress() & 0xFF;
    reqBody += req.getDataNumber() >>8;
    reqBody += req.getDataNumber() & 0xFF;
    for(int i=0;i<req.getDataNumber();i++) {
        if(i<req.getWrData().count()) reqBody += req.getWrData().at(i);
        else reqBody+='\0';
    }
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    return true;
}

WriteFram::~WriteFram()
{

}

//-------------------------------------------------

ResetController::ResetController()
{

}

bool ResetController::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xFE;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    return true;
}

ResetController::~ResetController()
{

}

//-------------------------------------------------

GetCanName::GetCanName()
{

}

bool GetCanName::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xA2;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    return true;
}

bool GetCanName::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    answer.chop(2);
    answer.remove(0,2);
    req.updateRdData(answer);
    return true;
}

GetCanName::~GetCanName()
{

}
