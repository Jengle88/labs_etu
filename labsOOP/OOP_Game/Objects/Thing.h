#pragma once
#include <string>
#include <vector>

enum ThingObject {
    ARMOR,
    SWORD,
    POTION_HEAL,
    THING_OBJECT_SIZE
};

enum ThingProperties {
    DAMAGE,
    PROTECTION,
    LUCK,
    HEALTH,
    THING_PROPERTIES_SIZE
};

class Thing {
    std::string nameThing;
    std::vector<double> properties; // дельта свойств, максимум 3 элемента
    int thingObject;
    friend bool operator==(const Thing& val1, const Thing& val2);

public:
    Thing(std::string nameThing, std::vector<double> properties, int thingObject, bool isVisualized);
    Thing() = default;
    std::string getNameThing() const;
    const std::vector<double>& getProperties() const;
    bool isActiveThing() const;
    int getThingObject() const;
    std::vector<double> getInverseValueProperties() const;
};

