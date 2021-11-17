#include "ConsoleLogger.h"

ConsoleLogger::ConsoleLogger(std::ostream *out) {
    output = out;
}

void ConsoleLogger::writePreInfo(const std::string &info) {
    Logger::writePreInfo(info);
}

void ConsoleLogger::writePostInfo(const std::string &info) {
    Logger::writePostInfo(info);
}

void ConsoleLogger::writeStyleInfo(const std::string &style) {
    Logger::writeStyleInfo(style);
}
