#ifndef RK_H
#define RK_H

#include "rkcommand.h"

namespace RkProtocol {

    class GetCoreVersion: public RkCommand
    {
        int netAddress;
    public:
        GetCoreVersion();
        CommandInterface* clone(void) {return new GetCoreVersion();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        int getNetAddress(void) const {return netAddress;}
        ~GetCoreVersion();
    };

    class GetCpu: public RkCommand
    {
    public:
        GetCpu();
        CommandInterface* clone(void) {return new GetCpu();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~GetCpu();
    };

    class WriteFram: public RkCommand
    {
    public:
        WriteFram();
        CommandInterface* clone(void) {return new WriteFram();}
        bool form(Request &req);
        bool waitAnAnswer(Request &req, QIODevice &io);
        ~WriteFram();
    };

    class WriteEE: public RkCommand
    {
    public:
        WriteEE();
        CommandInterface* clone(void) {return new WriteEE();}
        bool form(Request &req);
        bool waitAnAnswer(Request &req, QIODevice &io);
        ~WriteEE();
    };

    class WriteRam: public RkCommand
    {
    public:
        WriteRam();
        CommandInterface* clone(void) {return new WriteRam();}
        bool form(Request &req);
        ~WriteRam();
    };

    class WriteDispRam: public RkCommand
    {
    public:
        WriteDispRam();
        CommandInterface* clone(void) {return new WriteDispRam();}
        bool form(Request &req);
        ~WriteDispRam();
    };

    class WriteIO: public RkCommand
    {
    public:
        WriteIO();
        CommandInterface* clone(void) {return new WriteIO();}
        bool form(Request &req);
        ~WriteIO();
    };

    class ReadFram: public RkCommand
    {
    public:
        ReadFram();
        CommandInterface* clone(void) {return new ReadFram();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        bool waitAnAnswer(Request &req, QIODevice &io);
        ~ReadFram();
    };

    class ReadEE: public RkCommand
    {
    public:
        ReadEE();
        CommandInterface* clone(void) {return new ReadEE();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        bool waitAnAnswer(Request &req, QIODevice &io);
        ~ReadEE();
    };

    class ReadRam: public RkCommand
    {
    public:
        ReadRam();
        CommandInterface* clone(void) {return new ReadRam();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~ReadRam();
    };

    class ReadDispRam: public RkCommand
    {
    public:
        ReadDispRam();
        CommandInterface* clone(void) {return new ReadDispRam();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~ReadDispRam();
    };

    class ReadIO: public RkCommand
    {
    public:
        ReadIO();
        CommandInterface* clone(void) {return new ReadIO();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~ReadIO();
    };

    class ReadTime: public RkCommand
    {
    public:
        ReadTime();
        CommandInterface* clone(void) {return new ReadTime();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~ReadTime();
    };

    class WriteTime: public RkCommand
    {
    public:
        WriteTime();
        CommandInterface* clone(void) {return new WriteTime();}
        bool form(Request &req);
        bool waitAnAnswer(Request &req, QIODevice &io);
        ~WriteTime();
    };

    class ResetController: public RkCommand
    {
    public:
        ResetController();
        CommandInterface* clone(void) {return new ResetController();}
        bool form(Request &req);
        ~ResetController();
    };

    class GetCanName: public RkCommand
    {
    public:
        GetCanName();
        CommandInterface* clone(void) {return new GetCanName();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~GetCanName();
    };

    class F7toBootMode: public RkCommand
    {
    public:
        F7toBootMode() = default;
        CommandInterface* clone(void) {return new F7toBootMode();}
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~F7toBootMode() = default;
    };
}

#endif // RK_H
