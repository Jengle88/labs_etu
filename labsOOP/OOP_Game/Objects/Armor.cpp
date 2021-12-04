#include "Armor.h"

std::string Armor::getNameThing() const {
    return nameThing;
}

int Armor::getLevelThing() const {
    return levelThing;
}

int Armor::getTypeObject() const {
    return ThingObject::ARMOR;
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

Armor *Armor::clone() const {
    return new Armor(
            getNameThing(), getProperties(), getLevelThing()
    );
}

Armor::Armor(const std::string &nameThing, const std::map<std::string, double> &properties, int levelThing) {
    this->nameThing = nameThing;
    this->properties = properties;
    this->levelThing = levelThing;
}
