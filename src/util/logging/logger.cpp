#include "logger.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <chrono>

namespace Util::Logging
{
    Logger::Logger(const char * filePath, LogLevel level, bool unbuffered)
    {
        this->unbuffered = unbuffered;
        this->logFile = fopen(filePath, "a+");
        if (logFile == nullptr)
        {
            throw new std::runtime_error("Can't open log for writing...");
        }

        this->currentLogLevel = level;
    }

    Logger::~Logger()
    {
        if (this->logFile != NULL)
        {
            fclose(this->logFile);
        }
    }

    std::string levelToString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Trace:
            return "Trace";

        case LogLevel::Debug:
            return "Debug";

        case LogLevel::Info:
            return "Info";

        case LogLevel::Warning:
            return "Warning";

        case LogLevel::Error:
            return "Error";

        case LogLevel::Fatal:
            return "Fatal";
        }
    }

    void Logger::Write(std::string msg, LogLevel level)
    {
        if (level <= this->currentLogLevel)
        {
            std::ostringstream stream;

            time_t rawtime;
            struct tm * timeinfo;
            auto now = std::chrono::system_clock::now();

            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

            time(&rawtime);
            timeinfo = localtime(&rawtime);

            //std::string timeStr =

            //timeStr = timeStr.substr(0, timeStr.length() - 1);

            stream << levelToString(level) << ": ";
            stream << std::put_time(timeinfo, "%d-%m-%y %H:%M:%S");
            stream << '.' << std::setfill('0') << std::setw(3) << ms.count() << ": " << msg;
            auto logMessage = stream.str();
            if (fwrite(logMessage.c_str(), 1, logMessage.length(), this->logFile) != logMessage.length())
            {
                throw new std::runtime_error("failed to write log line...");
            }

            if (this->unbuffered)
            {
                fflush(this->logFile);
            }
        }
    }

    void Logger::Trace(const char * msg)
    {
        Write(msg, LogLevel::Trace);
    }

    void Logger::Debug(const char * msg)
    {
        Write(msg, LogLevel::Debug);
    }

    void Logger::Info(const char * msg)
    {
        Write(msg, LogLevel::Info);
    }

    void Logger::Warning(const char * msg)
    {
        Write(msg, LogLevel::Warning);
    }
    void Logger::Error(const char * msg)
    {
        Write(msg, LogLevel::Error);
    }
    void Logger::Fatal(const char * msg)
    {
        Write(msg, LogLevel::Fatal);
    }
}