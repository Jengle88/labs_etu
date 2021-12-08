#pragma once

#include "CharacterProperties.h"
#include "ThingProperties.h"
#include "RulesChecker.h"

class DifficultPreset : public RulesChecker {
    std::unordered_map<std::string, CharacterProperties> charactersParams;
    std::unordered_map<std::string, ThingProperties> thingsParams;
    std::unordered_map<std::string, int> cntKilledEnemy;
    int cntThingsRightLevel;
    int cntEnemyOnField;
    int levelAllThings;
    int cntHealThing;
    int timeBetweenGenerateEnemy;
    int timeBetweenGenerateVisualThing;
    int timeBetweenGenerateHealThing;
public:
    bool checkHero(MainHero& hero) const override;
    bool checkField(Field &field) const override;
    void recalcCntThingsRightLevel();  // считает количество вещей одного нужного уровня для сравнения

    const std::unordered_map<std::string, CharacterProperties> &getCharactersParams() const;
    const std::unordered_map<std::string, ThingProperties> &getThingsParams() const;
    const std::unordered_map<std::string, int> &getCntKilledEnemy() const;
    int getCntEnemyOnField() const;
    int getLevelAllThings() const;
    int getCntThingsRightLevel() const;
    int getCntHealThing() const;
    int getTimeBetweenGenerateEnemy() const;
    int getTimeBetweenGenerateVisualThing() const;
    int getTimeBetweenGenerateHealThing() const;

    void setCharactersParams(const std::unordered_map<std::string, CharacterProperties> &charactersParams);
    void setThingsParams(const std::unordered_map<std::string, ThingProperties> &thingsParams);
    void setCntKilledEnemy(const std::unordered_map<std::string, int> &cntKilledEnemy);
    void setCntEnemyOnField(int cntEnemyOnField);
    void setLevelAllThings(int levelAllThings);
    void setCntHealThing(int cntHealThing);
    void setTimeBetweenGenerateEnemy(int timeBetweenGenerateEnemy);
    void setTimeBetweenGenerateVisualThing(int timeBetweenGenerateVisualThing);
    void setTimeBetweenGenerateHealThing(int timeBetweenGenerateHealThing);
};
