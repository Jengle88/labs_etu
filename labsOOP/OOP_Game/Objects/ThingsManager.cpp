#include "ThingsManager.h"

ThingsManager::ThingsManager(Field *field, std::map<CellPoint, Thing> visualThingsPlaces,
                             std::map<CellPoint, Thing> healthThingsPlaces)
        : field(field), visualThingsPlaces(visualThingsPlaces), healthThingsPlaces(healthThingsPlaces){}

void ThingsManager::generateVisualThing(DataManager *dataManager) {
    constexpr auto getVectorFromMapPointThings = [](const std::map<CellPoint, Thing>& table) {
        std::vector<Thing> res(THING_OBJECT_SIZE - 1);
        for(auto &item : table)
            res[item.second.getThingObject()] = item.second;
        return res;
    };
    CellPoint point = field->generateRandomFreePoint();
    auto things = getVectorFromMapPointThings(visualThingsPlaces);
    for (int i = 0; i < things.size(); ++i) {
        if (things[i].getNameThing().empty() && std::find(field->getHero().getInventory().begin(), field->getHero().getInventory().end(), dataManager->getThing(levelThings, i)) == field->getHero().getInventory().end()) {
            this->visualThingsPlaces[point] = dataManager->getThing(levelThings, i);
            field->setElem(point, CellObject(TypeCell::EMPTY, TypeObject::NOTHING, true));
            break;
        }
    }
}

void ThingsManager::checkThingsLevel(std::map<std::string, int> &achievements) {
    if (levelThings == 1 && achievements["Monster"] >= 3 && achievements["Archer"] >= 1 && achievements["Gargoyle"] >= 1) {
        levelThings = 2;
    }
}


void ThingsManager::generateHealthThing(DataManager *dataManager) {
    CellPoint point = field->generateRandomFreePoint();
    this->healthThingsPlaces[point] = dataManager->getHealthThing();
    field->setElem(point, CellObject(TypeCell::EMPTY, TypeObject::NOTHING, true));
}

void ThingsManager::tryGenerateThing(MainHero& hero, DataManager *dataManager) {
    field->incCountSteps();
    auto& achievements = hero.getCountKilledEnemy();
    const auto& heroInventory = hero.getInventory();

    if (hero.getHealth() * 100 / MainHero::MainHeroProperties::MAIN_HERO_MAX_HEALTH <= LOW_HEALTH_PERCENT && healthThingsPlaces.size()
                                                                               + std::count_if(heroInventory.begin(),  heroInventory.end(),
                                                                                               [](const Thing& thing) {return thing.getThingObject() == ThingObject::POTION_HEAL;}) <= MAX_COUNT_HEALTH_THINGS) {
        generateHealthThing(dataManager);
        return;
    }
    checkThingsLevel(achievements);
    if (field->getCountSteps() % TIME_BETWEEN_GENERATE_THING == 0 && visualThingsPlaces.size() <= ThingObject::THING_OBJECT_SIZE - 2) {
        generateVisualThing(dataManager);
    }
}

std::pair<bool, Thing> ThingsManager::checkCellHasSmth(CellPoint point) {
    if (visualThingsPlaces.count(point) > 0) {
        return {true, visualThingsPlaces[point]};
    } else if (healthThingsPlaces.count(point) > 0) {
        return {true, healthThingsPlaces[point]};
    }
    return {false, Thing()};
}

void ThingsManager::deleteThingFromField(CellPoint point) {
    field->setElem(point, CellObject(field->getElem(point).getValue().getTypeCell(), field->getElem(point).getValue().getTypeObject(), false));
    if (visualThingsPlaces.count(point))
        visualThingsPlaces.erase(point);
    else if (healthThingsPlaces.count(point))
        healthThingsPlaces.erase(point);

}