#ifndef ASCIIDECORATOR_H
#define ASCIIDECORATOR_H

// реализация декоратора команды - преобразование в ASCII

#include "commanddecorator.h"

class AsciiDecorator : public CommandDecorator
{
public:
    AsciiDecorator(CommandInterface* cmd);
    bool form(Request &req);
    bool waitAnAnswer(Request &req, QIODevice &io);
    bool checkAnAnswer(Request &req);
    ~AsciiDecorator();
private:
    static bool convertToAscii(Request &req);
    static bool convertToBin(Request &req);
};

#endif // ASCIIDECORATOR_H
