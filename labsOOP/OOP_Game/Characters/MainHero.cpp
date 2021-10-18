#include "MainHero.h"

MainHero::MainHero(int characterType, double health, double attackPower, double protection, double luck) : Character(characterType, health, attackPower, protection, std::max(luck, 1.0)){
    countKilledEnemy.resize(CharacterType::CHARACTER_TYPE_SIZE - 1);
}


std::vector<double> MainHero::requestAttack(Character &enemy) {
    std::vector<double> actionTable(3);
    bool wasCriticalAttack = isCriticalCase(luck);
    double startEnemyHealth = enemy.getHealth();
    bool wasDodge;
    if (wasCriticalAttack)
        wasDodge = enemy.requestProtect(this->attackPower * CHARACTER_CRITICAL_FACTOR);
    else
        wasDodge = enemy.requestProtect(this->attackPower);
    return {double(wasCriticalAttack), double(wasDodge), startEnemyHealth - enemy.getHealth()};
}

bool MainHero::requestDodge() const {
    return isCriticalCase(luck);
}

bool MainHero::requestProtect(double attackPower) {
    bool wasDodge = this->requestDodge();
    if (wasDodge)
        this->health -= attackPower * calcReflectionArmor() * CHARACTER_DODGE_FACTOR;
    else
        this->health -= attackPower * calcReflectionArmor();
    return wasDodge;
}

void MainHero::recalcCharacteristics(std::vector<double> thingProperties) {
    this->health += thingProperties[ThingProperties::HEAL];
    this->attackPower += thingProperties[ThingProperties::DAMAGE];
    this->protection += thingProperties[ThingProperties::PROTECTION];
    this->luck += thingProperties[ThingProperties::LUCK];
}

void MainHero::takeThing(Thing thing) {
    things.push_back(thing);
    recalcCharacteristics(thing.getProperties());
}

void MainHero::ejectThing(int pos) {
    auto prevThing = things[pos];
    things.erase(things.begin() + pos);
    recalcCharacteristics(prevThing.getInverseValueProperties());
}

void MainHero::replaceThing(int pos, Thing thing) {
    recalcCharacteristics(things[pos].getInverseValueProperties());
    recalcCharacteristics(thing.getProperties());
    things[pos] = thing;
}

const std::vector<int> &MainHero::getCountKilledEnemy() const {
    return countKilledEnemy;
}

const std::vector<Thing> & MainHero::getInventory() const {
    return things;
}


