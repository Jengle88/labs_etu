#pragma once

#include "CharacterProperties.h"
#include "ThingProperties.h"

class RulesPreset {
    std::unordered_map<std::string, CharacterProperties> charactersParams;
    std::unordered_map<std::string, ThingProperties> thingsParams;
    std::unordered_map<std::string, int> cntKilledEnemy;
    int cntEnemyOnField;
    int levelAllThings;
    int cntHealThing;
    int timeBetweenGenerateEnemy;
    int timeBetweenGenerateVisualThing;
    int timeBetweenGenerateHealThing;
public:
//    RulesPreset(const std::unordered_map<std::string, CharacterProperties> &charactersParams,
//                const std::unordered_map<std::string, ThingProperties> &thingsParams,
//                int cntEnemyOnField, const std::unordered_map<std::string, int> &cntKilledEnemy, int levelAllThings,
//                int cntHealThing, int timeBetweenGenerateEnemy, int timeBetweenGenerateVisualThing,
//                int timeBetweenGenerateHealThing)
//            : charactersParams(charactersParams),
//              thingsParams(thingsParams),
//              cntEnemyOnField(cntEnemyOnField),
//              cntKilledEnemy(cntKilledEnemy),
//              levelAllThings(levelAllThings),
//              cntHealThing(cntHealThing),
//              timeBetweenGenerateEnemy(timeBetweenGenerateEnemy),
//              timeBetweenGenerateVisualThing(timeBetweenGenerateVisualThing),
//              timeBetweenGenerateHealThing(timeBetweenGenerateHealThing) {}

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
        RulesPreset::charactersParams = charactersParams;
    }

    void setThingsParams(const std::unordered_map<std::string, ThingProperties> &thingsParams) {
        RulesPreset::thingsParams = thingsParams;
    }

    void setCntKilledEnemy(const std::unordered_map<std::string, int> &cntKilledEnemy) {
        RulesPreset::cntKilledEnemy = cntKilledEnemy;
    }

    void setCntEnemyOnField(int cntEnemyOnField) {
        RulesPreset::cntEnemyOnField = cntEnemyOnField;
    }

    void setLevelAllThings(int levelAllThings) {
        RulesPreset::levelAllThings = levelAllThings;
    }

    void setCntHealThing(int cntHealThing) {
        RulesPreset::cntHealThing = cntHealThing;
    }

    void setTimeBetweenGenerateEnemy(int timeBetweenGenerateEnemy) {
        RulesPreset::timeBetweenGenerateEnemy = timeBetweenGenerateEnemy;
    }

    void setTimeBetweenGenerateVisualThing(int timeBetweenGenerateVisualThing) {
        RulesPreset::timeBetweenGenerateVisualThing = timeBetweenGenerateVisualThing;
    }

    void setTimeBetweenGenerateHealThing(int timeBetweenGenerateHealThing) {
        RulesPreset::timeBetweenGenerateHealThing = timeBetweenGenerateHealThing;
    }
};
