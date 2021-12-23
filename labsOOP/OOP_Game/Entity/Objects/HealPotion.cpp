#include "HealPotion.h"


std::string HealPotion::getNameThing() const {
    return nameThing;
}

int HealPotion::getLevelThing() const {
    return levelThing;
}

int HealPotion::getTypeObject() const {
    return ThingObject::POTION_HEAL;
}

std::map<std::string, double> HealPotion::getProperties() const {
    return properties;
}

std::map<std::string, double> HealPotion::getInverseValueProperties() const {
    auto invProperties = properties;
    for (auto &property: invProperties) {
        property.second = -property.second;
    }
    return invProperties;
}

bool HealPotion::isActiveThing() const {
    return true;
}

bool HealPotion::isHealThing() const {
    return true;
}

bool HealPotion::isVisualThing() const {
    return false;
}

HealPotion *HealPotion::clone() const {
    return new HealPotion(
            getNameThing(), getProperties(), getLevelThing()
            );
}

HealPotion::HealPotion(const std::string &nameThing, const std::map<std::string, double> &properties, int levelThing) {
    this->nameThing = nameThing;
    this->properties = properties;
    this->levelThing = levelThing;
}

std::string HealPotion::getStrType() const {
    return "healPotion";
}
