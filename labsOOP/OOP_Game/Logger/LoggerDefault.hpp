#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "LoggerDataAdapter.hpp"

class LoggerDefault {
    struct LoggingColor {
        static constexpr char NONE[] = "\033[0m";
        static constexpr char RED[] = "\033[0;31m";
        static constexpr char YELLOW[] = "\033[0;33m";
    };

    static std::unordered_map<std::string, std::fstream> fileOutputs;
    static LoggerDefault* logger;
    LoggerDefault();

public:
    struct LoggingType {
        static constexpr char Info[] = "Info";
        static constexpr char Warning[] = "Warning";
        static constexpr char Error[] = "Error";
    };
private:
    struct LoggerTypeData {
        const char* type = nullptr;
        const char* color = nullptr;
        LoggerTypeData(){};
        LoggerTypeData(const char* type, const char* color): type(type), color(color) {}
    };
    static std::unordered_map<const char*, LoggerTypeData> loggerTypeData;

public:
    static LoggerDefault* getInstance();
    ~LoggerDefault();

    static void setKeyOutputFile(const std::string& key, const std::string& filePath);
    static void closeOutputFile(const std::string& key);
    void closeAllStreams();
    static void writeMessageToConsole(const std::string& message, const char* typeMessage = LoggingType::Info, std::ostream& output = std::cout);
    static void writeMessageToFile(const std::string& key, const std::string& message, const char* typeMessage = LoggingType::Info);
    static void writeMessageInBoth(const std::string& key, const std::string& message, const char* typeMessage = LoggingType::Info, std::ostream& output = std::cout);
    template<typename T>
    static void writeDataToConsole(const LoggerDataAdapter<T> &data, const char* typeMessage = LoggingType::Info, std::ostream &output = std::cout) {
        if (loggerTypeData.count(typeMessage)) {
            const auto& loggerData = loggerTypeData[typeMessage];
            output << loggerData.color << loggerData.type << ": " << data << "\n" << LoggingColor::NONE;
        }
    }
    template<typename T>
    static void writeDataToFile(const std::string& key, const LoggerDataAdapter<T> &data, const char* typeMessage = LoggingType::Info) {
        if (!fileOutputs.count(key))
            return;
        if (loggerTypeData.count(typeMessage)) {
            const auto& loggerData = loggerTypeData[typeMessage];
            fileOutputs[key] << loggerData.type << ": " << data << "\n";
        }
    }
    template<typename T>
    static void writeDataInBoth(const std::string& key, const LoggerDataAdapter<T> &data, const char* typeMessage = LoggingType::Info, std::ostream &output = std::cout) {
        writeDataToFile(key, data, typeMessage);
        writeDataToConsole(data, typeMessage, output);
    }
};
