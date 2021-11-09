#pragma once
#include <string>
#include "UI/FieldScreen.h"
#include "Logger/Logger.hpp"

class GameStart {
public:
    static void startGameMode(std::string modeName) {
        if (modeName == "game") {
            std::setlocale(LC_ALL, "");
            Logger *logger = Logger::getInstance();
            Logger::setKeyOutputFile("gameLogs", "logs.txt");
            auto *dataManager = new DataManager();
            dataManager->uploadModels();
            Logger::writeMessageToFile("gameLogs", "Модели загружены");
            FieldScreen mainScreen;
            mainScreen.showStartFieldScreen(dataManager);
            mainScreen.gameStatusObserver();
            delete dataManager;
            delete logger;
        }
        else if (modeName == "features") {
            Logger* logger = Logger::getInstance();
            Logger::setKeyOutputFile("feat1","feat1.txt");
            Logger::setKeyOutputFile("feat2","feat2.txt");
            Logger::writeDataToFile("feat1", LoggerDataAdapter<int>(100, "Целое число"));
            Logger::writeDataToFile("feat2", LoggerDataAdapter<double>(100, "Число c плавающей точкой"));
            Logger::writeMessageToFile("feat1", "Выше было число");
            Logger::writeMessageToFile("feat2", "Выше было число с плавающей точкой");
            Logger::writeMessageToConsole("Здесь могло быть число");
            Logger::writeMessageToConsole("Здесь должно быть число", Logger::LoggingType::Warning);
            Logger::writeMessageToConsole("Здесь нет числа", Logger::LoggingType::Error);
            Logger::writeDataToConsole(LoggerDataAdapter<int>(15, "Здесь есть число!"));
            Logger::writeDataToConsole(LoggerDataAdapter<int>(-15, "Здесь неверное число!"), Logger::LoggingType::Warning);
            Logger::writeDataToConsole(LoggerDataAdapter<double>(15.15, "Здесь не целое число!"), Logger::LoggingType::Error);
            delete logger;
        }
    }
};