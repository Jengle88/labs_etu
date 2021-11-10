#include "Logger.hpp"

std::unordered_map<std::string, std::fstream> Logger::fileOutputs;
Logger* Logger::logger = nullptr;

Logger::Logger() {}

Logger::~Logger() {
    closeAllStreams();
    logger = nullptr;
}

void Logger::setKeyOutputFile(const std::string& key, const std::string& filePath) {
    if (logger == nullptr) // должен быть создан объект, чтобы в конце вызывался деструктор при освобождении памяти
        throw -1;
    if (Logger::fileOutputs.count(key)) {
        Logger::fileOutputs[key].close();
    }
    Logger::fileOutputs[key].open(filePath, std::ios_base::out);
}

void Logger::closeOutputFile(const std::string& key) {
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

void Logger::writeMessageToConsole(const std::string& message, int typeMessage, std::ostream &output) {
    switch (typeMessage) {
        case LoggingType::Info:
            output << LoggingColor::NONE << "Info: " <<  message + "\n" << LoggingColor::NONE;
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

void Logger::writeMessageToFile(const std::string& key, const std::string& message, int typeMessage) {
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

void Logger::writeMessageInBoth(const std::string& key, const std::string& message, int typeMessage, std::ostream &output) {
    writeMessageToFile(key, message, typeMessage);
    writeMessageToConsole(message, typeMessage, output);
}
