#pragma once

#include <ostream>
#include "LoggerDataAdapter.hpp"

class Logger {
protected:
    std::ostream *output = nullptr;
    virtual void writePreInfo(const std::string &info);
    virtual void writePostInfo(const std::string &info);
    virtual void writeStyle(const std::string &style);
public:
    template<typename T>
    void write(const LoggerDataAdapter<T> &data, const std::string &styleBegin = "", const std::string &styleEnd = "",
               const std::string &preInfo = "", const std::string &postInfo = "");
    virtual ~Logger() = default;
};

template<typename T>
void Logger::write(const LoggerDataAdapter<T> &data, const std::string &styleBegin, const std::string &styleEnd,
                   const std::string &preInfo, const std::string &postInfo) {
    writeStyle(styleBegin);
    writePreInfo(preInfo);
    *output << data;
    writePostInfo(postInfo);
    writeStyle(styleEnd);
}





