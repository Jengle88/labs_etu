#pragma once
#include <string>
#include <unordered_map>

enum ThingObject {
    HELMET,
    ARMOR,
    SHIELD,
    SWORD,
    POTION_HEAL,
    RING_LUCKY,
    NONE
};

enum TypeProperties {
    DAMAGE,
    PROTECTION,
    STAMINA,
    LUCKY,
    HEAL
};

class Thing {
    std::string nameThing;
    std::unordered_map<int, double> properties; // тип свойства + дельта
    int thingObject;
    bool isVisualized;
    bool isActive;
    int countBattles; // -1, если не ограничено количеством боёв
public:
    Thing() = delete;
    Thing(std::string nameThing, std::unordered_map<int, double> properties, int thingObject, bool isVisualized, bool isActive, int countBattles = -1);
    std::string getNameThing() const;
    std::unordered_map<int, double> getProperties() const;
    int getThingObject() const;
    bool getStatusIsVisualized() const;
    bool getStatusIsActive() const;
    int getCountBattles() const;
    // сделать функцию action, принимающую героя
};

