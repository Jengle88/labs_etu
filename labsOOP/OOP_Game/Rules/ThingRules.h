#pragma once
#include "../Objects/Thing.h"

struct ThingRules {
    std::string nameThing;
    std::map<std::string, double> properties; // берём только нужные свойства
    int level = 0;
    int typeObject;
public:
    ThingRules(const std::string &nameThing, const std::map<std::string, double> &properties, int level,int typeObject)
            : properties(properties), nameThing(nameThing), level(level), typeObject(typeObject) {}
    Thing toThing() const {
        return {nameThing, properties,typeObject, level};
    }
};
