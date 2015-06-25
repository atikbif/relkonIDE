#ifndef UDPDECORATOR_H
#define UDPDECORATOR_H

#include "commanddecorator.h"

class UdpDecorator : public CommandDecorator
{
public:
    UdpDecorator(CommandInterface *cmd);
    bool waitAnAnswer(Request &req, QIODevice &io);
    bool checkAnAnswer(Request &req);
    bool getAnAnswer(Request &req);
    ~UdpDecorator();
};

#endif // UDPDECORATOR_H
