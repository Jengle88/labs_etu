#pragma once
#include <vector>
#include <cmath>
#include "Character.h"
#include "../Objects/Thing.h"
#include <algorithm>

#define MAIN_HERO_RANGE_VISIBILITY 1
#define MAIN_HERO_DAMAGE 1
#define MAIN_HERO_PROTECTION 1
#define MAIN_HERO_LUCK 0.65

class MainHero : public Character {
    std::vector<Thing> things;
    std::vector<int> countKilledEnemy;
    bool requestProtect(double attackPower);
    bool requestDodge() const override;
    void recalcCharacteristics(std::vector<double> thingProperties);
public:
    MainHero(int characterType, double health, double attackPower, double protection, double luck);
    MainHero() = default;
    // урон, уклонение и крит
    std::vector<double> requestAttack(Character &enemy);
    void takeThing(Thing thing);
    void ejectThing(int pos);
    bool useThing(int pos);
    bool hasThing(int thingObject) const;
    void writeKill(int enemyType);
    const std::vector<Thing> & getInventory() const;
    const std::vector<int> &getCountKilledEnemy() const;
    bool checkPositiveHealth() const;
};
