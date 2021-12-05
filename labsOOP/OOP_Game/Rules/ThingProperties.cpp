#include "ThingProperties.h"


Thing *ThingProperties::toThing() const {
    switch (typeObject) {
        case ThingObject::SWORD:
            return new Sword(nameThing, properties, level);
        case ThingObject::ARMOR:
            return new Armor(nameThing, properties, level);
        case ThingObject::POTION_HEAL:
            return new HealPotion(nameThing, properties, level);
    }
    throw std::logic_error("Не найден нужный конструктор вещи");
}

ThingProperties::ThingProperties(const std::string &nameThing, const std::map<std::string, double> &properties,
                                 int level, int typeObject)
        : properties(properties), nameThing(nameThing), level(level), typeObject(typeObject) {}

const std::string &ThingProperties::getNameThing() const {
    return nameThing;
}

const std::map<std::string, double> &ThingProperties::getProperties() const {
    return properties;
}

int ThingProperties::getLevel() const {
    return level;
}

int ThingProperties::getTypeObject() const {
    return typeObject;
}
