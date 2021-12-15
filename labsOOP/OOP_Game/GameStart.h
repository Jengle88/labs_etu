#pragma once
#include <string>
#include "UI/FieldScreen.h"
#include "Logger/ConsoleLogger.h"
#include "Logger/LoggerPull.h"
#include "GameHandler.h"
#include "Rules/DifficultDataReader.h"
#include "KeyControl/KeyboardControl.h"
#include "KeyControl/KeyDataReader.h"
#include "UI/KeySettingsScreen.h"


class GameStart {
public:
    static void startGameMode() {
        std::setlocale(LC_ALL, "");
        LoggerPull *loggerPull = LoggerPull::getInstance();
        LoggerPull::addFileLogger("gameLogs", new FileLogger("logs.txt"));

        static auto dataDifficult = DifficultDataReader::readDifficultPresets("../Data/GameEntityProperties.txt");
        std::string difficultName = "Easy";
        static DifficultPreset difficultPreset = dataDifficult[difficultName];
        static RulesChecker* checker = &dataDifficult[difficultName];

        auto keyboardSetting = KeyDataReader::readKeysSettings("../Data/KeyboardSettings.txt");
        static KeyboardControl keyboardControl(keyboardSetting);
        static auto keyControl = static_cast<KeyControl*>(&keyboardControl);
        if (!keyControl->checkAllKeyBound())
            throw std::logic_error("Не все привязки указаны");

        GameHandler<&keyControl, difficultPreset, &checker> gameHandler;
        gameHandler.showStartScreen();

        delete loggerPull;
    }
};