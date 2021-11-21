#include "../RulesPreset.h"
#include "../ThingProperties.h"

class EasyPreset : public RulesPreset {
public:
    explicit EasyPreset(const std::unordered_map<std::string, CharacterProperties> &charactersParams = {
            {"MainHero", CharacterProperties("MainHero", 100, 1.2, 1.2, 1.2, 1, 2, 0.5, -1, 1, -1)},
            {"Monster",  CharacterProperties("Monster", 60, 0.7, 0.8, 0.7, 1, 1.1, 0.9, 60, 1, 33)},
            {"Archer",   CharacterProperties("Archer", 55, 0.85, 0.7, 0.7, 1, 1.15, 0.85, 60, 1, 33)},
            {"Gargoyle", CharacterProperties("Gargoyle", 65, 0.85, 0.75, 0.73, 1, 1.15, 0.8, 65, 1, 33)},
    },
                        const std::unordered_map<std::string, ThingProperties> &thingParams = {
                                {"Железный нагрудник", ThingProperties("Железный нагрудник", {
                                        {"damage",     0},
                                        {"protection", 1.5},
                                        {"luck",       0},
                                        {"health",     0}}, 1, ThingObject::ARMOR)},
                                {"Железный меч",       ThingProperties("Железный меч", {
                                        {"damage",     1.8},
                                        {"protection", 0},
                                        {"luck",       0},
                                        {"health",     0}}, 1, ThingObject::SWORD)},
                                {"Стальной нагрудник", ThingProperties("Стальной нагрудник", {
                                        {"damage",     0},
                                        {"protection", 2},
                                        {"luck",       0},
                                        {"health",     0}}, 2, ThingObject::ARMOR)},
                                {"Стальной меч",       ThingProperties("Стальной меч", {
                                        {"damage",     2.1},
                                        {"protection", 0},
                                        {"luck",       0},
                                        {"health",     0}}, 2, ThingObject::SWORD)},
                                {"Лечебный эликсир",   ThingProperties("Лечебный эликсир", {
                                        {"damage",     0},
                                        {"protection", 0},
                                        {"luck",       0},
                                        {"health",     40}}, 0, ThingObject::POTION_HEAL)}
                        },
                        int cntEnemyOnField = 3,
                        const std::unordered_map<std::string, int> &cntKilledEnemy = {
                                {"Monster",  1},
                                {"Archer",   1},
                                {"Gargoyle", 1}
                        },
                        int levelAllThings = 1,
                        int cntHealThing = 4,
                        int timeBetweenGenerateEnemy = 13,
                        int timeBetweenGenerateVisualThing = 11,
                        int timeBetweenGenerateHealThing = 8
    ) : RulesPreset(
            charactersParams, thingParams, cntEnemyOnField, cntKilledEnemy, levelAllThings, cntHealThing, timeBetweenGenerateEnemy,
            timeBetweenGenerateVisualThing, timeBetweenGenerateHealThing) {}
};