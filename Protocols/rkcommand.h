#ifndef RKCOMMAND_H
#define RKCOMMAND_H

// базовая реализация команды протокола RKBIN
// интерфейс передачи данных - UART

#include "commandinterface.h"
//#include <QSerialPort>

class RkCommand : public CommandInterface
{
public:
    RkCommand();
    bool waitAnAnswer(Request &req, QIODevice &io);
    bool checkAnAnswer(Request &req);
    bool getAnAnswer(Request &req);
    ~RkCommand();
};

#endif // RKCOMMAND_H
