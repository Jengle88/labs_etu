#pragma once

#include <utility>
#include <map>
#include "Thing.h"
#include "../Tools/CellPoint.h"
#include "../Characters/MainHero.h"
#include "../UI/Models/Field.h"
#include "../Data/DataManager.h"

#define STEP_MULTIPLICITY 15

class ThingsManager {
    Field *field;
    DataManager dataManager;
    std::map<CellPoint, Thing> visualThingsPlaces;
    std::map<CellPoint, Thing> healthThingsPlaces;
    int levelThings = 1;
    long int counterSteps = 0;
    void generateVisualThing();
    void checkThingsLevel(const std::vector<int> &achievements);
    void generateHealthThing();

public:
    ThingsManager(Field *field, std::map<CellPoint, Thing> visualThingsPlaces = std::map<CellPoint, Thing>(),
                  std::map<CellPoint, Thing> healthThingsPlaces = std::map<CellPoint, Thing>());

    void generateThing(const MainHero &hero);
    void incCountSteps();

};