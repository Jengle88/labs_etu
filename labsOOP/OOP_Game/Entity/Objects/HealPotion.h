#pragma once
#include "Thing.h"
#include "../../Rules/ThingProperties.h"

class HealPotion : public Thing {
    std::map<std::string, double> properties; // дельта свойств, максимум 4 элемента
    std::string nameThing;
    int levelThing;
public:
    HealPotion(const std::string& nameThing, const std::map<std::string, double>& properties, int levelThing);
    ~HealPotion() override = default;
    std::string getNameThing() const override;
    std::string getStrType() const override;
    int getLevelThing() const override;
    int getTypeObject() const override;
    std::map<std::string, double> getProperties() const override;
    std::map<std::string, double> getInverseValueProperties() const override;
    bool isActiveThing() const override;
    bool isHealThing() const override;
    bool isVisualThing() const override;
    HealPotion *clone() const override;
};
