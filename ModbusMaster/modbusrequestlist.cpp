#include "modbusrequestlist.h"

namespace modbusMaster {

using std::sort;

const unsigned char ModbusRequestList::crc16H[256] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

const unsigned char ModbusRequestList::crc16L[256] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

void ModbusRequestList::setMaxSpaceLength(int value)
{
    maxSpaceLength = value;
}

void ModbusRequestList::setMaxLength(int value)
{
    maxLength = value;
}

QStringList ModbusRequestList::getVarNames()
{
    QStringList res;
    const unsigned char varsCountInString = 5;
    res += "const unsigned short " + can.toLower() + "_req_count=" + QString::number(reqs.count())+";";
    res += "const unsigned short modbus_delay = " + QString::number(delay)+";";
    int varIndex = 0;
    int strNum=0;

    forever{
        QString s = "unsigned short ";
        for(int i=0;i<varsCountInString;++i) {
            varIndex = strNum*varsCountInString + i;
            if(varIndex>=vars.count()) break;
            s += vars.at(varIndex)->getVarName();
            if((i!=varsCountInString-1)&&(varIndex+1<vars.count())) s += ",";
        }
        s += ";";
        res += s;
        strNum++;
        if(strNum*varsCountInString>=vars.count()) break;
    }
    return res;
}

QStringList ModbusRequestList::getPlugVarNames()
{
    return QStringList() << "const unsigned short " + can.toLower() + "_req_count=0;" <<
                            "const unsigned short modbus_delay = 100;";
}

QStringList ModbusRequestList::getHeader()
{
    QStringList res;
    res+="#include \"mmb.h\"";
    res+=getVarNames();
    /*res+="typedef struct";
    res+="{";
    res+="\tunsigned short start_byte_num;";
    res+="\tchar bit_offset;";
    res+="\tunsigned short *ptr;";
    res+="}mvar;";
    res+="";
    res+="typedef struct";
    res+="{";
    res+="\tconst char *request;";
    res+="\tunsigned short req_length;";
    res+="\tunsigned short answer_length;";
    res+="\tconst mvar *varsPtr;";
    res+="\tunsigned short varCnt;";
    res+="\tunsigned char wr_flag;";
    res+="}mvar_reqs;";*/
    return res;
}

ModbusRequestList::ModbusRequestList(const QString &canName, ModbusVarsStorage &mVars):can(canName),
    maxSpaceLength(16),maxLength(128),delay(100)
{
    int varCnt = mVars.getVarCnt();
    for(int i=0;i<varCnt;++i) {
        QSharedPointer<ModbusVar> var = mVars.getModbusVar(i);
        if(var->getActiv()) {
            ModbusVar::canType cType;
            if(canName=="PC") cType = ModbusVar::CAN_PC;
            else if(canName=="MB") cType = ModbusVar::CAN_MB;
            else return;
            if(var->getCanType()==cType) {
                vars.append(var);
            }
        }
    }
}

QStringList ModbusRequestList::getResult()
{
    QStringList reqBody = getReqText();
    QStringList res = getHeader();
    res += "";
    res += reqBody;
    return res;
}

QStringList ModbusRequestList::getPlugResult()
{
    QStringList res = getPlugVarNames();
    res += "const " + can.toLower() + "_mvar_reqs[] = {(const char*)0,0,0,(const mvar*)0,0,0};";
    return res;
}

void ModbusRequestList::createRequests()
{
    reqs.clear();
    sortVarsByMemAddress();
    // заглушка
    for(int i=0;i<vars.count();++i) {
        VarReq vr;
        QSharedPointer<ModbusVar> v = vars.at(i);
        Request req;
        req.netAddress = v->getNetAddr();
        req.memAddress = v->getMemAddr();
        switch(v->getMemType()) {
            case ModbusVar::INPUTS:
                req.cmd = READ_DI;
                vr.bitOffset = 0;
                break;
            case ModbusVar::COILS:
                if(v->getWriteFlag()) req.cmd = WRITE_COILS;
                else req.cmd = READ_COILS;
                vr.bitOffset = 0;
                break;
            case ModbusVar::INP_REG:
                req.cmd = READ_INP_REG;
                vr.bitOffset = -1;
                break;
            case ModbusVar::HOLD_REG:
                if(v->getWriteFlag()) req.cmd = WRITE_HOLD_REG;
                else req.cmd = READ_HOLD_REG;
                vr.bitOffset =-1;
                break;
        }
        req.cnt = 1;
        vr.byteOffset = 0;
        vr.varName = v->getVarName();
        req.reqVars.append(vr);
        addRequestToList(req);
    }
}

QByteArray ModbusRequestList::getRequestBody(const ModbusRequestList::Request &r)
{
    QByteArray res;
    switch(r.cmd) {
    case READ_DI:
        res.append(r.netAddress);
        res.append(0x02);
        res.append(r.memAddress >> 8);
        res.append(r.memAddress & 0xFF);
        res.append(r.cnt >> 8);
        res.append(r.cnt & 0xFF);
        addCRC16(res);
        break;
    case READ_COILS:
        res.append(r.netAddress);
        res.append(0x01);
        res.append(r.memAddress >> 8);
        res.append(r.memAddress & 0xFF);
        res.append(r.cnt >> 8);
        res.append(r.cnt & 0xFF);
        addCRC16(res);
        break;
    case READ_INP_REG:
        res.append(r.netAddress);
        res.append(0x04);
        res.append(r.memAddress >> 8);
        res.append(r.memAddress & 0xFF);
        res.append(r.cnt >> 8);
        res.append(r.cnt & 0xFF);
        addCRC16(res);
        break;
    case READ_HOLD_REG:
        res.append(r.netAddress);
        res.append(0x03);
        res.append(r.memAddress >> 8);
        res.append(r.memAddress & 0xFF);
        res.append(r.cnt >> 8);
        res.append(r.cnt & 0xFF);
        addCRC16(res);
        break;
    case WRITE_COILS:{
        res.append(r.netAddress);
        res.append(0x0F);
        res.append(r.memAddress >> 8);
        res.append(r.memAddress & 0xFF);
        res.append(r.cnt >> 8);
        res.append(r.cnt & 0xFF);
        int byteCount = (r.cnt%8)?(r.cnt/8+1):r.cnt/8;
        res.append(byteCount);
        for(int i=0;i<byteCount;++i) res.append('\0');
        addCRC16(res);}
        break;
    case WRITE_HOLD_REG:
        res.append(r.netAddress);
        res.append(0x10);
        res.append(r.memAddress >> 8);
        res.append(r.memAddress & 0xFF);
        res.append(r.cnt >> 8);
        res.append(r.cnt & 0xFF);
        res.append(r.cnt*2);
        for(int i=0;i<r.cnt;i++) {
            res.append('\0');
            res.append('\0');
        }
        addCRC16(res);
        break;
    }

    return res;
}

int ModbusRequestList::getAnswerLength(const ModbusRequestList::Request &r)
{
    int length = 0;
    ModbusCMD cmd = r.cmd;
    switch(cmd) {
        case READ_DI:length=3+2+(r.cnt/8+1);if(r.cnt%8==0) length--;break;
        case READ_COILS:length=3+2+(r.cnt/8+1);if(r.cnt%8==0) length--;break;
        case WRITE_COILS:length=8;break;
        case READ_HOLD_REG:length=3+2+r.cnt*2;break;
        case WRITE_HOLD_REG:length=8;break;
        case READ_INP_REG:length=3+2+r.cnt*2;break;
    }

    return length;
}

bool ModbusRequestList::isWriteReq(const ModbusRequestList::Request &r)
{
    switch(r.cmd) {
    case WRITE_COILS:return true;
    case WRITE_HOLD_REG:return true;
    default:return false;
    }
    return false;
}

void ModbusRequestList::addCRC16(QByteArray &reqData)
{
    unsigned char i;
    unsigned char crch=0xFF,crcl=0xFF;
    for(auto reqByte: reqData) {
        i = crch ^ ((quint8)reqByte);
        crch=crcl ^ crc16H[i];
        crcl=crc16L[i];
    }
    reqData.append(crch);
    reqData.append(crcl);
}

void ModbusRequestList::sortVarsByMemAddress()
{
    sort(vars.begin(),vars.end(),
         [](QSharedPointer<ModbusVar> r1, QSharedPointer<ModbusVar> r2)->bool
    {return r1->getMemAddr()<r2->getMemAddr();});
}

void ModbusRequestList::addRequestToList(const Request &r)
{
    // search last similar request
    bool findFlag = false;
    if(reqs.count()) {
        for(int i=reqs.count()-1;i>=0;--i) {
            Request req = reqs.at(i);
            if((req.netAddress==r.netAddress)&&(req.cmd==r.cmd)&&(req.memAddress<r.memAddress)&&r.reqVars.count()) {
                int startAddr = req.memAddress;
                int cnt = req.cnt;
                int requiredCount = r.memAddress + r.cnt - 1;
                requiredCount = requiredCount - startAddr + 1;
                int spaceLength = r.memAddress - (startAddr+cnt);
                if((requiredCount <= maxLength) && (spaceLength <= maxSpaceLength)) {
                    reqs[i].cnt=requiredCount;
                    VarReq vr = r.reqVars.at(0);
                    if((r.cmd==READ_DI)||(r.cmd==READ_COILS)||(r.cmd==WRITE_COILS)) {
                        int bitNum = r.memAddress - req.memAddress;
                        vr.byteOffset = bitNum/8;
                        vr.bitOffset = bitNum%8;
                    }else {
                        vr.byteOffset = (r.memAddress - req.memAddress)*2;
                    }
                    reqs[i].reqVars.append(vr);
                    findFlag = true;
                    break;
                }else {
                    reqs.append(r);
                    findFlag = true;
                    break;
                }
            }
        }
        if(!findFlag) reqs.append(r);
    }else reqs.append(r);
}

QStringList ModbusRequestList::getReqText()
{
    QStringList res;
    createRequests();
    for(int i=0;i<reqs.count();++i) {
        res += "const mvar " + can.toLower() + "_req" + QString::number(i+1) + "_vars[] = {";
        for(int j=0;j<reqs.at(i).reqVars.count();++j) {
            VarReq v = reqs.at(i).reqVars.at(j);
            QString varDef = "{" + QString::number(v.byteOffset) + "," + QString::number(v.bitOffset) + ",&"  +v.varName+"}";
            if(j!=reqs.at(i).reqVars.count()-1) varDef += ",";
            res += "\t" + varDef;
        }
        res += "};";
    }
    res+="";
    res += "const mvar_reqs " + can.toLower() + "_mvar_reqs[] = {";
    for(int i=0;i<reqs.count();++i) {
        Request r = reqs.at(i);
        QString reqStr = "{\"";
        QByteArray reqBody = getRequestBody(r);
        for(auto reqByte:reqBody) {
            reqStr+="\\x";
            QString hexCode = QString::number((quint8)reqByte,16);
            if(hexCode.length()<2) hexCode = "0" + hexCode;
            reqStr += hexCode;
        }
        reqStr += "\", " + QString::number(reqBody.count()) + ", " + QString::number(getAnswerLength(r));
        reqStr += ", " + can.toLower() + "_req" + QString::number(i+1) + "_vars, ";
        reqStr += QString::number(r.reqVars.count()) + ", ";
        isWriteReq(r)?reqStr+="1}":reqStr+="0}";
        if(i!=reqs.count()-1) reqStr+=",";
        res += "\t" + reqStr;
    }
    res += "};";
    return res;
}

}
