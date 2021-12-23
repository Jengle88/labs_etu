#pragma once

#include <string>
#include <map>
#include "../Prototype.h"

enum ThingObject {
    ARMOR,
    SWORD,
    POTION_HEAL,
    THING_OBJECT_SIZE
};

class Thing : public Prototype {
public:
    virtual std::string getNameThing() const = 0;
    virtual int getTypeObject() const = 0;
    virtual std::string getStrType() const = 0;
    virtual int getLevelThing() const = 0;
    virtual std::map<std::string, double> getProperties() const = 0;
    virtual std::map<std::string, double> getInverseValueProperties() const = 0;
    virtual bool isActiveThing() const = 0;
    virtual bool isHealThing() const = 0;
    virtual bool isVisualThing() const = 0;
    virtual Thing* clone() const = 0;
    virtual ~Thing() = default;
};
