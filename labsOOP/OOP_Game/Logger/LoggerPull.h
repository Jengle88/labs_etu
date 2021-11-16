#pragma once

#include <unordered_map>
#include <vector>
#include "Logger.h"
#include "FileLogger.h"
#include "ConsoleLogger.h"

class LoggerPull {
    struct LoggingColor {
        static constexpr char NONE[] = "\033[0m";
        static constexpr char RED[] = "\033[0;31m";
        static constexpr char YELLOW[] = "\033[0;33m";
    };
    struct LoggerTypeData {
        const char* type = nullptr;
        const char* color = nullptr;
        LoggerTypeData(){};
        LoggerTypeData(const char* type, const char* color): type(type), color(color) {}
    };

    static std::unordered_map<std::string, Logger*> loggers;
    static std::unordered_map<const char*, LoggerTypeData> loggerTypeData;
    static LoggerPull* loggerPull;
    LoggerPull();

public:
    struct LoggingType {
        static constexpr char Info[] = "Info";
        static constexpr char Warning[] = "Warning";
        static constexpr char Error[] = "Error";
    };

    ~LoggerPull();
    static LoggerPull* getInstance();
    static void addFileLogger(const std::string& key, FileLogger *fileLogger);
    static void addConsoleLogger(const std::string& key, ConsoleLogger *consoleLogger);
    static void removeLogger(const std::string& key);
    static void closeAllFileStreams();
    template<typename T>
    static void writeData(const std::string& key, const LoggerDataAdapter<T>& data, const char loggingType[] = LoggingType::Info);
    template<typename T>
    static void writeDataInStreams(const std::vector<std::string> &keys, const LoggerDataAdapter<T> &data, const char loggingType[] = LoggingType::Info);

};

template<typename T>
void LoggerPull::writeData(const std::string &key, const LoggerDataAdapter<T> &data, const char *loggingType) {
    if (LoggerPull::loggers.count(key)) {
        auto& loggingTypeData = loggerTypeData[loggingType];
        std::string preInfo = std::string(loggingTypeData.type) + ": ";
        std::string postInfo = std::string("\n");
        LoggerPull::loggers[key]->write(data, std::string(loggingTypeData.color), std::string(LoggingColor::NONE), preInfo, postInfo);
    }
}

template<typename T>
void LoggerPull::writeDataInStreams(const std::vector<std::string> &keys, const LoggerDataAdapter<T> &data,
                                    const char loggingType[]) {
    auto& loggingTypeData = loggerTypeData[loggingType];
    std::string preInfo = std::string(loggingTypeData.type) + ": ";
    std::string postInfo = std::string("\n");
    for (const auto &key: keys) {
        if (LoggerPull::loggers.count(key))
            LoggerPull::loggers[key]->write(data, std::string(loggingTypeData.color), std::string(LoggingColor::NONE), preInfo, postInfo);
    }
}