#include "Thing.h"

Thing::Thing(std::string nameThing, std::map<std::string, double> properties, int thingObject)
        : nameThing(nameThing), properties(properties), thingObject(thingObject) {}

bool operator==(const Thing& val1, const Thing& val2) {
    return val1.nameThing == val2.nameThing &&
           val1.properties == val2.properties &&
           val1.thingObject == val2.thingObject;
}

std::string Thing::getNameThing() const {
    return nameThing;
}

const std::map<std::string, double>& Thing::getProperties() const {
    return properties;
}

bool Thing::isActiveThing() const {
    return thingObject == ThingObject::POTION_HEAL;
}

int Thing::getThingObject() const {
    return thingObject;
}

std::map<std::string, double> Thing::getInverseValueProperties() const {
    std::map<std::string, double> resProperties = getProperties();
    for (auto & resProperty : resProperties)
        resProperty.second = -resProperty.second;
    return resProperties;
}
