#ifndef COMMANDDECORATOR_H
#define COMMANDDECORATOR_H

// декоратор для интерфейса команды

#include "commandinterface.h"

class CommandDecorator : public CommandInterface
{
public:
    explicit CommandDecorator(CommandInterface* cmd);
    bool form(Request& req);
    bool send(Request &req, QIODevice &io);
    bool waitAnAnswer(Request &req, QIODevice &io);
    bool checkAnAnswer(Request& req);
    bool getAnAnswer(Request& req);
    ~CommandDecorator();
private:
    CommandInterface* cmd;
};

#endif // COMMANDDECORATOR_H
