#include "../UI/Models/Field.h"
#include "../Data/DataManager.h"

class Printer {
public:
    static void printFullField(Field *field) ;
    static void printInventory(MainHero *hero, bool withSerialNumber = false);
    static void printEnemyInfo(std::map<CellPoint, Enemy*> *enemies);
    static void printFight(const DataManager& dataManager, const MainHero& hero, const Enemy& enemy);
};
