#pragma once
#include <string>
#include "UI/FieldScreen.h"
#include "Logger/LoggerDefault.hpp"
#include "Logger/ConsoleLogger.h"
#include "Logger/LoggerPull.h"

class GameStart {
public:
    static void startGameMode(const std::string& modeName) {
        if (modeName == "game") {
            std::setlocale(LC_ALL, "");
            LoggerPull *loggerPull = LoggerPull::getInstance();
            LoggerPull::addFileLogger("gameLogs", new FileLogger("logs.txt"));
            auto *dataManager = new DataManager();
            dataManager->uploadModels();
            LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Модели загружены"));
            FieldScreen mainScreen;
            mainScreen.showStartFieldScreen(dataManager);
            mainScreen.gameStatusObserver();
            delete dataManager;
            delete loggerPull;
        }
        else if (modeName == "features") {
            LoggerPull *loggerPull = LoggerPull::getInstance();
            LoggerPull::addFileLogger("gameLogs1", new FileLogger("feat1.txt"));
            LoggerPull::addFileLogger("gameLogs2", new FileLogger("feat2.txt"));
            LoggerPull::addConsoleLogger("gameLogs3", new ConsoleLogger(&std::cout));
//            LoggerPull::removeLogger("gameLogs1");
            LoggerPull::writeDataInStreams({"gameLogs1","gameLogs-1", "gameLogs2", "gameLogs3"}, LoggerDataAdapter<std::string>("Hi!123"), LoggerPull::LoggingType::Error);
            LoggerPull::writeDataInStreams({"gameLogs1","gameLogs-1", "gameLogs3"}, LoggerDataAdapter<std::string>("Hi!1234"), LoggerPull::LoggingType::Error);
            LoggerPull::writeDataInStreams({"gameLogs1","gameLogs-1", "gameLogs2"}, LoggerDataAdapter<std::string>("Hi!1235"), LoggerPull::LoggingType::Error);
            delete loggerPull;
        }
    }
};