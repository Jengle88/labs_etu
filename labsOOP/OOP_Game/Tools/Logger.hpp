#pragma once
#include <map>
#include <iostream>
#include <fstream>

class Logger {
    struct LoggingColor {
        static constexpr char NONE[] = "\033[0m";
        static constexpr char RED[] = "\033[0;31m";
        static constexpr char YELLOW[] = "\033[0;33m";
    };
    static std::map<std::string, std::fstream> fileOutputs;
    static Logger* logger;
    Logger(); // Паттерн Синглтон
public:
    struct LoggingType {
        static constexpr int Info = 1;
        static constexpr int Warning = 2;
        static constexpr int Error = 3;
    };
    static Logger* getInstance();
    ~Logger();

    static void setKeyOutputFile(std::string key, std::string filePath);
    static void closeOutputFile(std::string key);
    void closeAllStreams();

    static void writeMessageToConsole(std::string message, int typeMessage = LoggingType::Info, std::ostream& output = std::cout);
    static void writeMessageToFile(std::string key, std::string message, int typeMessage = LoggingType::Info);
    static void writeMessageInBoth(std::string key, std::string message, int typeMessage = LoggingType::Info, std::ostream& output = std::cout);
    template<typename T>
    static void writeDataToFile(std::string key, T data, int typeMessage = LoggingType::Info, std::string additionData = "") {
        if (!fileOutputs.count(key))
            return;
        switch (typeMessage) {
            case LoggingType::Info:
                fileOutputs[key] << "Info: " + (additionData.empty() ? "" : additionData + "\nData: ") << data << '\n';
                break;
            case LoggingType::Warning:
                fileOutputs[key] << "Warning: " + (additionData.empty() ? "" : additionData + "\nData: ") << data << '\n';
                break;
            case LoggingType::Error:
                fileOutputs[key] << "Error: " + (additionData.empty() ? "" : additionData + "\nData: ") << data << '\n';
                break;
            default:
                return;
        }
    }
    template<typename T>
    static void writeDataToConsole(T data, int typeMessage = LoggingType::Info, std::string additionData = "", std::ostream &output = std::cout) {
        switch (typeMessage) {
            case LoggingType::Info:
                output << LoggingColor::NONE << "Info: " + (additionData.empty() ? "" : additionData + "\nData: ") << data << "\n" << LoggingColor::NONE;
                break;
            case LoggingType::Warning:
                output << LoggingColor::YELLOW << "Warning: " + (additionData.empty() ? "" : additionData + "\nData: ") << data << "\n" << LoggingColor::NONE;
                break;
            case LoggingType::Error:
                output << LoggingColor::RED << "Error: " + (additionData.empty() ? "" : additionData + "\nData: ") << data << "\n" << LoggingColor::NONE;
                break;
            default:
                return;
        }
    }
    template<typename T>
    static void writeDataInBoth(std::string key, T data, int typeMessage = LoggingType::Info,
                                std::string additionData = "", std::ostream &output = std::cout) {
        writeDataToFile(key, data, typeMessage, additionData);
        writeDataToConsole(data, typeMessage, additionData, output);
    }
};
