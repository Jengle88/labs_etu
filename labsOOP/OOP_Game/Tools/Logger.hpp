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
    Logger();
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
    static void writeDataToFile(std::string key, T data, int typeMessage = LoggingType::Info, std::string additionData = "");
    template<typename T>
    static void writeDataToConsole(T data, int typeMessage = LoggingType::Info, std::ostream &output = std::cout, std::string additionData = "");
    template<typename T>
    static void writeDataInBoth(std::string key, T data, int typeMessage = LoggingType::Info, std::ostream &output = std::cout, std::string additionData = "");
};

std::map<std::string, std::fstream> Logger::fileOutputs;
Logger* Logger::logger = nullptr;

Logger::Logger() {}

Logger::~Logger() {
    closeAllStreams();
    logger = nullptr;
}

void Logger::setKeyOutputFile(std::string key, std::string filePath) {
    if (logger == nullptr) // должен быть создан объект, чтобы в конце вызывался деструктор
        throw -1;
    if (Logger::fileOutputs.count(key)) {
        Logger::fileOutputs[key].close();
    }
    Logger::fileOutputs[key].open(filePath, std::ios_base::out);
}

void Logger::closeOutputFile(std::string key) {
    if (Logger::fileOutputs.count(key)) {
        Logger::fileOutputs[key].close();
    }
}

void Logger::closeAllStreams() {
    for(auto &output : fileOutputs) {
        output.second.close();
    }
    fileOutputs.clear();
}

Logger* Logger::getInstance() {
    if (Logger::logger == nullptr) {
        Logger::logger = new Logger();
    }
    return Logger::logger;
}

template<typename T>
void Logger::writeDataToFile(std::string key, T data, int typeMessage, std::string additionData) {
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
void Logger::writeDataToConsole(T data, int typeMessage, std::ostream &output, std::string additionData) {
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
void Logger::writeDataInBoth(std::string key, T data, int typeMessage, std::ostream &output, std::string additionData) {
    writeDataToFile(key, data, typeMessage, additionData);
    writeDataToConsole(data, typeMessage, output, additionData);
}

void Logger::writeMessageToConsole(std::string message, int typeMessage, std::ostream &output) {
    switch (typeMessage) {
        case LoggingType::Info:
            output << LoggingColor::NONE << message << LoggingColor::NONE;
            break;
        case LoggingType::Warning:
            output << LoggingColor::YELLOW << "Warning: " + message + "\n" << LoggingColor::NONE;
            break;
        case LoggingType::Error:
            output << LoggingColor::RED << "Error: " + message + "\n" << LoggingColor::NONE;
            break;
        default:
            return;
    }
}

void Logger::writeMessageToFile(std::string key, std::string message, int typeMessage) {
    if (!fileOutputs.count(key))
        return;
    switch (typeMessage) {
        case LoggingType::Info:
            fileOutputs[key] << "Info: " + message +  "\n";
            break;
        case LoggingType::Warning:
            fileOutputs[key] << "Warning: " + message +  "\n";
            break;
        case LoggingType::Error:
            fileOutputs[key] << "Error: " + message +  "\n";
            break;
        default:
            return;
    }
}

void Logger::writeMessageInBoth(std::string key, std::string message, int typeMessage, std::ostream &output) {
    writeMessageToFile(key, message, typeMessage);
    writeMessageToConsole(message, typeMessage, output);
}
