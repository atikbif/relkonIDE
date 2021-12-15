#include "f7loadercontroller.h"
#include <QVBoxLayout>
#include <QMutexLocker>
#include <QSerialPort>
#include "f7loaderprotocol.h"
#include <QFile>

F7LoaderController::F7LoaderController(const QString pName, int netAddr, const QString &fName, bool reset_flag, QObject *parent) : QObject(parent),
    rstFlag(reset_flag)
{
    QThread::msleep(500);
    dialog = new QDialog();
    dialog->setWindowTitle("Загрузка программы");
    auto *layout = new QVBoxLayout(dialog);
    bar = new QProgressBar();
    layout->addWidget(bar);
    label = new QLabel();
    layout->addWidget(label);
    dialog->adjustSize();
    dialog->setMinimumWidth(dialog->width()*2);
    //dialog->show();

    worker = new F7LoaderWorker(pName, netAddr,rstFlag);
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &F7LoaderController::writeCmd, worker, &F7LoaderWorker::writeFile);
    connect(this, &F7LoaderController::stopCmd, worker, &F7LoaderWorker::stopLoad);
    connect(worker, &F7LoaderWorker::info, this, &F7LoaderController::info);
    connect(worker, &F7LoaderWorker::percentUpdate, this, &F7LoaderController::percentUpdate);
    connect(worker, &F7LoaderWorker::writeComplete, this, &F7LoaderController::writeComplete);
    connect(worker, &F7LoaderWorker::error, this, &F7LoaderController::error);
    connect(worker, &F7LoaderWorker::writeComplete,dialog,&QDialog::close);

    thread()->start();
    emit writeCmd(fName);

    workerThread.start();
    dialog->exec();
}

F7LoaderController::~F7LoaderController()
{
    if(worker) worker->stopLoad();
    workerThread.quit();
    workerThread.wait();
    dialog->close();
    delete dialog;
}

void F7LoaderController::info(QString message)
{
    if(label) label->setText(message);
}

void F7LoaderController::percentUpdate(double val)
{
    if(bar) bar->setValue(lround(val));
}

F7LoaderWorker::F7LoaderWorker(const QString pName, int netAddr, bool rstFlag, QObject *parent): QObject(parent),
    pName(pName), netAddr (netAddr), rstFlag(rstFlag)
{

}

void F7LoaderWorker::writeFile(const QString &fName)
{
    const int wr_size = 500;
    QSerialPort port(pName);
    port.setDataBits(QSerialPort::Data8);
    port.setStopBits(QSerialPort::OneStop);
    port.setParity(QSerialPort::NoParity);
    port.setBaudRate(QSerialPort::Baud115200);
    if(port.open(QSerialPort::ReadWrite)) {
        int try_num = 0;
        const int try_max = 3;
        while(try_num<try_max) {
            if(F7LoaderProtocol::checkBootMode(port,netAddr, 500)) break;
            try_num++;
            QThread::msleep(10);
        }
        if(try_num>=try_max) {
            emit info("не удалось перейти в режим загрузчика");
            port.close();
            return;
        }
        // стирание флэш памяти
        QFile file(fName);
        if(file.open(QFile::ReadOnly)) {
            QByteArray data = file.readAll();
            while(data.count()%4) data.append(static_cast<char>(0xFFu));// размер должен быть кратным 4 байтам

            emit info("стирание памяти контроллера");
            emit percentUpdate(0);
            const int sect_cnt = 3;
            for(int i=0;i<sect_cnt;i++) {
                try_num = 0;
                mutex.lock();
                bool exit = stopFlag;
                mutex.unlock();
                if(exit) {
                    port.close();
                    return;
                }
                while(try_num<try_max) {
                    if(F7LoaderProtocol::eraseSector(port,netAddr, 2000,i)) {
                        emit percentUpdate(100.0/sect_cnt*(i+1));
                        break;
                    }
                    QThread::msleep(10);
                    try_num++;
                }
                if(try_num>=try_max) {
                    emit info("не удалось стереть память контроллера");
                    port.close();
                    return;
                }
            }

            emit info("загрузка программы");
            double percent = 0;
            double percWriteStep = data.count()%wr_size?100.0/(data.count()/wr_size+1):100.0/(data.count()/wr_size);
            emit percentUpdate(percent);

            auto endIt = data.constEnd();
            auto curIt = data.constBegin();
            quint32 addr = 0;
            auto dist=std::distance(curIt,endIt);
            while(dist!=0) {
                quint16 length = wr_size;
                if(dist<wr_size) length = dist;
                try_num=0;
                while(try_num<try_max) {
                    mutex.lock();
                    bool exit = stopFlag;
                    mutex.unlock();
                    if(exit) {
                        port.close();
                        return;
                    }
                    port.readAll();
                    bool res = F7LoaderProtocol::writeFlash(port,netAddr,100,addr,length,curIt);
                    if(res) {
                        percent += percWriteStep;
                        emit percentUpdate(percent);
                        break;
                    }
                    try_num++;
                    QThread::msleep(10);
                }
                if(try_num>=try_max) {
                    emit info("контроллер не отвечает");
                    port.close();
                    return;
                }
                curIt+=length;
                addr+=length;
                dist=std::distance(curIt,endIt);
            }
            emit info("загрузка завершена");

            if(rstFlag) {
                // переход к программе
                try_num = 0;
                while(try_num<try_max) {
                    if(F7LoaderProtocol::jumptoProg(port,netAddr, 100)) break;
                    try_num++;
                    QThread::msleep(10);
                }
                emit writeComplete();
            }else emit writeComplete();

        }else {
            emit info(QString("не удалось открыть файл ") + fName);
        }
        port.close();
    }

}

void F7LoaderWorker::stopLoad()
{
    QMutexLocker locker(&mutex);
    stopFlag = true;
}
