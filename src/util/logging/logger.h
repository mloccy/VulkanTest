#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <string>

namespace Util::Logging
{
    enum class LogLevel
    {
        Trace = 6,
        Debug = 5,
        Info = 4,
        Warning = 3,
        Error = 2,
        Fatal = 1
    };

    class Logger
    {
    public:
        Logger(const char * filePath, LogLevel level, bool unbuffered);
        ~Logger();

        void Trace(const char * msg);
        void Debug(const char * msg);
        void Info(const char * msg);
        void Warning(const char * msg);
        void Error(const char * msg);
        void Fatal(const char * msg);
        void Write(std::string msg, LogLevel level);

    private:
        bool unbuffered;
        FILE * logFile;
        LogLevel currentLogLevel;
    };
}
#endif