#include <fstream>
#include "FileLogger.h"

FileLogger::FileLogger(const std::string &filePath) {
    output = new std::ofstream(filePath, std::ios_base::out);
}

FileLogger::~FileLogger() {
    dynamic_cast<std::ofstream*>(output)->close();
    delete output;
}

void FileLogger::writePreInfo(const std::string &info) {
    Logger::writePreInfo(info);
}

void FileLogger::writePostInfo(const std::string &info) {
    Logger::writePostInfo(info);
}

void FileLogger::writeStyleInfo(const std::string &style) {
}

