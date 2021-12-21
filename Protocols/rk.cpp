#include "rk.h"
#include "checksum.h"
#include <QThread>
#include "Debugger/memstorage.h"

using namespace RkProtocol;

//-------------------------------------------------

GetCoreVersion::GetCoreVersion():netAddress(1)
{

}

bool GetCoreVersion::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xA0u;
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
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xA1u;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    return true;
}

bool GetCpu::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    answer.chop(2);
    answer.remove(0,2);
    req.updateRdData(answer);
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
    reqBody += 0xE3u;
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
    req.insParam("rw","write");
    req.insParam("mem","FRAM");
    return true;
}

bool WriteFram::waitAnAnswer(Request &req, QIODevice &io)
{
    static const int maxCnt = 500; // ограничение ожидания ответа при длительном входящем потоке данных
    if(io.isOpen()){
        QByteArray answer;
        if(io.waitForReadyRead(200)){
            int cnt=0;
            answer+=io.readAll();
            while(io.waitForReadyRead(10)) {
                answer+=io.readAll();
                cnt++;if(cnt>=maxCnt) break;
            }
        }
        req.updateRdData(answer);
        if(answer.count()) return true;
    }
    return false;
}

WriteFram::~WriteFram()
{

}

//-------------------------------------------------

WriteEE::WriteEE()
{

}

bool WriteEE::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xE6u;
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
    req.insParam("rw","write");
    req.insParam("mem","EE");
    return true;
}

bool WriteEE::waitAnAnswer(Request &req, QIODevice &io)
{
    static const int maxCnt = 500; // ограничение ожидания ответа при длительном входящем потоке данных
    if(io.isOpen()){
        QByteArray answer;
        if(io.waitForReadyRead(200)){
            int cnt=0;
            answer+=io.readAll();
            while(io.waitForReadyRead(10)) {
                answer+=io.readAll();
                cnt++;if(cnt>=maxCnt) break;
            }
        }
        req.updateRdData(answer);
        if(answer.count()) return true;
    }
    return false;
}

WriteEE::~WriteEE()
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
    reqBody += 0xFEu;
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
    reqBody += 0xA2u;
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

//-------------------------------------------------


ReadFram::ReadFram()
{

}

bool ReadFram::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xD3u;
    reqBody += req.getMemAddress() >> 8;
    reqBody += req.getMemAddress() & 0xFF;
    reqBody += req.getDataNumber() >>8;
    reqBody += req.getDataNumber() & 0xFF;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    req.insParam("rw","read");
    req.insParam("mem","FRAM");
    return true;
}

bool ReadFram::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    answer.chop(2);
    answer.remove(0,1);
    req.updateRdData(answer);
    return true;
}

bool ReadFram::waitAnAnswer(Request &req, QIODevice &io)
{
    static const int maxCnt = 500; // ограничение ожидания ответа при длительном входящем потоке данных
    if(io.isOpen()){
        QByteArray answer;
        if(io.waitForReadyRead(200)){
            int cnt=0;
            answer+=io.readAll();
            while(io.waitForReadyRead(10)) {
                answer+=io.readAll();
                cnt++;if(cnt>=maxCnt) break;
            }
        }
        req.updateRdData(answer);
        if(answer.count()) return true;
    }
    return false;
}

ReadFram::~ReadFram()
{

}

//-------------------------------------------------


ReadEE::ReadEE()
{

}

bool ReadEE::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xD6u;
    reqBody += req.getMemAddress() >> 8;
    reqBody += req.getMemAddress() & 0xFF;
    reqBody += req.getDataNumber() >>8;
    reqBody += req.getDataNumber() & 0xFF;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    req.insParam("rw","read");
    req.insParam("mem","EE");
    return true;
}

bool ReadEE::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    answer.chop(2);
    answer.remove(0,1);
    req.updateRdData(answer);
    return true;
}

bool ReadEE::waitAnAnswer(Request &req, QIODevice &io)
{
    static const int maxCnt = 500; // ограничение ожидания ответа при длительном входящем потоке данных
    if(io.isOpen()){
        QByteArray answer;
        if(io.waitForReadyRead(200)){
            int cnt=0;
            answer+=io.readAll();
            while(io.waitForReadyRead(10)) {
                answer+=io.readAll();
                cnt++;if(cnt>=maxCnt) break;
            }
        }
        req.updateRdData(answer);
        if(answer.count()) return true;
    }
    return false;
}

ReadEE::~ReadEE()
{

}

//-------------------------------------------------

ReadRam::ReadRam()
{

}

bool ReadRam::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();

    if(req.getMemAddress()>65535) {
        reqBody += 0xDFu;
        reqBody += (req.getMemAddress() >> 16) & 0xFF;
        reqBody += (req.getMemAddress() >> 8) & 0xFF;
        reqBody += req.getMemAddress() & 0xFF;
    }else {
        reqBody += 0xD4u;
        reqBody += (req.getMemAddress() >> 8) & 0xFF;
        reqBody += req.getMemAddress() & 0xFF;
    }
    reqBody += req.getDataNumber() >>8;
    reqBody += req.getDataNumber() & 0xFF;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    req.insParam("rw","read");
    req.insParam("mem","RAM");
    return true;
}

