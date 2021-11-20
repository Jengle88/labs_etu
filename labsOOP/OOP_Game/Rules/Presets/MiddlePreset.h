#include "../CharacterRules.h"
#include "../RulesPresets.h"
#include "../ThingRules.h"


class MiddlePreset : public RulesPresets {
    std::vector <CharacterRules> charactersParams{
            CharacterRules("MainHero", 100, 1.3, 1.6, 1.3, 1, 1.75, 0.6, -1, 1, -1),
            CharacterRules("Monster", 65, 0.8, 0.8, 0.75, 1, 1.2, 0.85, 70, 1, 33),
            CharacterRules("Archer", 62, 0.9, 0.75, 0.8, 1, 1.25, 0.8, 70, 1, 33),
            CharacterRules("Gargoyle", 75, 0.95, 0.75, 0.73, 1, 1.15, 0.8, 65, 1, 33),
    };
    std::vector <ThingRules> thingParams{
            ThingRules("Железный нагрудник", {
                    {"damage",     0},
                    {"protection", 1.5},
                    {"luck",       0},
                    {"health",     0}}, 1, true, ThingObject::ARMOR),
            ThingRules("Железный меч", {
                    {"damage",     1.8},
                    {"protection", 0},
                    {"luck",       0},
                    {"health",     0}}, 1, true, ThingObject::SWORD),
            ThingRules("Стальной нагрудник", {
                    {"damage",     0},
                    {"protection", 2},
                    {"luck",       0},
                    {"health",     0}}, 2, true, ThingObject::ARMOR),
            ThingRules("Стальной меч", {
                    {"damage",     2.1},
                    {"protection", 0},
                    {"luck",       0},
                    {"health",     0}}, 2, true, ThingObject::SWORD),
            ThingRules("Лечебный эликсир", {
                    {"damage",     0},
                    {"protection", 0},
                    {"luck",       0},
                    {"health",     40}}, 0, false, ThingObject::POTION_HEAL)
    };
    std::map<std::string, int> cntKilledEnemy{
            {"Monster",  2},
            {"Archer",   1},
            {"Gargoyle", 0}
    };
    std::map<std::string, int> cntGenerateEnemyOnField{
            {"Monster",  3},
            {"Archer",   2},
            {"Gargoyle", 1}
    };
    int levelAllThings = 0;
};
