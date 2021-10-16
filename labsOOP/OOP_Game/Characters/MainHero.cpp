#include "MainHero.h"

void MainHero::requestAttack(Character &enemy) {
    if (isCriticalCase(this->luck))
        enemy.requestProtect(this->attackPower * CRITICAL_FACTOR);
    else
        enemy.requestProtect(this->attackPower);
}

double MainHero::requestDodge() {
    return isCriticalCase(this->luck) ? DODGE_FACTOR : 1;
}

bool MainHero::isCriticalCase(double luck) {
    srand(time(0)); // сделать глобально в начале игры????
    double checkCriticalAttack = std::sin((rand() % 100 + 1 / double(rand() % 100)) * luck); // есть ли способ проще?
    return ((checkCriticalAttack - int(checkCriticalAttack)) <= CRITICAL_EPSILON);
}

void MainHero::requestProtect(double attackPower) {
//    if (this->requestDodge())
        this->health -= attackPower * calcReflectionArmor() * requestDodge();
//    else
//        this->health -= attackPower * calcReflectionArmor();
}

void MainHero::recalcCharacteristics(std::vector<double> thingProperties) {
    this->health += thingProperties[ThingProperties::HEAL];
    this->attackPower += thingProperties[ThingProperties::DAMAGE];
    this->protection += thingProperties[ThingProperties::PROTECTION];
    this->stamina += thingProperties[ThingProperties::STAMINA];
    this->luck += thingProperties[ThingProperties::LUCK];
}

void MainHero::takeThing(Thing thing) {
    things.push_back(thing);
    recalcCharacteristics(thing.getProperties());
}

void MainHero::ejectThing(int pos) {
    auto prevThing = things.erase(things.begin() + pos);
    recalcCharacteristics(prevThing->getInverseValueProperties());
}

void MainHero::replaceThing(int pos, Thing thing) {
    recalcCharacteristics(things[pos].getInverseValueProperties());
    recalcCharacteristics(thing.getProperties());
    things[pos] = thing;
}
