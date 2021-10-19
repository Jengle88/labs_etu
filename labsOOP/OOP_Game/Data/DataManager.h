#pragma once
#include <map>
#include "../Objects/Thing.h"

class DataManager {
    std::map<int, std::vector<Thing>> levelToThings;
    // Враги
    std::vector<std::string> getModelMonsterWait() const;
    std::vector<std::string> getModelArcherWait() const;
    std::vector<std::string> getModelGargoyleWait() const;
    // Герой
    std::vector<std::string> getModelHeroHead() const;
    std::vector<std::string> getModelHeroBodyWait(bool withSword = false, bool withArmor = false) const;
    std::vector<std::string> getModelHeroLegs() const;
public:
    DataManager();
    Thing getThing(int level, int typeThing);
    std::vector<std::string> getEnemy(int enemyType) const;
    std::vector<std::string> getHero(bool withSword = false, bool withArmor = false) const;
};
