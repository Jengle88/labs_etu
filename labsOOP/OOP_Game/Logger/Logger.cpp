#include "Logger.h"

void Logger::writePreInfo(const std::string &info) {
    *output << info;
}

void Logger::writePostInfo(const std::string &info) {
    *output << info;
}

void Logger::writeStyleInfo(const std::string &style) {
    *output << style;
}
