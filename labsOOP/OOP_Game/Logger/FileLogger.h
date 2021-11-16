#pragma once
#include "Logger.h"

class FileLogger : public Logger{
public:
    explicit FileLogger(const std::string& filePath);
    ~FileLogger();

protected:
    void writePreInfo(const std::string &info) override;
    void writePostInfo(const std::string &info) override;
    void writeStyle(const std::string &style) override;
};
