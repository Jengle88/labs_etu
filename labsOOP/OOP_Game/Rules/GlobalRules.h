#pragma once
#include <vector>
#include <map>
#include "RulesPreset.h"
#include "../Characters/MainHero.h"

template<RulesPreset & rulesPreset>
class GlobalRules {
public:
    bool checkFinishCondition(MainHero& mainHero);

};

template<RulesPreset &rulesPreset>
bool GlobalRules<rulesPreset>::checkFinishCondition(MainHero &mainHero) {
    auto cntKilled = mainHero.getCountKilledEnemy();
    auto requiredCntKilled = rulesPreset.getCntKilledEnemy();
    for (const auto &killed: cntKilled) {
//        if (killed.second > 0) // Для демонстрации
//            return true;
        if (requiredCntKilled[killed.first] > killed.second)
            return false;
    }
    auto heroThing = mainHero.getInventory();
    for (const auto &thing: heroThing) {
        if (thing->getLevelThing() < rulesPreset.getLevelAllThings() && thing->getLevelThing() != 0)
            return false;
    }
    return true;
}



