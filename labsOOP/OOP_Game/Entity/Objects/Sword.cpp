#include "Sword.h"


std::string Sword::getNameThing() const {
    return nameThing;
}

int Sword::getLevelThing() const {
    return levelThing;
}

int Sword::getTypeObject() const {
    return ThingObject::SWORD;
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

Sword *Sword::clone() const {
    return new Sword(
            getNameThing(), getProperties(), getLevelThing()
            );
}

Sword::Sword(const std::string &nameThing, const std::map<std::string, double> &properties, int levelThing) {
    this->nameThing = nameThing;
    this->properties = properties;
    this->levelThing = levelThing;
}

std::string Sword::getStrType() const {
    return "sword";
}
