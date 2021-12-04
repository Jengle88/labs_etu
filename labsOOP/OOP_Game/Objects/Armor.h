#pragma once
#include "ThingInterface.h"
#include "../Rules/ThingProperties.h"

class Armor : public ThingInterface {
    std::map<std::string, double> properties; // дельта свойств, максимум 4 элемента
    std::string nameThing;
    int levelThing;
public:
    Armor(const std::string& nameThing, const std::map<std::string, double>& properties, int levelThing);
    ~Armor() override = default;
    std::string getNameThing() const override;
    int getLevelThing() const override;
    int getTypeObject() const override;
    std::map<std::string, double> getProperties() const override;
    std::map<std::string, double> getInverseValueProperties() const override;
    bool isActiveThing() const override;
    bool isHealThing() const override;
    bool isVisualThing() const override;
    Armor *clone() const override;
};
