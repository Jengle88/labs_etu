#pragma once

#include <string>
#include <map>

class ThingInterface {
public:
    virtual std::string getNameThing() = 0;
    virtual int getLevelThing() const = 0;
    virtual std::map<std::string, double> getProperties() const = 0;
    virtual std::map<std::string, double> getInverseValueProperties() const = 0;
    virtual bool isActiveThing() const = 0;
    virtual bool isHealThing() const = 0;
    virtual bool isVisualThing() const = 0;
};
