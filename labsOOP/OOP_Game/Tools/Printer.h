#pragma once
#include "../UI/Models/Field.h"
#include "../Data/DataManager.h"

class Printer {
public:
    static void printFullField(Field *field) ;
    static void printInventory(MainHero *hero, bool withSerialNumber = false);
    static void printEnemyInfo(std::map<CellPoint, Enemy*> *enemies);
    static void printHealthInfo(double heroHealth, double enemyHealth);
    static void printAttackInfo(std::string nameCharacter, double damage, bool wasDodge, bool wasCritical);
    static void printHeroAchievement(std::map<std::string, int>& achievement);
    static void printMessage(const std::string& message);
};
