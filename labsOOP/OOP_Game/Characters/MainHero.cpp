#include "MainHero.h"

MainHero::MainHero(int characterType, double health, double attackPower, double protection, double luck) : Character(
        characterType, health, attackPower, protection, std::max(luck, 1.0)) {
    countKilledEnemy.resize(CharacterType::CHARACTER_TYPE_SIZE - 1);
}

std::vector<double> MainHero::requestAttack(Character &enemy) {
    return Character::requestAttack(enemy, CHARACTER_CRITICAL_FACTOR);
}

bool MainHero::requestProtect(double attackPower) {
    return Character::requestProtect(attackPower);
}

bool MainHero::requestDodge() const {
    return Character::isCriticalCase();
}

void MainHero::recalcCharacteristics(std::vector<double> thingProperties) {
    this->health += thingProperties[ThingProperties::HEALTH];
    this->attackPower += thingProperties[ThingProperties::DAMAGE];
    this->protection += thingProperties[ThingProperties::PROTECTION];
    this->luck += thingProperties[ThingProperties::LUCK];
}

void MainHero::takeThing(Thing thing) {
    things.push_back(thing);
    if (!thing.isActiveThing())
        recalcCharacteristics(thing.getProperties());
}

void MainHero::ejectThing(int pos) {
    auto prevThing = things[pos];
    things.erase(things.begin() + pos);
    if (!prevThing.isActiveThing())
        recalcCharacteristics(prevThing.getInverseValueProperties());
}

bool MainHero::useThing(int pos) {
    if (0 <= pos && pos < things.size()) {
        if (things[pos].isActiveThing()) {
            auto properties = things[pos].getProperties();
            things.erase(things.begin() + pos);
            recalcCharacteristics(properties);
            return true;
        }
    }
    return false;
}

bool MainHero::hasThing(int thingObject) const {
    return std::find_if(things.begin(),  things.end(),
                        [&thingObject](const Thing& thing) {return thingObject == thing.getThingObject();}) != things.end();
}

void MainHero::writeKill(int enemyType) {
    countKilledEnemy[enemyType]++;
}

const std::vector<Thing> &MainHero::getInventory() const {
    return things;
}

const std::vector<int> &MainHero::getCountKilledEnemy() const {
    return countKilledEnemy;
}

double MainHero::getDodgeFactor() const {
    return CHARACTER_DODGE_FACTOR;
}

bool MainHero::checkPositiveHealth() const {
    return health > 0;
}


