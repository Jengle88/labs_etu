#include "Thing.h"

Thing::Thing(std::string nameThing, std::unordered_map<int, double> properties, int thingObject, bool isVisualized,
             bool isActive, int countBattles)
        : nameThing(nameThing), properties(properties), thingObject(thingObject), isVisualized(isVisualized),
          isActive(isActive), countBattles(countBattles) {}

std::string Thing::getNameThing() const {
    return nameThing;
}

std::unordered_map<int, double> Thing::getProperties() const {
    return properties;
}

int Thing::getThingObject() const {
    return thingObject;
}

bool Thing::getStatusIsVisualized() const {
    return isVisualized;
}

bool Thing::getStatusIsActive() const {
    return isActive;
}

int Thing::getCountBattles() const {
    return countBattles;
}

