#include "../UI/Models/Field.h"
#include "../Data/DataManager.h"

class Printer {
public:
    static void printFullField(Field *field) ;
    static void printInventory(MainHero *hero, bool withSerialNumber = false);
    static void printEnemyInfo(std::map<CellPoint, Enemy*> *enemies);
    static void printHealthInfo(const double heroHealth, const double enemyHealth);
    static void printAttackInfo(int characterType, double damage, bool wasDodge, bool wasCritical);
    static void printHeroAchievement(const std::vector<int>& achievement);
//    static void printFight(const DataManager& dataManager, const MainHero& hero, const Enemy& enemy);
};
