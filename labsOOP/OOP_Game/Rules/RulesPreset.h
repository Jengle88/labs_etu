#pragma once

#include "CharacterProperties.h"
#include "ThingProperties.h"

class RulesPreset {
    std::unordered_map<std::string, CharacterProperties> charactersParams;
    std::unordered_map<std::string, ThingProperties> thingParams;
    std::unordered_map<std::string, int> cntKilledEnemy;
    int cntEnemyOnField;
    int levelAllThings;
    int cntHealThing;
    int timeBetweenGenerateEnemy;
    int timeBetweenGenerateVisualThing;
    int timeBetweenGenerateHealThing;
public:
    RulesPreset(const std::unordered_map<std::string, CharacterProperties> &charactersParams,
                const std::unordered_map<std::string, ThingProperties> &thingParams,
                int cntEnemyOnField, const std::unordered_map<std::string, int> &cntKilledEnemy, int levelAllThings,
                int cntHealThing, int timeBetweenGenerateEnemy, int timeBetweenGenerateVisualThing,
                int timeBetweenGenerateHealThing)
            : charactersParams(charactersParams),
              thingParams(thingParams),
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

    const std::unordered_map<std::string, ThingProperties> &getThingParams() const {
        return thingParams;
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
