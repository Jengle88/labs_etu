#pragma once
#include <map>
#include <unordered_map>
#include "../Objects/Thing.h"
#include "../Characters/Monster.h"
#include "../Tools/ModelDataReader.h"
#include "../Rules/ThingRules.h"

#

class DataManager {
    std::map<int, std::vector<Thing>> levelToThings;
    std::vector<Thing> healThings;
    std::map<std::string, std::vector<std::string>> modelsCharacter;
    std::string dataModelsPathFile = "../Data/ObjectModel.xml";
    // Герой
    std::vector<std::string> getModelHeroHead() const;
    std::vector<std::string> getModelHeroBodyWait(bool withSword = false, bool withArmor = false) const;
    std::vector<std::string> getModelHeroLegs() const;
public:
    DataManager(const std::unordered_map<std::string, ThingRules>& things);
    Thing getThing(int level, int typeThing);
    Thing getHealthThing() const;
    void uploadModels();
    void uploadParamsThing(const std::vector<Thing> & things);
    std::vector<std::string> getModelCharacter(const std::string &character);
    std::vector<std::string> getHero(bool withSword = false, bool withArmor = false) const;
};
