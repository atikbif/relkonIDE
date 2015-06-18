#include "udpdecorator.h"

UdpDecorator::UdpDecorator(CommandInterface *cmd):CommandDecorator(cmd)
{

}

bool UdpDecorator::send(Request &req, QIODevice &io)
{
    return CommandDecorator::send(req,io);
}

bool UdpDecorator::waitAnAnswer(Request &req, QIODevice &io)
{
    return CommandDecorator::waitAnAnswer(req,io);
}

bool UdpDecorator::checkAnAnswer(Request &req)
{
    return CommandDecorator::checkAnAnswer(req);
}

bool UdpDecorator::getAnAnswer(Request &req)
{
    return CommandDecorator::getAnAnswer(req);
}

UdpDecorator::~UdpDecorator()
{

}

