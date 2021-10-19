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
    bool isVisualized;
    friend bool operator==(const Thing& val1, const Thing& val2);

public:
    Thing() = default;
    Thing(std::string nameThing, std::vector<double> properties, int thingObject, bool isVisualized);
    std::string getNameThing() const;
    const std::vector<double>& getProperties() const;
    int getThingObject() const;
    bool getStatusIsVisualized() const;
    bool isActiveThing() const;
    std::vector<double> getInverseValueProperties() const;
};

