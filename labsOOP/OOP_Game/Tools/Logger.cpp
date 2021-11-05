#include "Logger.hpp"

std::map<std::string, std::fstream> Logger::fileOutputs;
Logger* Logger::logger = nullptr;

Logger::Logger() {}

Logger::~Logger() {
    closeAllStreams();
    logger = nullptr;
}

void Logger::setKeyOutputFile(std::string key, std::string filePath) {
    if (logger == nullptr) // должен быть создан объект, чтобы в конце вызывался деструктор при освобождении памяти
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
