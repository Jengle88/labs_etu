#pragma once
#include <vector>
#include <cmath>
#include <map>
#include "Character.h"
#include "../Objects/Thing.h"
#include <algorithm>


class MainHero : public Character {
    std::vector<Thing> inventory;
    std::map<std::string, int> countKilledEnemy;
    bool requestProtect(double attackPower);
    bool requestDodge() const override;
    void recalcCharacteristics(std::map<std::string, double> thingProperties);
public:
    struct MainHeroProperties{
        constexpr static char MAIN_HERO_NAME[] = "Hero";
        constexpr static double MAIN_HERO_RANGE_VISIBILITY = 1;
        constexpr static double MAIN_HERO_MAX_HEALTH = CharacterProperties::CHARACTER_MAX_HEALTH;
        constexpr static double MAIN_HERO_DAMAGE = 1;
        constexpr static double MAIN_HERO_PROTECTION = 1;
        constexpr static double MAIN_HERO_LUCK = 0.65;
    };
    MainHero(std::vector<std::string> model,
                std::string name = MainHeroProperties::MAIN_HERO_NAME,
                double health = CharacterProperties::CHARACTER_MAX_HEALTH,
                double attackPower = MainHeroProperties::MAIN_HERO_DAMAGE,
                double protection = MainHeroProperties::MAIN_HERO_PROTECTION,
                double luck = MainHeroProperties::MAIN_HERO_LUCK);
    MainHero() = default;
    // урон, уклонение и крит
    std::vector<double> requestAttack(Character &enemy);
    void takeThing(Thing thing);
    void ejectThing(int pos);
    bool useThing(int pos);
    bool hasThing(int thingObject) const;
    void writeKill(std::string enemyName);
    const std::vector<Thing> & getInventory() const;
    const std::map<std::string, int> &getCountKilledEnemy() const;
    std::string getName() const override;
    std::vector<std::string> getModel() const override;
    MainHero * clone() const override;
    double getDodgeFactor() const override;
    bool checkPositiveHealth() const;
    void resetModel(std::vector<std::string> newModel);
};
