//#include "../CharacterProperties.h"
//#include "../RulesPreset.h"
//#include "../ThingProperties.h"
//
//
//class MiddlePreset : public RulesPreset {
//public:
//    MiddlePreset(const std::unordered_map<std::string, CharacterProperties> &charactersParams = {
//            {"MainHero", CharacterProperties("MainHero", 100, 1.1, 1, 1.1, 1, 1.2, 0.69, -1, -1)},
//            {"Monster",  CharacterProperties("Monster", 65, 0.9, 0.8, 0.75, 1, 1.2, 0.85, 70, 1)},
//            {"Archer",   CharacterProperties("Archer", 62, 0.9, 0.77, 0.8, 1, 1.25, 0.8, 70, 1)},
//            {"Gargoyle", CharacterProperties("Gargoyle", 75, 1, 0.95, 0.73, 1, 1.3, 0.7, 75, 1)},
//    },
//                 const std::unordered_map<std::string, ThingProperties> &thingParams = {
//                         {"Железный нагрудник", ThingProperties("Железный нагрудник", {
//                                 {"damage",     0},
//                                 {"protection", 1.3},
//                                 {"luck",       0},
//                                 {"health",     0}}, 1, ThingObject::ARMOR)},
//                         {"Железный меч",       ThingProperties("Железный меч", {
//                                 {"damage",     1.5},
//                                 {"protection", 0},
//                                 {"luck",       0},
//                                 {"health",     0}}, 1, ThingObject::SWORD)},
//                         {"Стальной нагрудник", ThingProperties("Стальной нагрудник", {
//                                 {"damage",     0},
//                                 {"protection", 1.7},
//                                 {"luck",       0},
//                                 {"health",     0}}, 2, ThingObject::ARMOR)},
//                         {"Стальной меч",       ThingProperties("Стальной меч", {
//                                 {"damage",     1.9},
//                                 {"protection", 0},
//                                 {"luck",       0},
//                                 {"health",     0}}, 2, ThingObject::SWORD)},
//                         {"Лечебный эликсир",   ThingProperties("Лечебный эликсир", {
//                                 {"damage",     0},
//                                 {"protection", 0},
//                                 {"luck",       0},
//                                 {"health",     30}}, 0, ThingObject::POTION_HEAL)}
//                 },
//                 int cntEnemyOnField = 5,
//                 const std::unordered_map<std::string, int> &cntKilledEnemy = {
//                         {"Monster",  3},
//                         {"Archer",   2},
//                         {"Gargoyle", 1}
//                 },
//                 int levelAllThings = 2,
//                 int cntHealThing = 3,
//                 int timeBetweenGenerateEnemy = 11,
//                 int timeBetweenGenerateVisualThing = 13,
//                 int timeBetweenGenerateHealThing = 10
//    ) : RulesPreset(
//            charactersParams, thingParams, cntEnemyOnField, cntKilledEnemy, levelAllThings, cntHealThing,
//            timeBetweenGenerateEnemy,
//            timeBetweenGenerateVisualThing, timeBetweenGenerateHealThing) {}
//};
