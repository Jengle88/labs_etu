#include "MainHero.h"

MainHero::MainHero(double health, double attackPower, double protection, double luck) : Character(health, attackPower, protection), luck(std::max(luck, 1.0)) {
    countKilledEnemy.resize(EnemyType::ENEMY_TYPE_SIZE);
}


std::vector<double> MainHero::requestAttack(Character &enemy) {
    std::vector<double> actionTable(3);
    bool wasCriticalAttack = isCriticalCase(this->luck);
    double startEnemyHealth = enemy.getHealth();
    bool wasDodge;
    if (wasCriticalAttack)
        wasDodge = enemy.requestProtect(this->attackPower * CRITICAL_FACTOR);
    else
        wasDodge = enemy.requestProtect(this->attackPower);
    return {double(wasCriticalAttack), double(wasDodge), startEnemyHealth - enemy.getHealth()};
}

bool MainHero::requestDodge() {
    return isCriticalCase(this->luck);
}

bool MainHero::isCriticalCase(double luck) {
    srand(time(0)); // сделать глобально в начале игры????
    double checkCriticalAttack = std::sin(
            (rand() % 100 + 1 / double(rand() % 100)) * luck); // есть ли способ проще? //luck >= 1, поэтому проблем нет
    return ((checkCriticalAttack - int(checkCriticalAttack)) <= ROOT_EPSILON_FOR_CRITICAL);
}

bool MainHero::requestProtect(double attackPower) {
    bool wasDodge = this->requestDodge();
    if (wasDodge)
        this->health -= attackPower * calcReflectionArmor() * DODGE_FACTOR;
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


