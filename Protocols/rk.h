#ifndef RK_H
#define RK_H

#include "rkcommand.h"

namespace RkProtocol {

    class GetCoreVersion: public RkCommand
    {
        int netAddress;
    public:
        GetCoreVersion();
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        int getNetAddress(void) const {return netAddress;}
        ~GetCoreVersion();
    };

    class GetCpu: public RkCommand
    {
    public:
        GetCpu();
        bool form(Request &req);
        ~GetCpu();
    };

    class WriteFram: public RkCommand
    {
    public:
        WriteFram();
        bool form(Request &req);
        bool waitAnAnswer(Request &req, QIODevice &io);
        ~WriteFram();
    };

    class WriteRam: public RkCommand
    {
    public:
        WriteRam();
        bool form(Request &req);
        ~WriteRam();
    };

    class ReadFram: public RkCommand
    {
    public:
        ReadFram();
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        bool waitAnAnswer(Request &req, QIODevice &io);
        ~ReadFram();
    };

    class ReadRam: public RkCommand
    {
    public:
        ReadRam();
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~ReadRam();
    };

    class ReadIO: public RkCommand
    {
    public:
        ReadIO();
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~ReadIO();
    };

    class ReadTime: public RkCommand
    {
    public:
        ReadTime();
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~ReadTime();
    };

    class WriteTime: public RkCommand
    {
    public:
        WriteTime();
        bool form(Request &req);
        bool waitAnAnswer(Request &req, QIODevice &io);
        ~WriteTime();
    };

    class ResetController: public RkCommand
    {
    public:
        ResetController();
        bool form(Request &req);
        ~ResetController();
    };

    class GetCanName: public RkCommand
    {
    public:
        GetCanName();
        bool form(Request &req);
        bool getAnAnswer(Request &req);
        ~GetCanName();
    };
}

/*
    readUserMem();
    readRAM();
    readFRAM();
    readClock();
    readIO();
    readFlash();
    readFactorySettings();
    writeUserMem();
    writeRAM();
    writeClock();
    writeIO();
    writeFactorySettings();
*/

#endif // RK_H
