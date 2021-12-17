#include "DifficultPreset.h"

bool DifficultPreset::checkHero(MainHero &hero) const {
    auto cntKilled = hero.getCountKilledEnemy();
    auto requiredCntKilled = getCntKilledEnemy();
    for (const auto &killed: cntKilled) {
          if (killed.second > 0) // Для демонстрации
              return true;
        if (requiredCntKilled[killed.first] > killed.second)
            return false;
    }
    auto heroThing = hero.getInventory();
    int cntSuitableThings = 0;
    for (const auto &thing: heroThing) {
        if (thing->getLevelThing() != 0 && thing->getLevelThing() < getLevelAllThings())
            return false;
        cntSuitableThings += thing->getLevelThing() != 0;
    }
    if (cntSuitableThings < getCntThingsRightLevel())
        return false;
    return true;
}

bool DifficultPreset::checkField(Field &field) const {
    return true;
}

void DifficultPreset::recalcCntThingsRightLevel() {
    cntThingsRightLevel = std::count_if(thingsParams.begin(), thingsParams.end(),
                                        [this](const std::pair<std::string, ThingProperties> &thing){
                                            return thing.second.getLevel() == levelAllThings;
                                        });
}

const std::unordered_map<std::string, CharacterProperties> &DifficultPreset::getCharactersParams() const {
    return charactersParams;
}

const std::unordered_map<std::string, ThingProperties> &DifficultPreset::getThingsParams() const {
    return thingsParams;
}

const std::unordered_map<std::string, int> &DifficultPreset::getCntKilledEnemy() const {
    return cntKilledEnemy;
}

int DifficultPreset::getCntEnemyOnField() const {
    return cntEnemyOnField;
}

int DifficultPreset::getLevelAllThings() const {
    return levelAllThings;
}

int DifficultPreset::getCntThingsRightLevel() const {
    return cntThingsRightLevel;
}

int DifficultPreset::getCntHealThing() const {
    return cntHealThing;
}

int DifficultPreset::getTimeBetweenGenerateEnemy() const {
    return timeBetweenGenerateEnemy;
}

int DifficultPreset::getTimeBetweenGenerateVisualThing() const {
    return timeBetweenGenerateVisualThing;
}

int DifficultPreset::getTimeBetweenGenerateHealThing() const {
    return timeBetweenGenerateHealThing;
}

void DifficultPreset::setCharactersParams(const std::unordered_map<std::string, CharacterProperties> &charactersParams) {
    DifficultPreset::charactersParams = charactersParams;
}

void DifficultPreset::setThingsParams(const std::unordered_map<std::string, ThingProperties> &thingsParams) {
    DifficultPreset::thingsParams = thingsParams;
    recalcCntThingsRightLevel();
}

void DifficultPreset::setCntKilledEnemy(const std::unordered_map<std::string, int> &cntKilledEnemy) {
    DifficultPreset::cntKilledEnemy = cntKilledEnemy;
}

void DifficultPreset::setCntEnemyOnField(int cntEnemyOnField) {
    DifficultPreset::cntEnemyOnField = cntEnemyOnField;
}

void DifficultPreset::setLevelAllThings(int levelAllThings) {
    DifficultPreset::levelAllThings = levelAllThings;
    recalcCntThingsRightLevel();
}

void DifficultPreset::setCntHealThing(int cntHealThing) {
    DifficultPreset::cntHealThing = cntHealThing;
}

void DifficultPreset::setTimeBetweenGenerateEnemy(int timeBetweenGenerateEnemy) {
    DifficultPreset::timeBetweenGenerateEnemy = timeBetweenGenerateEnemy;
}

void DifficultPreset::setTimeBetweenGenerateVisualThing(int timeBetweenGenerateVisualThing) {
    DifficultPreset::timeBetweenGenerateVisualThing = timeBetweenGenerateVisualThing;
}

void DifficultPreset::setTimeBetweenGenerateHealThing(int timeBetweenGenerateHealThing) {
    DifficultPreset::timeBetweenGenerateHealThing = timeBetweenGenerateHealThing;
}
