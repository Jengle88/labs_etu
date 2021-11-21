#include "MainHero.h"

MainHero::MainHero(std::vector<std::string> model, std::string name, double health, double attackPower, double protection, double luck) : Character(
        model, name, health, attackPower, protection, luck) {
}

std::vector<double> MainHero::requestAttack(Character &enemy) {
    return Character::requestAttack(enemy, CharacterProperties::CHARACTER_CRITICAL_FACTOR);
}

bool MainHero::requestProtect(double attackPower) {
    return Character::requestProtect(attackPower);
}

bool MainHero::requestDodge() const {
    return Character::isCriticalCase();
}

void MainHero::recalcCharacteristics(std::map<std::string, double> thingProperties) {
    this->health += thingProperties.at("health");
    this->attackPower += thingProperties.at("damage");
    this->protection += thingProperties.at("protection");
    this->luck += thingProperties.at("luck");
}

void MainHero::takeThing(Thing thing) {
    auto duplicateThing = std::find_if(inventory.begin(), inventory.end(),
                                       [&thing](Thing& inventoryThing){return inventoryThing.getThingObject() == thing.getThingObject() && !inventoryThing.isActiveThing();});
    if (duplicateThing != inventory.end()){
        recalcCharacteristics(duplicateThing->getInverseValueProperties());
        *duplicateThing = thing;
        recalcCharacteristics(duplicateThing->getProperties());
        return;
    }
    inventory.push_back(thing);
    if (!thing.isActiveThing())
        recalcCharacteristics(thing.getProperties());
}

void MainHero::ejectThing(int pos) {
    auto prevThing = inventory[pos];
    inventory.erase(inventory.begin() + pos);
    if (!prevThing.isActiveThing())
        recalcCharacteristics(prevThing.getInverseValueProperties());
}

bool MainHero::useThing(int pos) {
    if (0 <= pos && pos < inventory.size()) {
        if (inventory[pos].isActiveThing()) {
            auto properties = inventory[pos].getProperties();
            inventory.erase(inventory.begin() + pos);
            recalcCharacteristics(properties);
            return true;
        }
    }
    return false;
}

bool MainHero::hasThing(int thingObject) const {
    return std::find_if(inventory.begin(), inventory.end(),
                        [&thingObject](const Thing& thing) {return thingObject == thing.getThingObject();}) != inventory.end();
}

void MainHero::writeKill(std::string enemyName) {
    countKilledEnemy[enemyName]++;
}

const std::vector<Thing> &MainHero::getInventory() const {
    return inventory;
}

const std::map<std::string, int> &MainHero::getCountKilledEnemy() const {
    return countKilledEnemy;
}

double MainHero::getDodgeFactor() const {
    return CharacterProperties::CHARACTER_DODGE_FACTOR;
}

bool MainHero::checkPositiveHealth() const {
    return health > 0;
}

MainHero * MainHero::clone() const {
    auto res = new MainHero(model, name, health, attackPower, protection, luck);
    res->inventory = inventory;
    res->countKilledEnemy = countKilledEnemy;
    return res;
}

std::string MainHero::getName() const {
    return Character::getName();
}

std::vector<std::string> MainHero::getModel() const {
    return Character::getModel();
}

void MainHero::resetModel(std::vector<std::string> newModel) {
    model = newModel;
}


