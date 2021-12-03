#pragma once

#include "ThingInterface.h"
#include "../Rules/ThingProperties.h"

class Sword : public ThingInterface {
    std::map<std::string, double> properties; // дельта свойств, максимум 4 элемента
    std::string nameThing;
    int levelThing;
public:
    Sword(const ThingProperties& thingProperties);
    std::string getNameThing() override;
    int getLevelThing() const override;
    std::map<std::string, double> getProperties() const override;
    std::map<std::string, double> getInverseValueProperties() const override;
    bool isActiveThing() const override;
    bool isHealThing() const override;
    bool isVisualThing() const override;
};
