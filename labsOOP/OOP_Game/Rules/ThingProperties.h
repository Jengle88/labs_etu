#pragma once

#include <memory>
#include "../Entity/Objects/Sword.h"
#include "../Entity/Objects/HealPotion.h"
#include "../Entity/Objects/Armor.h"


class ThingProperties {
    std::string nameThing;
    std::map<std::string, double> properties; // берём только нужные свойства
    int level = 0;
    int typeObject;
public:
    ThingProperties(const std::string &nameThing, const std::map<std::string, double> &properties, int level,int typeObject);
    Thing* toThing() const;
    const std::string &getNameThing() const;
    const std::map<std::string, double> &getProperties() const;
    int getLevel() const;
    int getTypeObject() const;
};

