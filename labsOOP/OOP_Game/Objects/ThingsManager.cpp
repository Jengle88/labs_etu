#include "ThingsManager.h"

ThingsManager::ThingsManager(Field *field, std::map<CellPoint, Thing> visualThingsPlaces,
                             std::map<CellPoint, Thing> healthThingsPlaces)
        : field(field), visualThingsPlaces(visualThingsPlaces), healthThingsPlaces(healthThingsPlaces), dataManager(DataManager()){}

void ThingsManager::generateVisualThing() {
    constexpr auto getVectorFromMapPointThings = [](const std::map<CellPoint, Thing>& table) {
        std::vector<Thing> res(THING_OBJECT_SIZE - 1);
        for(auto &item : table)
            res[item.second.getThingObject()] = item.second;
        return res;
    };
    CellPoint point = field->generateRandomFreePoint();
    auto things = getVectorFromMapPointThings(visualThingsPlaces);
    for (int i = 0; i < things.size(); ++i) {
        if (things[i].getNameThing().empty() && std::find(field->getHero().getInventory().begin(), field->getHero().getInventory().end(), dataManager.getThing(levelThings, i)) == field->getHero().getInventory().end()) {
            this->visualThingsPlaces[point] = dataManager.getThing(levelThings, i);
            field->setElem(point, CellObject(TypeCell::EMPTY, TypeObject::NOTHING, true));
            break;
        }
    }
}

void ThingsManager::checkThingsLevel(const std::vector<int> &achievements) {
    if (levelThings == 1 && achievements[CharacterType::MONSTER] >= 3 && achievements[CharacterType::SKELETON_ARCHER] >= 1 && achievements[CharacterType::GARGOYLE] >= 1) {
        levelThings = 2;
    }
    if (levelThings == 2 && achievements[CharacterType::MONSTER] >= 7 && achievements[CharacterType::SKELETON_ARCHER] >= 5 && achievements[CharacterType::GARGOYLE] >= 2) {
        levelThings = 3;
    }
}


void ThingsManager::generateHealthThing() {
    CellPoint point = field->generateRandomFreePoint();
    this->healthThingsPlaces[point] = Thing("Лечебный эликсир", {0,0,0,20}, ThingObject::POTION_HEAL, false);
    field->setElem(point, CellObject(TypeCell::EMPTY, TypeObject::NOTHING, true));
}

void ThingsManager::tryGenerateThing(const MainHero& hero) {
    field->incCountSteps();
    const auto& achievements = hero.getCountKilledEnemy();
    const auto& heroInventory = hero.getInventory();

    if (hero.getHealth() * 100 / CHARACTER_MAX_HEALTH <= LOW_HEALTH_PERCENT && healthThingsPlaces.size()
    + std::count_if(heroInventory.begin(),  heroInventory.end(),
                    [](const Thing& thing) {return thing.getThingObject() == ThingObject::POTION_HEAL;}) <= MAX_COUNT_HEALTH_THINGS) {
        generateHealthThing();
        return;
    }
    checkThingsLevel(achievements);
    if (field->getCountSteps() % TIME_BETWEEN_GENERATE_THING == 0 && visualThingsPlaces.size() <= ThingObject::THING_OBJECT_SIZE - 2) {
        generateVisualThing();
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
