#include "commandinterface.h"

CommandInterface::CommandInterface()
{

}

bool CommandInterface::execute(Request &req, QIODevice &io)
{
    form(req);
    if(io.isOpen()) {
        io.readAll();
        io.write(req.getBody());
        io.waitForBytesWritten(100);
        if(waitAnAnswer(req,io)) {
            if(checkAnAnswer(req)) {
                getAnAnswer(req);
                return true;
            }
        }
    }
    return false;
}

CommandInterface::~CommandInterface()
{

}

