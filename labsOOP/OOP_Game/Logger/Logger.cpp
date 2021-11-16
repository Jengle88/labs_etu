#include "Logger.h"

void Logger::writePreInfo(const std::string &info) {
    *output << info;
}

void Logger::writePostInfo(const std::string &info) {
    *output << info;
}

void Logger::writeStyle(const std::string &style) {
    *output << style;
}
