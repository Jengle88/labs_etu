#include "DataManager.h"

DataManager::DataManager() {
    levelToThings[1] = {
            Thing("Железный шлем", {0, 0.5, 0, 0, 0}, ThingObject::HELMET, true, -1),
            Thing("Железный нагрудник", {0, 1, 0, 0, 0}, ThingObject::ARMOR, true, -1),
            Thing("Деревянный щит", {0, 0.3, 0, 0, 0}, ThingObject::SHIELD, true, -1),
            Thing("Железный меч", {1.2, 0, 0, 0, 0}, ThingObject::SWORD, true, -1),
    };
    levelToThings[2] = {
            Thing("Стальной шлем", {0, 0.8, 0, 0, 0}, ThingObject::HELMET, true, -1),
            Thing("Стальной нагрудник", {0, 1.3, 0, 0, 0}, ThingObject::ARMOR, true, -1),
            Thing("Стальной щит", {0, 0.7, 0, 0, 0}, ThingObject::SHIELD, true, -1),
            Thing("Стальной меч", {1.6, 0, 0, 0, 0}, ThingObject::SWORD, true, -1),

    };
}

Thing DataManager::getThing(int level, int typeThing) {
    return levelToThings[level][typeThing];
}
