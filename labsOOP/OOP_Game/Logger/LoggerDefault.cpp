//#include "LoggerDefault.hpp"
//
//std::unordered_map<std::string, std::fstream> LoggerDefault::fileOutputs;
//LoggerDefault* LoggerDefault::logger = nullptr;
//std::unordered_map<const char*, LoggerDefault::LoggerTypeData> LoggerDefault::loggerTypeData = {
//        { LoggerDefault::LoggingType::Info, LoggerDefault::LoggerTypeData(LoggerDefault::LoggingType::Info, LoggerDefault::LoggingColor::NONE) },
//        { LoggerDefault::LoggingType::Warning, LoggerDefault::LoggerTypeData(LoggerDefault::LoggingType::Warning, LoggerDefault::LoggingColor::YELLOW) },
//        { LoggerDefault::LoggingType::Error, LoggerDefault::LoggerTypeData(LoggerDefault::LoggingType::Error, LoggerDefault::LoggingColor::RED) }
//};
//
//
//LoggerDefault::LoggerDefault() {}
//
//LoggerDefault::~LoggerDefault() {
//    closeAllStreams();
//    logger = nullptr;
//}
//
//void LoggerDefault::setKeyOutputFile(const std::string& key, const std::string& filePath) {
//    if (logger == nullptr) // должен быть создан объект, чтобы в конце вызывался деструктор при освобождении памяти
//        throw -1;
//    if (LoggerDefault::fileOutputs.count(key)) {
//        LoggerDefault::fileOutputs[key].close();
//    }
//    LoggerDefault::fileOutputs[key].open(filePath, std::ios_base::out);
//}
//
//void LoggerDefault::closeOutputFile(const std::string& key) {
//    if (LoggerDefault::fileOutputs.count(key)) {
//        LoggerDefault::fileOutputs[key].close();
//    }
//}
//
//void LoggerDefault::closeAllStreams() {
//    for(auto &output : fileOutputs) {
//        output.second.close();
//    }
//    fileOutputs.clear();
//}
//
//LoggerDefault* LoggerDefault::getInstance() {
//    if (LoggerDefault::logger == nullptr) {
//        LoggerDefault::logger = new LoggerDefault();
//    }
//    return LoggerDefault::logger;
//}
//
//void LoggerDefault::writeMessageToConsole(const std::string& message, const char* typeMessage, std::ostream &output) {
//    if (loggerTypeData.count(typeMessage)) {
//        const auto& loggerData = loggerTypeData[typeMessage];
//        output << loggerData.color << loggerData.type << ": " << message + "\n" << LoggingColor::NONE;
//    }
//}
//
//void LoggerDefault::writeMessageToFile(const std::string& key, const std::string& message, const char* typeMessage) {
//    if (!fileOutputs.count(key))
//        return;
//    if (loggerTypeData.count(typeMessage)) {
//        const auto& loggerData = loggerTypeData[typeMessage];
//        fileOutputs[key] << loggerData.type << ": " << message + "\n";
//    }
//}
//
//void LoggerDefault::writeMessageInBoth(const std::string& key, const std::string& message, const char* typeMessage, std::ostream &output) {
//    writeMessageToFile(key, message, typeMessage);
//    writeMessageToConsole(message, typeMessage, output);
//}
