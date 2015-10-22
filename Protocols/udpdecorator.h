#ifndef UDPDECORATOR_H
#define UDPDECORATOR_H

#include "commanddecorator.h"

class UdpDecorator : public CommandDecorator
{
public:
    explicit UdpDecorator(CommandInterface *cmd);
    bool waitAnAnswer(Request &req, QIODevice &io);
    bool checkAnAnswer(Request &req);
    bool getAnAnswer(Request &req);
    ~UdpDecorator();

    // CommandInterface interface
public:
    bool execute(Request &req, QIODevice &io);
};

#endif // UDPDECORATOR_H