bool ReadRam::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    answer.chop(2);
    answer.remove(0,1);
    req.updateRdData(answer);
    return true;
}

ReadRam::~ReadRam()
{

}

//-------------------------------------------------

ReadTime::ReadTime()
{

}

bool ReadTime::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xD1u;
    reqBody += req.getMemAddress() & 0xFF;
    reqBody += req.getDataNumber() & 0xFF;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    req.insParam("rw","read");
    req.insParam("mem",MemStorage::timeMemName);
    return true;
}

bool ReadTime::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    answer.chop(2);
    answer.remove(0,1);
    req.updateRdData(answer);
    return true;
}

ReadTime::~ReadTime()
{

}

//-------------------------------------------------

WriteTime::WriteTime()
{

}

bool WriteTime::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xE1u;
    reqBody += req.getMemAddress() & 0xFF;
    reqBody += req.getDataNumber() & 0xFF;
    for(int i=0;i<req.getDataNumber();i++) {
        if(i<req.getWrData().count()) reqBody += req.getWrData().at(i);
        else reqBody+='\0';
    }
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    req.insParam("rw","write");
    req.insParam("mem",MemStorage::timeMemName);
    return true;
}

bool WriteTime::waitAnAnswer(Request &req, QIODevice &io)
{
    static const int maxCnt = 500; // ограничение ожидания ответа при длительном входящем потоке данных
    if(io.isOpen()){
        QByteArray answer;
        if(io.waitForReadyRead(200)){
            int cnt=0;
            answer+=io.readAll();
            while(io.waitForReadyRead(10)) {
                answer+=io.readAll();
                cnt++;if(cnt>=maxCnt) break;
            }
        }
        req.updateRdData(answer);
        if(answer.count()) return true;
    }
    return false;
}

WriteTime::~WriteTime()
{

}


WriteRam::WriteRam()
{

}

bool WriteRam::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    if(req.getMemAddress()>65535) {
        reqBody += 0xEFu;
        reqBody += (req.getMemAddress() >> 16) & 0xFF;
        reqBody += (req.getMemAddress() >> 8) & 0xFF;
        reqBody += req.getMemAddress() & 0xFF;
    }else {
        reqBody += 0xE4u;
        reqBody += req.getMemAddress() >> 8;
        reqBody += req.getMemAddress() & 0xFF;
    }

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
    req.insParam("rw","write");
    req.insParam("mem","RAM");
    return true;
}

WriteRam::~WriteRam()
{

}


ReadIO::ReadIO()
{

}

bool ReadIO::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xB0u;
    reqBody += req.getMemAddress() >> 8;
    reqBody += req.getMemAddress() & 0xFF;
    reqBody += req.getDataNumber() >>8;
    reqBody += req.getDataNumber() & 0xFF;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    req.insParam("rw","read");
    req.insParam("mem","IO");
    return true;
}

bool ReadIO::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    answer.chop(2);
    answer.remove(0,1);
    req.updateRdData(answer);
    return true;
}

ReadIO::~ReadIO()
{

}


ReadDispRam::ReadDispRam()
{

}

bool ReadDispRam::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xD0u;
    reqBody += req.getMemAddress() & 0xFF;
    reqBody += req.getDataNumber() & 0xFF;
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    req.insParam("rw","read");
    req.insParam("mem","USER");
    return true;
}

bool ReadDispRam::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    answer.chop(2);
    answer.remove(0,1);
    req.updateRdData(answer);
    return true;
}

ReadDispRam::~ReadDispRam()
{

}


WriteDispRam::WriteDispRam()
{

}

bool WriteDispRam::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xE0u;
    reqBody += req.getMemAddress() & 0xFF;
    reqBody += req.getDataNumber() & 0xFF;
    for(int i=0;i<req.getDataNumber();i++) {
        if(i<req.getWrData().count()) reqBody += req.getWrData().at(i);
        else reqBody+='\0';
    }
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    req.insParam("rw","write");
    req.insParam("mem","USER");
    return true;
}

WriteDispRam::~WriteDispRam()
{

}


WriteIO::WriteIO()
{

}

bool WriteIO::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xB1u;
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
    req.insParam("rw","write");
    req.insParam("mem","IO");
    return true;
}

WriteIO::~WriteIO()
{

}

bool F7toBootMode::form(Request &req)
{
    QByteArray reqBody = req.getBody();
    reqBody.clear();
    reqBody += req.getNetAddress();
    reqBody += 0xECu;
    // two bytes id
    reqBody += '\0';
    reqBody += '\0';
    int crc = CheckSum::getCRC16(reqBody);
    reqBody += crc&0xFF;
    reqBody += (crc>>8)&0xFF;
    req.getBody() = reqBody;
    return true;
}

bool F7toBootMode::getAnAnswer(Request &req)
{
    QByteArray answer = req.getRdData();
    req.updateRdData(answer);
    return true;
}
