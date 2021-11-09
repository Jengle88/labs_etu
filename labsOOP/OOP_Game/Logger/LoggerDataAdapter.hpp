#pragma once

#include <string>
#include <utility>

template<typename T>
class LoggerDataAdapter { // Паттерн: Адаптер
    T data;
    std::string message;
public:
    explicit LoggerDataAdapter(const T &data, const std::string &message = "") : data(data), message(message) {}

    T getData() const {
        return data;
    }

    const std::string &getMessage() const {
        return message;
    }

    friend std::ostream &operator<<(std::ostream &os, const LoggerDataAdapter<T> &data) {
        os << (data.message.empty() ? "" : data.message + "\nData: ") << data.data;
        return os;
    }
};




