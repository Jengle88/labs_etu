//#include "Logger.hpp"
//
//std::map<std::string, std::fstream> Logger::fileOutputs;
//Logger* Logger::logger = nullptr;
//
//void Logger::setKeyOutputFile(std::string key, std::string filePath) {
//    if (Logger::fileOutputs.count(key)) {
//        Logger::fileOutputs[key].close();
//    }
//    Logger::fileOutputs[key].open(filePath, std::ios_base::out);
//}
//
//void Logger::closeOutputFile(std::string key) {
//    if (Logger::fileOutputs.count(key)) {
//        Logger::fileOutputs[key].close();
//    }
//}
//
//void Logger::closeAllStreams() {
//    for(auto &output : fileOutputs) {
//        output.second.close();
//    }
//    fileOutputs.clear();
//}
//
////template<typename T>
//void Logger::writeDataFile(std::string typeMessage, std::string key, int& data, std::string additionData) {
//    if (!additionData.empty()) {
//        Logger::fileOutputs[key] << typeMessage + ": " + additionData << '\n';
//        Logger::fileOutputs[key] << "Data: " << data << '\n';
//    } else {
//        Logger::fileOutputs[key] << typeMessage + ": " << data << '\n';
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
//    writeDataFile("Info", key, data, additionData);
//}
//
//template<typename T>
//void Logger::writeWarningData(std::string key, T &data, std::string additionData) {
//    writeDataFile("Warning", key, data, additionData);
//}
//
//template<typename T>
//void Logger::writeErrorData(std::string key, T &data, std::string additionData) {
//    writeDataFile("Error", key, data, additionData);
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
