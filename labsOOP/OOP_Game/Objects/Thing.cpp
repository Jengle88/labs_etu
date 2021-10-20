#include "Thing.h"

Thing::Thing(std::string nameThing, std::vector<double> properties, int thingObject, bool isVisualized)
        : nameThing(nameThing), properties(properties), thingObject(thingObject) {}

bool operator==(const Thing& val1, const Thing& val2) {
    return val1.nameThing == val2.nameThing &&
           val1.properties == val2.properties &&
           val1.thingObject == val2.thingObject;
}

std::string Thing::getNameThing() const {
    return nameThing;
}

const std::vector<double>& Thing::getProperties() const {
    return properties;
}

bool Thing::isActiveThing() const {
    return thingObject == ThingObject::POTION_HEAL;
}

int Thing::getThingObject() const {
    return thingObject;
}

std::vector<double> Thing::getInverseValueProperties() const {
    std::vector<double> resProperties = getProperties();
    for (double & resProperty : resProperties)
        resProperty = -resProperty;
    return resProperties;
}

