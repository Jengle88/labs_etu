#include "Sword.h"

Sword::Sword(const ThingProperties &thingProperties) {
    this->nameThing = thingProperties.nameThing;
    this->levelThing = thingProperties.level;
    this->properties = thingProperties.properties;
}

std::string Sword::getNameThing() {
    return nameThing;
}

int Sword::getLevelThing() const {
    return levelThing;
}

std::map<std::string, double> Sword::getProperties() const {
    return properties;
}

std::map<std::string, double> Sword::getInverseValueProperties() const {
    auto invProperties = properties;
    for (auto &property: invProperties) {
        property.second = -property.second;
    }
    return invProperties;
}

bool Sword::isActiveThing() const {
    return false;
}

bool Sword::isHealThing() const {
    return false;
}

bool Sword::isVisualThing() const {
    return true;
}
