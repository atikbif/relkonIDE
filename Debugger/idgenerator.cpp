#include "idgenerator.h"
#include <boost/crc.hpp>
#include<cstddef>
#include <QString>
#include <QDateTime>
#include <QCryptographicHash>

IdGenerator::IdGenerator()
{

}


QString IdGenerator::getID(const QString &inpString)
{
    return inpString;
}

IdGenerator::~IdGenerator()
{

}

