#pragma once
#include <utility>
#include "Thing.h"

class ThingsManager {
    std::unordered_map<std::pair<int,int>, Thing> thingsPlaces;

    void generateThing(int type);

};