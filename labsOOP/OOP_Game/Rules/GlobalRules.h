#pragma once
#include <vector>
#include <map>
#include "RulesPreset.h"
#include "../Characters/MainHero.h"

template<RulesPreset & rulesPreset>
class GlobalRules {
public:
    const std::vector<CharacterRules>& getCharacterRules() const;
    const std::vector<ThingRules>& getThingRules() const;
    const std::map<std::string, int>& getCntGenerateEnemyOnField() const;
    bool checkFinishCondition(MainHero& mainHero);

};

template<RulesPreset &rulesPreset>
const std::vector<CharacterRules> &GlobalRules<rulesPreset>::getCharacterRules() const {
    return rulesPreset.getCharactersParams();
}

template<RulesPreset &rulesPreset>
const std::vector<ThingRules> &GlobalRules<rulesPreset>::getThingRules() const {
    return rulesPreset.getThingParams();
}

template<RulesPreset &rulesPreset>
const std::map<std::string, int> &GlobalRules<rulesPreset>::getCntGenerateEnemyOnField() const {
    return rulesPreset.getCntGenerateEnemyOnField();
}

template<RulesPreset &rulesPreset>
bool GlobalRules<rulesPreset>::checkFinishCondition(MainHero &mainHero) {
    auto cntKilled = mainHero.getCountKilledEnemy();
    auto requiredCntKilled = rulesPreset.getCntKilledEnemy();
    for (const auto &killed: cntKilled) {
        if (requiredCntKilled[killed.first] > killed.second)
            return false;
    }
    auto heroThing = mainHero.getInventory();
    for (const auto &thing: heroThing) {
        if (thing.getLevelThing() < rulesPreset.getLevelAllThings())
            return false;
    }
    return true;
}



