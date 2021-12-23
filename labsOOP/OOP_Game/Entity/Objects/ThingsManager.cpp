#include "ThingsManager.h"
#include "../../Logger/LoggerPull.h"
#include "../../Tools/SaveDataReader.h"
#include "../../Rules/DifficultDataReader.h"

ThingsManager::ThingsManager(const std::shared_ptr<Field> &field, std::map<CellPoint, Thing*> visualThingsPlaces,
                             std::map<CellPoint, Thing*> healthThingsPlaces)
        : field(field), visualThingsPlaces(visualThingsPlaces), nonVisualThingsPlaces(healthThingsPlaces) {}

void ThingsManager::generateVisualThing(const std::shared_ptr<DataManager> &dataManager) {
    constexpr auto getVectorFromMapPointThings = [](const std::map<CellPoint, Thing*> &table) {
        std::vector<Thing*> res(THING_OBJECT_SIZE - 1);
        for (auto &item: table)
            res[item.second->getTypeObject()] = item.second;
        return res;
    };
    CellPoint point = field->generateRandomFreePoint();
    auto things = getVectorFromMapPointThings(visualThingsPlaces);
    for (int i = 0; i < things.size(); ++i) {
        if (things[i] == nullptr &&
            std::find(field->getHero().getInventory().begin(), field->getHero().getInventory().end(),
                      dataManager->getThing(levelThings, i)) == field->getHero().getInventory().end()) {
            this->visualThingsPlaces[point] = dataManager->getThing(levelThings, i);
            field->setElem(point, CellObject(TypeCell::EMPTY, TypeObject::NOTHING, true));
            break;
        }
    }
}

void ThingsManager::checkThingsLevel(std::map<std::string, int> &achievements) {
    if (achievements.size() > 0 && levelThings == 1 && achievements.count("Monster") >= 3 && achievements.count("Archer") >= 1 &&
        achievements.count("Gargoyle") >= 1) {
        levelThings = 2;
    }
}


void ThingsManager::generateHealthThing(const std::shared_ptr<DataManager> &dataManager) {
    CellPoint point = field->generateRandomFreePoint();
    this->nonVisualThingsPlaces[point] = dataManager->getHealthThing();
    field->setElem(point, CellObject(TypeCell::EMPTY, TypeObject::NOTHING, true));
}

void ThingsManager::tryGenerateThing(MainHero &hero, std::shared_ptr<DataManager> &dataManager) {
    auto &achievements = hero.getCountKilledEnemy();
    const auto &heroInventory = hero.getInventory();

    if (field->getCountSteps() % timeBetweenGenerateHealThing == 0 &&
    hero.getHealth() * 100 / MainHero::MainHeroProperties::MAIN_HERO_MAX_HEALTH <= LOW_HEALTH_PERCENT &&
        std::count_if(nonVisualThingsPlaces.begin(), nonVisualThingsPlaces.end(),
                      [](const std::pair<CellPoint,Thing*> &place) { return place.second->isHealThing(); }) +
        std::count_if(heroInventory.begin(), heroInventory.end(),
                        [](const Thing* thing) { return thing->isHealThing(); }) <= cntHealThing) {
        generateHealthThing(dataManager);
        return;
    }
    checkThingsLevel(achievements);
    if (field->getCountSteps() % timeBetweenGenerateVisualThing == 0 &&
        visualThingsPlaces.size() <= ThingObject::THING_OBJECT_SIZE - 2) {
        generateVisualThing(dataManager);
    }
}

std::pair<bool, Thing*> ThingsManager::checkCellHasSmth(CellPoint point) {
    if (visualThingsPlaces.count(point) > 0) {
        return {true, visualThingsPlaces[point]};
    } else if (nonVisualThingsPlaces.count(point) > 0) {
        return {true, nonVisualThingsPlaces[point]};
    }
    return {false, nullptr};
}

void ThingsManager::deleteThingFromField(CellPoint point) {
    field->setElem(point, CellObject(field->getElem(point).getValue().getTypeCell(),
                                     field->getElem(point).getValue().getTypeObject(), false));
    if (visualThingsPlaces.count(point))
        visualThingsPlaces.erase(point);
    else if (nonVisualThingsPlaces.count(point))
        nonVisualThingsPlaces.erase(point);
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<CellPoint>(point, "Предмет на данной позиции был взят героем"));
}

void ThingsManager::setRules(int cntHealThing, int timeBetweenGenerateVisualThing, int timeBetweenGenerateHealThing) {
    this->cntHealThing = cntHealThing;
    this->timeBetweenGenerateVisualThing = timeBetweenGenerateVisualThing;
    this->timeBetweenGenerateHealThing = timeBetweenGenerateHealThing;

}

std::vector<std::string> ThingsManager::prepareDataToSave() const {
    std::vector<std::string> data;
    data.emplace_back("// расположение вещей (уровень, позиция xy)\n");
    data.emplace_back("thingsPosLevel\n");
    data.push_back(SaveDataReader::START_TAG + "\n");
    for (const auto &thingPlace: visualThingsPlaces) {
        data.push_back(thingPlace.second->getStrType() + " " + std::to_string(thingPlace.second->getLevelThing()) +
            " " + std::to_string(thingPlace.first.getX()) + " " + std::to_string(thingPlace.first.getY()) + "\n");
    }
    for (const auto &thingPlace: nonVisualThingsPlaces) {
        data.push_back(thingPlace.second->getStrType() + " " + std::to_string(thingPlace.second->getLevelThing()) +
            " " + std::to_string(thingPlace.first.getX()) + " " + std::to_string(thingPlace.first.getY()) + "\n");
    }
    data.push_back(SaveDataReader::END_TAG + "\n");
    data.emplace_back("// уровень героя\n");
    data.push_back("heroLevel " + std::to_string(levelThings) + "\n");
    return data;
}

void ThingsManager::reeditThingsManager(const SaveDataAdapter &adapter) {
    for (auto &thingsPlace: visualThingsPlaces) {
        delete thingsPlace.second;
    }
    for (auto &thingsPlace: nonVisualThingsPlaces) {
        delete thingsPlace.second;
    }
    nonVisualThingsPlaces.clear();
    visualThingsPlaces.clear();
    levelThings = adapter.getHeroLevel();
    for (const auto &thingsPos: adapter.getThingsPos()) {
        if(field->getDataManager()->getThing(thingsPos.second.first, DifficultDataReader::getTypeObjectFromStr(thingsPos.first))->isVisualThing())
            visualThingsPlaces[thingsPos.second.second] = field->getDataManager()->getThing(thingsPos.second.first, DifficultDataReader::getTypeObjectFromStr(thingsPos.first));
        else
            nonVisualThingsPlaces[thingsPos.second.second] = field->getDataManager()->getThing(thingsPos.second.first, DifficultDataReader::getTypeObjectFromStr(thingsPos.first));
        field->setElem(thingsPos.second.second, CellObject(field->getElem(thingsPos.second.second).getValue().getTypeCell(),field->getElem(thingsPos.second.second).getValue().getTypeObject(), true));
    }
}
