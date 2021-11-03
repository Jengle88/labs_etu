#pragma once
#include <map>
#include <iostream>
#include <fstream>

class Logger {
    static std::map<std::string, std::fstream> outputs;
    static Logger* logger;
    template<typename T>
    static void writeData(std::string typeMessage, std::string key, T& data, std::string additionData = "");
    template<typename T>
    static void writeDataToConsole(std::string typeMessage, T& data, std::string additionData = "");
    Logger();

public:
    static Logger* getInstance();
    ~Logger();

    static void setKeyOutputFile(std::string key, std::string filePath);
    static void closeOutputFile(std::string key);
    void closeAllStreams();

    template<typename T>
    static void writeInfoData(std::string key, T& data, std::string additionData = "");
    template<typename T>
    static void writeWarningData(std::string key, T& data, std::string additionData = "");
    template<typename T>
    static void writeErrorData(std::string key, T& data, std::string additionData = "");
    template<typename T>
    static void writeInfoDataToConsole(T& data, std::string additionData = "");
    template<typename T>
    static void writeWarningDataToConsole(T& data, std::string additionData = "");
    template<typename T>
    static void writeErrorDataToConsole(T& data, std::string additionData = "");
};

std::map<std::string, std::fstream> Logger::outputs;
Logger* Logger::logger = nullptr;

void Logger::setKeyOutputFile(std::string key, std::string filePath) {
    if (Logger::outputs.count(key)) {
        Logger::outputs[key].close();
    }
    Logger::outputs[key].open(filePath, std::ios_base::out);
}

void Logger::closeOutputFile(std::string key) {
    if (Logger::outputs.count(key)) {
        Logger::outputs[key].close();
    }
}

void Logger::closeAllStreams() {
    for(auto &output : outputs) {
        output.second.close();
    }
    outputs.clear();
}

template<typename T>
void Logger::writeData(std::string typeMessage, std::string key, T& data, std::string additionData) {
    if (!additionData.empty()) {
        Logger::outputs[key] << typeMessage + ": " + additionData << '\n';
        Logger::outputs[key] << "Data: " << data << '\n';
    } else {
        Logger::outputs[key] << typeMessage + ": " << data << '\n';
    }
}

template<typename T>
void Logger::writeDataToConsole(std::string typeMessage, T &data, std::string additionData) {
    if (!additionData.empty()) {
        std::cout << typeMessage + ": " + additionData << '\n';
        std::cout << "Data: " << data << '\n';
    } else {
        std::cout << typeMessage + ": " << data << '\n';
    }
}

template<typename T>
void Logger::writeInfoData(std::string key, T &data, std::string additionData) {
    writeData("Info", key, data, additionData);
}

template<typename T>
void Logger::writeWarningData(std::string key, T &data, std::string additionData) {
    writeData("Warning", key, data, additionData);
}

template<typename T>
void Logger::writeErrorData(std::string key, T &data, std::string additionData) {
    writeData("Error", key, data, additionData);
}

template<typename T>
void Logger::writeInfoDataToConsole(T &data, std::string additionData) {
    writeDataToConsole("Info", (T&)data, additionData);
}

template<typename T>
void Logger::writeWarningDataToConsole(T &data, std::string additionData) {
    writeDataToConsole("Warning", data, additionData);
}

template<typename T>
void Logger::writeErrorDataToConsole(T &data, std::string additionData) {
    writeDataToConsole("Error", data, additionData);
}

Logger* Logger::getInstance() {
    if (Logger::logger == nullptr) {
        Logger::logger = new Logger();
    }
    return Logger::logger;
}

Logger::Logger() {}

Logger::~Logger() {
    closeAllStreams();
}