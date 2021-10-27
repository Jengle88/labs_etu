#pragma once
#include <map>
#include "../Objects/Thing.h"
#include "../Characters/Monster.h"

class DataManager {
    std::map<int, std::vector<Thing>> levelToThings;
    std::map<std::string, std::vector<std::string>> modelsCharacter;
    std::string dataModelsPathFile = "../Data/ObjectModel.xml";
    // Герой
    std::vector<std::string> getModelHeroHead() const;
    std::vector<std::string> getModelHeroBodyWait(bool withSword = false, bool withArmor = false) const;
    std::vector<std::string> getModelHeroLegs() const;
public:
    DataManager();
    Thing getThing(int level, int typeThing);
    Thing getHealthThing() const;
    void uploadModels();
    std::vector<std::string> getModelCharacter(const std::string &character);
    std::vector<std::string> getHero(bool withSword = false, bool withArmor = false) const;
};
