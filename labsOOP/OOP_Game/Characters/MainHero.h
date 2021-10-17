#pragma once
#include <vector>
#include <cmath>
#include "Character.h"
#include "../Objects/Thing.h"



class MainHero : public Character {
    double stamina;
    double luck; // >= 1
    std::vector<Thing> things;
    std::vector<int> countKilledEnemy;
    bool isCriticalCase(double luck) override;
    bool requestProtect(double attackPower) override;
    bool requestDodge() override;
    void recalcCharacteristics(std::vector<double> thingProperties);
public:
    MainHero(double health, double attackPower, double protection, double stamina, double luck);// : Character(health, attackPower, protection), stamina(stamina), luck(std::max(luck, 1.0)) {}
    MainHero() {}
    std::vector<double> requestAttack(Character &enemy) override;
    void takeThing(Thing thing);
    void ejectThing(int pos);
    void replaceThing(int pos, Thing thing);
    const std::vector<Thing> & getInventory() const;
    const std::vector<int> &getCountKilledEnemy() const;

};
