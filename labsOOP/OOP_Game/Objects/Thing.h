#pragma once
#include <string>
#include <vector>

enum ThingObject {
    HELMET,
    ARMOR,
    SHIELD,
    SWORD,
    POTION_HEAL,
    RING_LUCKY,
    THING_OBJECT_SIZE
};

enum ThingProperties {
    DAMAGE,
    PROTECTION,
    STAMINA,
    LUCK,
    HEAL,
    THING_PROPERTIES_SIZE
};

class Thing {
    std::string nameThing;
    std::vector<double> properties; // дельта свойства, максимум 5 элементов
    int thingObject;
    bool isVisualized;
    int countBattles; // -1, если не ограничено количеством боёв
public:
    Thing() = default;
    Thing(std::string nameThing, std::vector<double> properties, int thingObject, bool isVisualized, int countBattles = -1);
    std::string getNameThing() const;
    const std::vector<double>& getProperties() const;
    int getThingObject() const;
    bool getStatusIsVisualized() const;
    int getCountBattles() const;
    std::vector<double> getInverseValueProperties() const;
    // сделать функцию action, принимающую героя
};

