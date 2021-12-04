#pragma once
#include "../Objects/Sword.h"
#include "../Objects/HealPotion.h"
#include "../Objects/Armor.h"


struct ThingProperties {
    std::string nameThing;
    std::map<std::string, double> properties; // берём только нужные свойства
    int level = 0;
    int typeObject;
public:
    ThingProperties(const std::string &nameThing, const std::map<std::string, double> &properties, int level,int typeObject);
    Thing* toThing() const;
};

