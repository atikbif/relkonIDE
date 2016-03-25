#include "matchboxexistance.h"
#include "pathstorage.h"
#include <QFile>
#include <QTextStream>
#include <QRegExp>

MatchboxExistance::MatchboxExistance()
{

}

QString MatchboxExistance::getMatchboxFile()
{
    QString res;
    QString fName = PathStorage::getSrcDir() + "/iodefines.h";
    QFile file(fName);
    if(file.open(QFile::ReadOnly)) {
        QTextStream stream(&file);
        res = stream.readAll();
        res += QString(" IN0 IN1 IN2 IN3 DIN4 DIN5 ");
        res += QString("OUT0 OUT1 OUT2 OUT3 DOUT4 DOUT5 ");
        res += QString("ADC1 ADC2 ADC3 ADC4 ADC5 ADC6 ADC7 ADC8 ");
        res += QString("ADC201 ADC202 ADC203 ADC204 ADC205 ADC206 ADC207 ADC208 ");
        res += QString("DAC1 DAC2 DAC3 DAC4 ");
        file.close();
    }
    return res;
}

bool MatchboxExistance::checkIO(const QString &ioName, const QString &ioList)
{
    if(ioList.contains(QRegExp("\\b"+ioName+"\\b"))) return true;
    return false;
}
