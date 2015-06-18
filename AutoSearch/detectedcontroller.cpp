#include "detectedcontroller.h"
#include <QMutexLocker>


qint8 DetectedController::getNetAddress()
{
    QMutexLocker locker(&mutex);
    return netAddress;
}

void DetectedController::setNetAddress(const qint8 &value)
{
    QMutexLocker locker(&mutex);
    netAddress = value;
}

QString DetectedController::getUartName()
{
    QMutexLocker locker(&mutex);
    return uartName;
}

void DetectedController::setUartName(const QString &value)
{
    QMutexLocker locker(&mutex);
    uartName = value;
}

bool DetectedController::getAsciiMode()
{
    QMutexLocker locker(&mutex);
    return asciiMode;
}

void DetectedController::setAsciiMode(bool value)
{
    QMutexLocker locker(&mutex);
    asciiMode = value;
}

bool DetectedController::getBootMode()
{
    QMutexLocker locker(&mutex);
    return bootMode;
}

void DetectedController::setBootMode(bool value)
{
    QMutexLocker locker(&mutex);
    bootMode = value;
}
qint32 DetectedController::getBaudrate()
{
    QMutexLocker locker(&mutex);
    return baudrate;
}

void DetectedController::setBaudrate(const qint32 &value)
{
    QMutexLocker locker(&mutex);
    baudrate = value;
}

DetectedController::DetectedController()
{

}

DetectedController::~DetectedController()
{

}
