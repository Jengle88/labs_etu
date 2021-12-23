#pragma once
#include "../UI/Models/Field.h"
#include "../Data/DataManager.h"

class Printer {
public:
    static void printDivider(int length = 50);
    static void printMenuWithChoice(const std::vector<std::string>& menuItem, int selectedItem = -1);
    static void printFullField(const std::shared_ptr<Field> &field);
    static void printInventory(MainHero *hero, bool withSerialNumber = false);
    static void printEnemyInfo(std::map<CellPoint, Enemy*> *enemies);
    static void printHealthInfo(double heroHealth, double enemyHealth);
    static void printAttackInfo(const std::string &nameCharacter, double damage, bool wasDodge, bool wasCritical);
    static void printHeroAchievement(std::map<std::string, int>& achievement);
    static void printMessage(const std::string& message);
    static void printModels(const std::vector<std::string> &models);
};
