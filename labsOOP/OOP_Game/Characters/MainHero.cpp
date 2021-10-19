#include "MainHero.h"

MainHero::MainHero(int characterType, double health, double attackPower, double protection, double luck) : Character(
        characterType, health, attackPower, protection, std::max(luck, 1.0)) {
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
    return {startEnemyHealth - enemy.getHealth(), double(wasDodge), double(wasCriticalAttack)};
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
    if (!thing.isActiveThing())
        recalcCharacteristics(thing.getProperties());
}

void MainHero::ejectThing(int pos) {
    auto prevThing = things[pos];
    things.erase(things.begin() + pos);
    if (!prevThing.isActiveThing())
        recalcCharacteristics(prevThing.getInverseValueProperties());
}

const std::vector<int> &MainHero::getCountKilledEnemy() const {
    return countKilledEnemy;
}

const std::vector<Thing> &MainHero::getInventory() const {
    return things;
}

bool MainHero::checkPositiveHealth() const {
    return health > 0;
}

bool MainHero::useThing(int pos) {
    if (0 <= pos && pos < things.size()) {
        if (things[pos].isActiveThing()) {
            auto properties = things[pos].getProperties();
            recalcCharacteristics(properties);
//            health += properties[ThingProperties::HEAL];
//            attackPower += properties[ThingProperties::DAMAGE];
//            protection += properties[ThingProperties::PROTECTION];
//            luck += properties[ThingProperties::LUCK];
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


