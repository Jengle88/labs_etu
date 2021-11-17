#pragma once

#include <ostream>
#include "LoggerDataAdapter.h"

class Logger {
protected:
    std::ostream *output = nullptr;
    virtual void writePreInfo(const std::string &info);
    virtual void writePostInfo(const std::string &info);
    virtual void writeStyleInfo(const std::string &style);
    Logger() = default;
public:
    template<typename T>
    void write(const LoggerDataAdapter<T> &data, const std::string &styleBegin = "", const std::string &styleEnd = "",
               const std::string &preInfo = "", const std::string &postInfo = "");
    virtual ~Logger() = default;
};

template<typename T>
void Logger::write(const LoggerDataAdapter<T> &data, const std::string &styleBegin, const std::string &styleEnd,
                   const std::string &preInfo, const std::string &postInfo) {
    writeStyleInfo(styleBegin);
    writePreInfo(preInfo);
    *output << data;
    writePostInfo(postInfo);
    writeStyleInfo(styleEnd);
}





