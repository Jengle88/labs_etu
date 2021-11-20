#pragma once
#include <string>
#include <vector>
#include <map>
#include <ostream>

enum ThingObject {
    ARMOR,
    SWORD,
    POTION_HEAL,
    THING_OBJECT_SIZE
};

class Thing {
    std::string nameThing;
    std::map<std::string, double> properties; // дельта свойств, максимум 4 элемента
    int thingObject;
    int levelThing;
    friend bool operator==(const Thing& val1, const Thing& val2);
public:

    Thing(std::string nameThing, std::map<std::string, double> properties, int thingObject, int levelThing);
    Thing() = default;
    std::string getNameThing() const;
    const std::map<std::string, double>& getProperties() const;
    bool isActiveThing() const;
    bool isHealThing() const;
    bool isVisualThing() const;
    int getThingObject() const;
    std::map<std::string, double> getInverseValueProperties() const;
    friend std::ostream &operator<<(std::ostream &os, const Thing &thing);
};

