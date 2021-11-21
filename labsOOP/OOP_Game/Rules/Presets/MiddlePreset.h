#include "../CharacterRules.h"
#include "../RulesPresets.h"
#include "../ThingRules.h"


class MiddlePreset : public RulesPresets {
public:
    MiddlePreset(const std::vector<CharacterRules> &charactersParams = {
            CharacterRules("MainHero", 100, 1.3, 1.6, 1.3, 1, 1.75, 0.6, -1, 1, -1),
            CharacterRules("Monster", 65, 0.8, 0.8, 0.75, 1, 1.2, 0.85, 70, 1, 33),
            CharacterRules("Archer", 62, 0.9, 0.75, 0.8, 1, 1.25, 0.8, 70, 1, 33),
            CharacterRules("Gargoyle", 75, 0.95, 0.85, 0.73, 1, 1.3, 0.7, 75, 1, 33),
    },
                 const std::vector<ThingRules> &thingParams = {
                         ThingRules("Железный нагрудник", {
                                 {"damage",     0},
                                 {"protection", 1.3},
                                 {"luck",       0},
                                 {"health",     0}}, 1, true, ThingObject::ARMOR),
                         ThingRules("Железный меч", {
                                 {"damage",     1.5},
                                 {"protection", 0},
                                 {"luck",       0},
                                 {"health",     0}}, 1, true, ThingObject::SWORD),
                         ThingRules("Стальной нагрудник", {
                                 {"damage",     0},
                                 {"protection", 1.7},
                                 {"luck",       0},
                                 {"health",     0}}, 2, true, ThingObject::ARMOR),
                         ThingRules("Стальной меч", {
                                 {"damage",     1.9},
                                 {"protection", 0},
                                 {"luck",       0},
                                 {"health",     0}}, 2, true, ThingObject::SWORD),
                         ThingRules("Лечебный эликсир", {
                                 {"damage",     0},
                                 {"protection", 0},
                                 {"luck",       0},
                                 {"health",     30}}, 0, false, ThingObject::POTION_HEAL)
                 },
                 const std::map<std::string, int> &cntGenerateEnemyOnField = {
                         {"Monster",  3},
                         {"Archer",   2},
                         {"Gargoyle", 1}
                 },
                 const std::map<std::string, int> &cntKilledEnemy = {
                         {"Monster",  4},
                         {"Archer",   3},
                         {"Gargoyle", 1}
                 },
                 int levelAllThings = 1,
                 int timeBetweenGenerateVisualThing = 13,
                 int timeBetweenGenerateHealThing = 10
    ) : RulesPresets(
            charactersParams, thingParams, cntGenerateEnemyOnField, cntKilledEnemy, levelAllThings,
            timeBetweenGenerateVisualThing, timeBetweenGenerateHealThing) {}
};
