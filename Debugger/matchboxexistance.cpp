#include "matchboxexistance.h"
#include "pathstorage.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>

 MatchboxExistance::MatchboxExistance(const QString &plcType):plc(plcType)
{

}

QString MatchboxExistance::getMatchboxFile()
{
    QString res;

    QString fName = PathStorage::getBuildDir() + "/iodefines.h";
    QFile file(fName);
    if(file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        res = stream.readAll();
        file.close();
    }

    if(!PLCUtils::hasNoIO(plc)) {
        if(plc=="PC470") {
            res += QString(" IN0 IN1 IN2 IN3 OUT0 OUT1 OUT2 OUT3 ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 ADC201 ADC202 ADC203 ADC204 ADC205 ADC206 ADC207 ADC208 DAC1 DAC2 ");
        }else if(plc=="PC471") {
            res += QString(" IN0 IN1 IN2 IN3 OUT0 OUT1 OUT2 OUT3 ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 ADC201 ADC202 ADC203 ADC204 ADC205 ADC206 DAC1 DAC2 ");
        }else if(plc=="PC472") {
            res += QString(" IN0 IN1 IN2 IN3 OUT0 OUT1 OUT2 OUT3 ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 ADC201 ADC202 ADC203 ADC204 ADC205 ADC206 ADC207 ADC208 DAC1 DAC2 ");
        }else if(plc=="X6X B") {
            res += QString(" IN0 IN1 IN2 IN3 OUT0 OUT1 OUT2 OUT3 ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 DAC1 DAC2 ");
        }else if(plc=="X6X DB") {
            res += QString(" IN0 IN1 IN2 IN3 OUT0 OUT1 OUT2 OUT3 ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 DAC1 DAC2 ");
        }else if(plc=="X6X C") {
            res += QString(" IN0 IN1 IN2 IN3 OUT0 OUT1 OUT2 OUT3 ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 DAC1 DAC2 ");
        }else if(plc=="X6X BH/DBH") {
            res += QString(" IN0 IN1 IN2 IN3 OUT0 OUT1 OUT2 OUT3 ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 ADC201 ADC202 ADC203 ADC204 ADC205 ADC206 ADC207 ADC208 DAC1 DAC2 ");
        }else if(plc=="X6X BH7/DBH7") {
            res += QString(" IN0 IN1 IN2 IN3 OUT0 OUT1 OUT2 OUT3 ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 ADC201 ADC202 ADC203 ADC204 ADC205 ADC206 ADC207 ADC208 DAC1 DAC2 ");
        }else {
            res += QString(" IN0 IN1 IN2 IN3 DIN4 DIN5 OUT0 OUT1 OUT2 OUT3 DOUT4 DOUT5 ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 ADC201 ADC202 ADC203 ADC204 ADC205 ADC206 ADC207 ADC208 DAC1 DAC2 DAC3 DAC4 ");
        }
    }
    return res;
}

bool MatchboxExistance::checkIO(const QString &ioName, const QString &ioList)
{
    if(ioList.contains(QRegExp("\\b"+ioName+"\\b"))) return true;
    return false;
}
