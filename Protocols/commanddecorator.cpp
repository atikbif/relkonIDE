#include "commanddecorator.h"

CommandDecorator::CommandDecorator(CommandInterface *cmd)
{
    this->cmd = cmd;
}

bool CommandDecorator::form(Request &req)
{
    return cmd->form(req);
}

bool CommandDecorator::send(Request &req, QIODevice &io)
{
    return cmd->send(req,io);
}

bool CommandDecorator::waitAnAnswer(Request &req, QIODevice &io)
{
    return cmd->waitAnAnswer(req,io);
}

bool CommandDecorator::checkAnAnswer(Request &req)
{
    return cmd->checkAnAnswer(req);
}

bool CommandDecorator::getAnAnswer(Request &req)
{
    return cmd->getAnAnswer(req);
}

CommandDecorator::~CommandDecorator()
{
    delete cmd;
}

