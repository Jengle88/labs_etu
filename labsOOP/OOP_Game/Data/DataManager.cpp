#include "DataManager.h"
#include "../Logger/LoggerPull.h"
#include "../Rules/ThingRules.h"

DataManager::DataManager(const std::vector<ThingRules>& things) {
    std::vector<Thing> thingsArray(things.size());
    for (int i = 0; i < thingsArray.size(); ++i) {
        thingsArray[i] = things[i].toThing();
    }
    uploadParamsThing(thingsArray);
}

Thing DataManager::getThing(int level, int typeThing) {
    if (levelToThings.empty())
        throw std::logic_error("Не загружены параметры предметов.");
    return levelToThings[level][typeThing];
}

Thing DataManager::getHealthThing() const {
    if (healThings.empty())
        throw std::logic_error("Не загружены параметры лечебных предметов.");
    return *healThings.begin();
}

std::vector<std::string> DataManager::getModelHeroHead() const {
    return modelsCharacter.at("Hero head");
}

std::vector<std::string> DataManager::getModelHeroBodyWait(bool withSword, bool withArmor) const {
    if (withArmor && withSword) {
        return modelsCharacter.at("Hero body withSwordArmor");
    } else if (withSword) {
        return modelsCharacter.at("Hero body withSword");
    } else if (withArmor) {
        return modelsCharacter.at("Hero body withArmor");
    } else {
        return modelsCharacter.at("Hero body default");
    }
}

std::vector<std::string> DataManager::getModelHeroLegs() const {
    return modelsCharacter.at("Hero legs");
}

std::vector<std::string> DataManager::getHero(bool withSword, bool withArmor) const {
    auto heroHead = getModelHeroHead();
    auto heroBody = getModelHeroBodyWait(withSword, withArmor);
    auto heroLegs = getModelHeroLegs();
    std::vector<std::string> mainHeroModel;
    mainHeroModel.reserve(heroHead.size() + heroBody.size() + heroLegs.size());
    std::move(heroHead.begin(),  heroHead.end(), std::back_inserter(mainHeroModel));
    std::move(heroBody.begin(),  heroBody.end(), std::back_inserter(mainHeroModel));
    std::move(heroLegs.begin(),  heroLegs.end(), std::back_inserter(mainHeroModel));
    LoggerPull::writeData("gameLogs",
                          LoggerDataAdapter<std::string>("Данные о модели героя получены"));
    return mainHeroModel;
}

void DataManager::uploadModels() {
    ModelDataReader reader;
    auto modelsData = reader.readXMLModelData(dataModelsPathFile);
    for(const auto& model : modelsData) {
        modelsCharacter[model.first] = model.second;
    }
}

std::vector<std::string> DataManager::getModelCharacter(const std::string &character) {
    if (modelsCharacter.count(character))
        return modelsCharacter[character];
    return {};
}

void DataManager::uploadParamsThing(const std::vector<Thing> &things) {
    for (const auto & thing : things) {
        if (thing.isHealThing()) {
            healThings.push_back(thing);
        } else {
            levelToThings[thing.getLevelThing()].push_back(thing);
        }
    }
}
