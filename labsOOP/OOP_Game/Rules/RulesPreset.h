#pragma once

#include "CharacterRules.h"
#include "ThingRules.h"

class RulesPreset {
    std::unordered_map<std::string, CharacterRules> charactersParams;
    std::unordered_map<std::string, ThingRules> thingParams;
    std::unordered_map<std::string, int> cntGenerateEnemyOnField;
    std::unordered_map<std::string, int> cntKilledEnemy;
    int levelAllThings;
    int timeBetweenGenerateVisualThing;
    int timeBetweenGenerateHealThing;
public:
    RulesPreset(const std::unordered_map<std::string,CharacterRules> &charactersParams, const std::unordered_map<std::string,ThingRules> &thingParams,
                 const std::unordered_map<std::string, int> &cntGenerateEnemyOnField,
                 const std::unordered_map<std::string, int> &cntKilledEnemy, int levelAllThings,
                 int timeBetweenGenerateVisualThing, int timeBetweenGenerateHealThing)
            : charactersParams(charactersParams),
              thingParams(thingParams),
              cntGenerateEnemyOnField(cntGenerateEnemyOnField),
              cntKilledEnemy(cntKilledEnemy),
              levelAllThings(levelAllThings),
              timeBetweenGenerateVisualThing(timeBetweenGenerateVisualThing),
              timeBetweenGenerateHealThing(timeBetweenGenerateHealThing) {}

    const std::unordered_map<std::string, CharacterRules> &getCharactersParams() const {
        return charactersParams;
    }

    const std::unordered_map<std::string, ThingRules> &getThingParams() const {
        return thingParams;
    }

    const std::unordered_map<std::string, int> &getCntGenerateEnemyOnField() const {
        return cntGenerateEnemyOnField;
    }

    const std::unordered_map<std::string, int> &getCntKilledEnemy() const {
        return cntKilledEnemy;
    }

    int getLevelAllThings() const {
        return levelAllThings;
    }

    int getTimeBetweenGenerateVisualThing() const {
        return timeBetweenGenerateVisualThing;
    }

    int getTimeBetweenGenerateHealThing() const {
        return timeBetweenGenerateHealThing;
    }
};
