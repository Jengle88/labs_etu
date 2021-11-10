#pragma once
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "LoggerDataAdapter.hpp"

class Logger {
    struct LoggingColor {
        static constexpr char NONE[] = "\033[0m";
        static constexpr char RED[] = "\033[0;31m";
        static constexpr char YELLOW[] = "\033[0;33m";
    };
    static std::unordered_map<std::string, std::fstream> fileOutputs;
    static Logger* logger;
    Logger();
public:
    struct LoggingType {
        static constexpr int Info = 1;
        static constexpr int Warning = 2;
        static constexpr int Error = 3;
    };
    static Logger* getInstance();
    ~Logger();

    static void setKeyOutputFile(const std::string& key, const std::string& filePath);
    static void closeOutputFile(const std::string& key);
    void closeAllStreams();
    static void writeMessageToConsole(const std::string& message, int typeMessage = LoggingType::Info, std::ostream& output = std::cout);
    static void writeMessageToFile(const std::string& key, const std::string& message, int typeMessage = LoggingType::Info);
    static void writeMessageInBoth(const std::string& key, const std::string& message, int typeMessage = LoggingType::Info, std::ostream& output = std::cout);
    template<typename T>
    static void writeDataToConsole(const LoggerDataAdapter<T> &data, int typeMessage = LoggingType::Info, std::ostream &output = std::cout) {
        switch (typeMessage) {
            case LoggingType::Info:
                output << LoggingColor::NONE << "Info: " << data << "\n" << LoggingColor::NONE;
                break;
            case LoggingType::Warning:
                output << LoggingColor::YELLOW << "Warning: " << data << "\n" << LoggingColor::NONE;
                break;
            case LoggingType::Error:
                output << LoggingColor::RED << "Error: " << data << "\n" << LoggingColor::NONE;
                break;
            default:
                return;
        }
    }
    template<typename T>
    static void writeDataToFile(const std::string& key, const LoggerDataAdapter<T> &data, int typeMessage = LoggingType::Info) {
        if (!fileOutputs.count(key))
            return;
        switch (typeMessage) {
            case LoggingType::Info:
                fileOutputs[key] << "Info: " << data << '\n';
                break;
            case LoggingType::Warning:
                fileOutputs[key] << "Warning: " << data << '\n';
                break;
            case LoggingType::Error:
                fileOutputs[key] << "Error: " << data << '\n';
                break;
            default:
                return;
        }
    }
    template<typename T>
    static void writeDataInBoth(const std::string& key, const LoggerDataAdapter<T> &data, int typeMessage = LoggingType::Info, std::ostream &output = std::cout) {
        writeDataToFile(key, data, typeMessage);
        writeDataToConsole(data, typeMessage, output);
    }
};
