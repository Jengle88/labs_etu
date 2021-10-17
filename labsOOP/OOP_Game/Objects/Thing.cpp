#include "Thing.h"

Thing::Thing(std::string nameThing, std::vector<double> properties, int thingObject, bool isVisualized,
             int countBattles)
        : nameThing(nameThing), properties(properties), thingObject(thingObject), isVisualized(isVisualized),
        countBattles(countBattles) {}

std::string Thing::getNameThing() const {
    return nameThing;
}

const std::vector<double>& Thing::getProperties() const {
    return properties;
}

int Thing::getThingObject() const {
    return thingObject;
}

bool Thing::getStatusIsVisualized() const {
    return isVisualized;
}


int Thing::getCountBattles() const {
    return countBattles;
}

std::vector<double> Thing::getInverseValueProperties() const {
    std::vector<double> resProperties = getProperties();
    for (double & resProperty : resProperties)
        resProperty = -resProperty;
    return resProperties;
}

