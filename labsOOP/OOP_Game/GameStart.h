#pragma once
#include <string>
#include "UI/FieldScreen.h"
#include "Logger/LoggerDefault.hpp"
#include "Logger/ConsoleLogger.h"
#include "Logger/LoggerPull.h"

class GameStart {
public:
    static void startGameMode(std::string modeName) {
        if (modeName == "game") {
            std::setlocale(LC_ALL, "");
            LoggerPull *loggerPull = LoggerPull::getInstance();
            LoggerPull::addFileLogger("gameLogs", new FileLogger("logs.txt"));
            LoggerPull::addConsoleLogger("gameLogs1", new ConsoleLogger(&std::cout));
            LoggerPull::removeLogger("gameLogs");
            LoggerPull::writeDataInStreams({"gameLogs", "gameLogs1"}, LoggerDataAdapter<std::string>("Hi!123"), LoggerPull::LoggingType::Error);
            delete loggerPull;
//            LoggerDefault *loggerPull = LoggerDefault::getInstance();
//            LoggerDefault::setKeyOutputFile("gameLogs", "logs.txt");
//            auto *dataManager = new DataManager();
//            dataManager->uploadModels();
//            LoggerDefault::writeMessageToFile("gameLogs", "Модели загружены");
//            FieldScreen mainScreen;
//            mainScreen.showStartFieldScreen(dataManager);
//            mainScreen.gameStatusObserver();
//            delete dataManager;
//            delete loggerPull;
        }
        else if (modeName == "features") {
            LoggerDefault* logger = LoggerDefault::getInstance();
            LoggerDefault::setKeyOutputFile("feat1","feat1.txt");
            LoggerDefault::setKeyOutputFile("feat2","feat2.txt");
            LoggerDefault::writeDataToFile("feat1", LoggerDataAdapter<int>(100, "Целое число"));
            LoggerDefault::writeDataToFile("feat2", LoggerDataAdapter<double>(100, "Число c плавающей точкой"));
            LoggerDefault::writeMessageToFile("feat1", "Выше было число");
            LoggerDefault::writeMessageToFile("feat2", "Выше было число с плавающей точкой");
            LoggerDefault::writeMessageToConsole("Здесь могло быть число");
            LoggerDefault::writeMessageToConsole("Здесь должно быть число", LoggerDefault::LoggingType::Warning);
            LoggerDefault::writeMessageToConsole("Здесь нет числа", LoggerDefault::LoggingType::Error);
            LoggerDefault::writeDataToConsole(LoggerDataAdapter<int>(15, "Здесь есть число!"));
            LoggerDefault::writeDataToConsole(LoggerDataAdapter<int>(-15, "Здесь неверное число!"), LoggerDefault::LoggingType::Warning);
            LoggerDefault::writeDataToConsole(LoggerDataAdapter<double>(15.15, "Здесь не целое число!"), LoggerDefault::LoggingType::Error);
            delete logger;
        }
    }
};