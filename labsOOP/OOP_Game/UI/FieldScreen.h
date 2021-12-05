#pragma once
#include "Models/Field.h"
#include "../Objects/ThingsManager.h"
#include "../Tools/Printer.h"
#include "FightScreen.h"
#include "../KeyControl/KeyControl.h"

class FieldScreen {
    std::tuple<int, int, int>
    showStartingParamsAndGenerateField(DataManager *dataManager, const KeyControl *keyController);

public:
    std::tuple<int, int, int> showStartFieldScreen(DataManager *dataManager, const KeyControl *keyController);
    std::string getScreenName() const;
    void showMessage(const std::string& message) const;
    void showUpdatedScreen(Field *field) const;
    void showEnemyInfo(std::map<CellPoint, Enemy *> *enemies) const;
    void showInventory(MainHero *hero, bool withSerialNumber = false) const;
    void showHeroAchievement(std::map<std::basic_string<char>, int> &achievement) const;
    std::string createTitleForThingAction(const std::string &nameThing, const std::map<std::string, double> &properties,
                                          char takeKey);
    void clearScreen() const;
};