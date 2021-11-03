//#include "Logger.hpp"
//
//std::map<std::string, std::fstream> Logger::outputs;
//Logger* Logger::logger = nullptr;
//
//void Logger::setKeyOutputFile(std::string key, std::string filePath) {
//    if (Logger::outputs.count(key)) {
//        Logger::outputs[key].close();
//    }
//    Logger::outputs[key].open(filePath, std::ios_base::out);
//}
//
//void Logger::closeOutputFile(std::string key) {
//    if (Logger::outputs.count(key)) {
//        Logger::outputs[key].close();
//    }
//}
//
//void Logger::closeAllStreams() {
//    for(auto &output : outputs) {
//        output.second.close();
//    }
//    outputs.clear();
//}
//
////template<typename T>
//void Logger::writeData(std::string typeMessage, std::string key, int& data, std::string additionData) {
//    if (!additionData.empty()) {
//        Logger::outputs[key] << typeMessage + ": " + additionData << '\n';
//        Logger::outputs[key] << "Data: " << data << '\n';
//    } else {
//        Logger::outputs[key] << typeMessage + ": " << data << '\n';
//    }
//}
//
////template<typename T>
//void Logger::writeDataToConsole(std::string typeMessage, int &data, std::string additionData) {
//    if (!additionData.empty()) {
//        std::cout << typeMessage + ": " + additionData << '\n';
//        std::cout << "Data: " << data << '\n';
//    } else {
//        std::cout << typeMessage + ": " << data << '\n';
//    }
//}
//
//template<typename T>
//void Logger::writeInfoData(std::string key, T &data, std::string additionData) {
//    writeData("Info", key, data, additionData);
//}
//
//template<typename T>
//void Logger::writeWarningData(std::string key, T &data, std::string additionData) {
//    writeData("Warning", key, data, additionData);
//}
//
//template<typename T>
//void Logger::writeErrorData(std::string key, T &data, std::string additionData) {
//    writeData("Error", key, data, additionData);
//}
//
//template<typename T>
//void Logger::writeInfoDataToConsole(T &data, std::string additionData) {
//    writeDataToConsole("Info", (T&)data, additionData);
//}
//
//template<typename T>
//void Logger::writeWarningDataToConsole(T &data, std::string additionData) {
//    writeDataToConsole("Warning", data, additionData);
//}
//
//template<typename T>
//void Logger::writeErrorDataToConsole(T &data, std::string additionData) {
//    writeDataToConsole("Error", data, additionData);
//}
//
//Logger* Logger::getInstance() {
//    if (Logger::logger == nullptr) {
//        Logger::logger = new Logger();
//    }
//    return Logger::logger;
//}
//
//Logger::Logger() {}
//
//Logger::~Logger() {
//    closeAllStreams();
//}
//
//
//
//
