#include "Armor.h"

Armor::Armor(const ThingProperties &thingProperties) {
    this->nameThing = thingProperties.nameThing;
    this->levelThing = thingProperties.level;
    this->properties = thingProperties.properties;
}

std::string Armor::getNameThing() {
    return nameThing;
}

int Armor::getLevelThing() const {
    return levelThing;
}

std::map<std::string, double> Armor::getProperties() const {
    return properties;
}

std::map<std::string, double> Armor::getInverseValueProperties() const {
    auto invProperties = properties;
    for (auto &property: invProperties) {
        property.second = -property.second;
    }
    return invProperties;
}

bool Armor::isActiveThing() const {
    return false;
}

bool Armor::isHealThing() const {
    return false;
}

bool Armor::isVisualThing() const {
    return true;
}
