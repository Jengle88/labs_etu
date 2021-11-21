#pragma once

#include "CharacterRules.h"
#include "ThingRules.h"

class RulesPresets {
    std::vector<CharacterRules> charactersParams;
    std::vector<ThingRules> thingParams;
    std::map<std::string, int> cntGenerateEnemyOnField;
    std::map<std::string, int> cntKilledEnemy;
    int levelAllThings;
    int timeBetweenGenerateVisualThing;
    int timeBetweenGenerateHealThing;
public:
    RulesPresets(const std::vector<CharacterRules> &charactersParams, const std::vector<ThingRules> &thingParams,
                 const std::map<std::string, int> &cntGenerateEnemyOnField,
                 const std::map<std::string, int> &cntKilledEnemy, int levelAllThings,
                 int timeBetweenGenerateVisualThing, int timeBetweenGenerateHealThing)
            : charactersParams(charactersParams),
              thingParams(thingParams),
              cntGenerateEnemyOnField(cntGenerateEnemyOnField),
              cntKilledEnemy(cntKilledEnemy),
              levelAllThings(levelAllThings),
              timeBetweenGenerateVisualThing(timeBetweenGenerateVisualThing),
              timeBetweenGenerateHealThing(timeBetweenGenerateHealThing) {}

    const std::vector<CharacterRules> &getCharactersParams() const {
        return charactersParams;
    }

    const std::vector<ThingRules> &getThingParams() const {
        return thingParams;
    }

    const std::map<std::string, int> &getCntGenerateEnemyOnField() const {
        return cntGenerateEnemyOnField;
    }

    const std::map<std::string, int> &getCntKilledEnemy() const {
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
