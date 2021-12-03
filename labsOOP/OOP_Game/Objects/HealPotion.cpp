#include "HealPotion.h"

HealPotion::HealPotion(const ThingProperties &thingProperties) {
    this->nameThing = thingProperties.nameThing;
    this->levelThing = thingProperties.level;
    this->properties = thingProperties.properties;
}

std::string HealPotion::getNameThing() {
    return nameThing;
}

int HealPotion::getLevelThing() const {
    return levelThing;
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
