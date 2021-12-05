#pragma once

#include "CharacterProperties.h"
#include "ThingProperties.h"
#include "RulesChecker.h"

class DifficultPreset : public RulesChecker {
    std::unordered_map<std::string, CharacterProperties> charactersParams;
    std::unordered_map<std::string, ThingProperties> thingsParams;
    std::unordered_map<std::string, int> cntKilledEnemy;
    int cntThingsRightLevel;
    int cntEnemyOnField;
    int levelAllThings;
    int cntHealThing;
    int timeBetweenGenerateEnemy;
    int timeBetweenGenerateVisualThing;
    int timeBetweenGenerateHealThing;
public:
    void recalcCntThingsRightLevel() {
        cntThingsRightLevel = std::count_if(thingsParams.begin(), thingsParams.end(),
                                            [this](std::pair<std::string, ThingProperties> thing){
            return thing.second.level == levelAllThings;
        });
    }
    bool checkHero(MainHero& hero) const override {
        auto cntKilled = hero.getCountKilledEnemy();
        auto requiredCntKilled = cntKilledEnemy;
        for (const auto &killed: cntKilled) {
//        if (killed.second > 0) // Для демонстрации
//            return true;
            if (requiredCntKilled[killed.first] > killed.second)
                return false;
        }
        auto heroThing = hero.getInventory();
        int cntSuitableThings = 0;
        for (const auto &thing: heroThing) {
            if (thing->getLevelThing() != 0 && thing->getLevelThing() < levelAllThings)
                return false;
            cntSuitableThings += thing->getLevelThing() != 0;
        }
        if (cntSuitableThings < cntThingsRightLevel)
            return false;
        return true;
    }
    bool checkField(Field &field) const override {
        return true;
    }
    const std::unordered_map<std::string, CharacterProperties> &getCharactersParams() const {
        return charactersParams;
    }
    const std::unordered_map<std::string, ThingProperties> &getThingsParams() const {
        return thingsParams;
    }
    const std::unordered_map<std::string, int> &getCntKilledEnemy() const {
        return cntKilledEnemy;
    }
    int getCntEnemyOnField() const {
        return cntEnemyOnField;
    }
    int getLevelAllThings() const {
        return levelAllThings;
    }
    int getCntHealThing() const {
        return cntHealThing;
    }
    int getTimeBetweenGenerateEnemy() const {
        return timeBetweenGenerateEnemy;
    }
    int getTimeBetweenGenerateVisualThing() const {
        return timeBetweenGenerateVisualThing;
    }
    int getTimeBetweenGenerateHealThing() const {
        return timeBetweenGenerateHealThing;
    }
    void setCharactersParams(const std::unordered_map<std::string, CharacterProperties> &charactersParams) {
        DifficultPreset::charactersParams = charactersParams;
    }
    void setThingsParams(const std::unordered_map<std::string, ThingProperties> &thingsParams) {
        DifficultPreset::thingsParams = thingsParams;
        recalcCntThingsRightLevel();
    }
    void setCntKilledEnemy(const std::unordered_map<std::string, int> &cntKilledEnemy) {
        DifficultPreset::cntKilledEnemy = cntKilledEnemy;
    }
    void setCntEnemyOnField(int cntEnemyOnField) {
        DifficultPreset::cntEnemyOnField = cntEnemyOnField;
    }
    void setLevelAllThings(int levelAllThings) {
        DifficultPreset::levelAllThings = levelAllThings;
        recalcCntThingsRightLevel();
    }
    void setCntHealThing(int cntHealThing) {
        DifficultPreset::cntHealThing = cntHealThing;
    }
    void setTimeBetweenGenerateEnemy(int timeBetweenGenerateEnemy) {
        DifficultPreset::timeBetweenGenerateEnemy = timeBetweenGenerateEnemy;
    }
    void setTimeBetweenGenerateVisualThing(int timeBetweenGenerateVisualThing) {
        DifficultPreset::timeBetweenGenerateVisualThing = timeBetweenGenerateVisualThing;
    }
    void setTimeBetweenGenerateHealThing(int timeBetweenGenerateHealThing) {
        DifficultPreset::timeBetweenGenerateHealThing = timeBetweenGenerateHealThing;
    }
};
