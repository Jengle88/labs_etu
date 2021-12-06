#pragma once
#include <string>
#include "UI/FieldScreen.h"
#include "Logger/ConsoleLogger.h"
#include "Logger/LoggerPull.h"
#include "GameHandler.h"
#include "Tools/DifficultDataReader.h"
#include "KeyControl/KeyboardControl.h"
#include "KeyControl/KeyboardDataReader.h"
#include "UI/KeySettingsScreen.h"


class GameStart {
public:
    static void startGameMode(const std::string& modeName) {
        if (modeName == "game") {
            std::setlocale(LC_ALL, "");
            LoggerPull *loggerPull = LoggerPull::getInstance();
            LoggerPull::addFileLogger("gameLogs", new FileLogger("logs.txt"));

            static auto dataDifficult = DifficultDataReader::readRulesPresets("../Data/GameEntityProperties.txt");
            static DifficultPreset difficultPreset = dataDifficult["Middle"];
            static RulesChecker* checker = &dataDifficult["Middle"];

            auto keyboardSetting = KeyboardDataReader::readKeyboardSetting("../Data/KeyboardSettings.txt");
            static KeyboardControl keyboardControl(keyboardSetting);
            static auto keyControl = static_cast<KeyControl*>(&keyboardControl);

            std::unordered_map<std::string, std::unordered_map<int, char>> keysActionControl;
            std::unordered_map<std::string, std::unordered_map<std::string, int>> actionBind;
            {
                auto actions = keyControl->getAllActionKeys();
                auto keyActionsBound = keyControl->getAllKeysBound();

                for (const auto &action: keyActionsBound) {
                    for (const auto &key: action.second) {
                        keysActionControl[action.first][key.second] = key.first;
                    }
                }
                for (const auto &action: actions) {
                    for (const auto &key: action.second) {
                        actionBind[action.first][key.first] = key.second;
                    }
                }
            }

            KeySettingsScreen keySettingsScreen(keysActionControl, actionBind);
            keySettingsScreen.showUpdatedScreen(2);
            int z = 2;
//            if (!keyControl->checkAllKeyBound()) // TODO заменить
//                throw std::logic_error("Не все кнопки указаны");
//
//            GameHandler<&keyControl, difficultPreset, &checker/*, &checker, &checker*/> gameHandler;
//            KeyboardControl keyboardController;
//            keyboardController.resetBindChar('w', HeroKeysControl::FIELD_MOVE_UP);
//            keyboardController.resetBindChar('s', HeroKeysControl::FIELD_MOVE_DOWN);
//            keyboardController.resetBindChar('d', HeroKeysControl::FIELD_MOVE_RIGHT);
//            keyboardController.resetBindChar('actions', HeroKeysControl::FIELD_MOVE_LEFT);
//            int z = 2;

//            Printer::printDivider();
//            Printer::printMenuWithChoice({"Start game", "Settings", "Exit"}, 1);
//            Printer::printDivider();
//            gameHandler.showStartScreen();
//            gameHandler.generateField();
//            gameHandler.observeField();

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