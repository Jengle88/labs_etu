#include "ConsoleLogger.h"

ConsoleLogger::ConsoleLogger(std::ostream *out) {
    output = out;
}

// TODO добавить вывод LoggerTypeData из LoggerPull
void ConsoleLogger::writePreInfo(const std::string &info) {
    Logger::writePreInfo(info);
}

void ConsoleLogger::writePostInfo(const std::string &info) {
    Logger::writePostInfo(info);
}

void ConsoleLogger::writeStyle(const std::string &style) {
    Logger::writeStyle(style);
}