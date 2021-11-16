#pragma once
#include "Logger.h"

class ConsoleLogger : public Logger {
public:
    explicit ConsoleLogger(std::ostream* out);

protected:
    void writePreInfo(const std::string &info) override;
    void writePostInfo(const std::string &info) override;
    void writeStyle(const std::string &style) override;
};

