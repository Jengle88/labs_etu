#pragma once
#include "CharacterRules.h"
#include "ThingRules.h"

class RulesPresets {
    std::vector<CharacterRules> charactersParams;
    std::vector<ThingRules> thingParams;
    std::map<std::string, int> cntKilledEnemy;
    std::map<std::string, int> cntGenerateEnemyOnField;
    int levelAllThings;
};
