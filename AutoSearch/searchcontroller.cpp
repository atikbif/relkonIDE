#include "searchcontroller.h"

qint32 SearchController::getBaudrate() const
{
    return baudrate;
}

void SearchController::setBaudrate(const qint32 &value)
{
    baudrate = value;
}

qint8 SearchController::getNetAddress() const
{
    return netAddress;
}

void SearchController::setNetAddress(const qint8 &value)
{
    netAddress = value;
}

QString SearchController::getUartName() const
{
    return uartName;
}

void SearchController::setUartName(const QString &value)
{
    uartName = value;
}

bool SearchController::getAsciiMode() const
{
    return asciiMode;
}

void SearchController::setAsciiMode(bool value)
{
    asciiMode = value;
}

bool SearchController::getBootMode() const
{
    return bootMode;
}

void SearchController::setBootMode(bool value)
{
    bootMode = value;
}

QString SearchController::getCanName() const
{
    return canName;
}

void SearchController::setCanName(const QString &value)
{
    canName = value;
}

SearchController::SearchController()
{
    baudrate = 0;
    netAddress = 0;
    uartName = "";
    asciiMode = false;
    bootMode = false;
    canName = "";
}
