#include "ThingsManager.h"

ThingsManager::ThingsManager(Field *field, std::map<CellPoint, Thing> visualThingsPlaces,
                             std::map<CellPoint, Thing> healthThingsPlaces)
        : field(field), visualThingsPlaces(visualThingsPlaces), healthThingsPlaces(healthThingsPlaces), dataManager(DataManager()){}

void ThingsManager::generateThing(const MainHero& hero) {
    const auto& achievements = hero.getCountKilledEnemy();
    if (hero.getHealth() * 100 / MAX_HEALTH <= LOW_HEALTH_PERCENT && healthThingsPlaces.size() <= MAX_COUNT_HEALTH_THINGS) {
        generateHealthThing();
    }
    checkThingsLevel(achievements);
    if (counterSteps % STEP_MULTIPLICITY == 0 && visualThingsPlaces.size() <= ThingObject::THING_OBJECT_SIZE - 2) {
        generateVisualThing();
    }
}

void ThingsManager::checkThingsLevel(const std::vector<int> &achievements) {
    if (levelThings == 1 && achievements[EnemyType::MONSTER] >= 3 && achievements[EnemyType::SKELETON_ARCHER] >= 1 && achievements[EnemyType::GARGOYLE] >= 1) {
        levelThings = 2;
    }
    if (levelThings == 2 && achievements[EnemyType::MONSTER] >= 7 && achievements[EnemyType::SKELETON_ARCHER] >= 5 && achievements[EnemyType::GARGOYLE] >= 2) {
        levelThings = 3;
    }
}

void ThingsManager::generateHealthThing() {
    CellPoint point = field->generateRandomFreePoint();
    this->healthThingsPlaces[point] = Thing("Лечебный эликсир", {0,0,0,0,20}, ThingObject::POTION_HEAL, false, -1);
    field->setElem(point, CellObject(TypeCell::EMPTY, TypeObject::NOTHING, true));
}

void ThingsManager::incCountSteps() {
    counterSteps++;
}

void ThingsManager::generateVisualThing() {
    constexpr auto getVectorFromMapPointThings = [](const std::map<CellPoint, Thing>& table) {
        std::vector<Thing> res(THING_OBJECT_SIZE - 2);
        for(auto &item : table)
            res[item.second.getThingObject()] = item.second;
        return res;
    };
    CellPoint point = field->generateRandomFreePoint();
    auto things = getVectorFromMapPointThings(visualThingsPlaces);
    for (int i = 0; i < things.size(); ++i) {
        if (things[i].getNameThing().empty()) {
            this->visualThingsPlaces[point] = dataManager.getThing(levelThings, i);
            field->setElem(point, CellObject(TypeCell::EMPTY, TypeObject::NOTHING, true));
            break;
        }
    }
}
