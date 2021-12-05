#pragma once
#include "../Characters/MainHero.h"
#include "../Characters/Enemy.h"
#include "../Data/DataManager.h"
#include <unistd.h>
#include "FieldScreen.h"
#include "../Tools/Printer.h"

class FightScreen {
    std::vector<std::string> heroModel;
    std::vector<std::string> enemyModel;
public:
    FightScreen(const std::vector<std::string>& heroModel, const std::vector<std::string>& enemyModel);
    std::string getScreenName() const;
    void showUpdatedScreen(MainHero &mainHero, int selectedThing);
    void showHealthInfo(MainHero &mainHero, Enemy &enemy) const;
    void showMessage(const std::string& message) const;
    void showInventory(MainHero *hero, int selectedThing) const;
    void showFighterModels(const std::vector<std::string> &models) const;
    void showAttackInfo(const std::string& nameCharacter, double damage, bool wasDodge, bool wasCritical) const;
    void clearScreen() const;
};
