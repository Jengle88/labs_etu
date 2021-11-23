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
    RulesPreset(const std::unordered_map<std::string, CharacterProperties> &charactersParams,
                const std::unordered_map<std::string, ThingProperties> &thingsParams,
                int cntEnemyOnField, const std::unordered_map<std::string, int> &cntKilledEnemy, int levelAllThings,
                int cntHealThing, int timeBetweenGenerateEnemy, int timeBetweenGenerateVisualThing,
                int timeBetweenGenerateHealThing)
            : charactersParams(charactersParams),
              thingsParams(thingsParams),
              cntEnemyOnField(cntEnemyOnField),
              cntKilledEnemy(cntKilledEnemy),
              levelAllThings(levelAllThings),
              cntHealThing(cntHealThing),
              timeBetweenGenerateEnemy(timeBetweenGenerateEnemy),
              timeBetweenGenerateVisualThing(timeBetweenGenerateVisualThing),
              timeBetweenGenerateHealThing(timeBetweenGenerateHealThing) {}

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
};
