#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

// базовый интерфейс команды протокола
// функционал расширяется с помощью паттерна декоратор

#include "request.h"
#include <QByteArray>
#include <QIODevice>

class CommandInterface
{
public:
    CommandInterface();
    virtual bool form(Request& req) = 0;    // сформировать тело команды
    virtual bool send(Request& req, QIODevice& io) = 0;    // отправить команду
    virtual bool waitAnAnswer(Request& req, QIODevice& io)=0;  // ожидание ответа
    virtual bool checkAnAnswer(Request& req)=0; // проверка ответа
    virtual bool getAnAnswer(Request& req)=0;   // формирование буфера ответа
    virtual bool execute(Request& req, QIODevice& io);
public:
    virtual ~CommandInterface();
};

#endif // COMMANDINTERFACE_H
