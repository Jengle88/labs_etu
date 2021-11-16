#include "LoggerPull.h"

std::unordered_map<std::string, Logger*> LoggerPull::loggers;
LoggerPull* LoggerPull::loggerPull = nullptr;

std::unordered_map<const char*, LoggerPull::LoggerTypeData> LoggerPull::loggerTypeData = {
        { LoggerPull::LoggingType::Info, LoggerPull::LoggerTypeData(LoggerPull::LoggingType::Info, LoggerPull::LoggingColor::NONE) },
        { LoggerPull::LoggingType::Warning, LoggerPull::LoggerTypeData(LoggerPull::LoggingType::Warning, LoggerPull::LoggingColor::YELLOW) },
        { LoggerPull::LoggingType::Error, LoggerPull::LoggerTypeData(LoggerPull::LoggingType::Error, LoggerPull::LoggingColor::RED) }
};

LoggerPull *LoggerPull::getInstance() {
    if (LoggerPull::loggerPull == nullptr)
        LoggerPull::loggerPull = new LoggerPull();
    return LoggerPull::loggerPull;
}

void LoggerPull::addFileLogger(const std::string &key, FileLogger *fileLogger) {
    if (loggerPull == nullptr)
        throw std::invalid_argument("Логгер является nullptr");
    if (LoggerPull::loggers.count(key))
        delete LoggerPull::loggers[key];
    LoggerPull::loggers[key] = fileLogger;
}

void LoggerPull::addConsoleLogger(const std::string &key, ConsoleLogger *consoleLogger) {
    LoggerPull::loggers[key] = consoleLogger;
}

void LoggerPull::removeLogger(const std::string &key) {
    if (LoggerPull::loggers.count(key)) {
        delete LoggerPull::loggers[key];
        LoggerPull::loggers.erase(key);
    }
}

void LoggerPull::closeAllFileStreams() {
    for (auto &logger: LoggerPull::loggers) {
        delete logger.second;
    }
    LoggerPull::loggers.clear();
}





LoggerPull::~LoggerPull() {
    closeAllFileStreams();
    loggerPull = nullptr;
}


LoggerPull::LoggerPull() = default;
