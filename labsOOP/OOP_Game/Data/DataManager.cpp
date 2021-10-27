#include "DataManager.h"
#include "../Tools/ModelDataReader.h"

DataManager::DataManager() {
    levelToThings[1] = {
            Thing("Железный нагрудник", {0, 1, 0, 0}, ThingObject::ARMOR),
            Thing("Железный меч", {1.2, 0, 0, 0}, ThingObject::SWORD)
    };
    levelToThings[2] = {
            Thing("Стальной нагрудник", {0, 1.3, 0, 0}, ThingObject::ARMOR),
            Thing("Стальной меч", {1.6, 0, 0, 0}, ThingObject::SWORD)
    };
}

Thing DataManager::getThing(int level, int typeThing) {
    return levelToThings[level][typeThing];
}

Thing DataManager::getHealthThing() const {
    return Thing("Лечебный эликсир", {0,0,0,20}, ThingObject::POTION_HEAL);
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
