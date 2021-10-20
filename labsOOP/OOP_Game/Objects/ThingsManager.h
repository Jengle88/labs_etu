#pragma once

#include <utility>
#include <map>
#include "Thing.h"
#include "../Tools/CellPoint.h"
#include "../Characters/MainHero.h"
#include "../UI/Models/Field.h"
#include "../Data/DataManager.h"

#define TIME_BETWEEN_GENERATE_THING 15
#define MAX_COUNT_HEALTH_THINGS 3

class ThingsManager {
    Field *field;
    DataManager dataManager;
    std::map<CellPoint, Thing> visualThingsPlaces;
    std::map<CellPoint, Thing> healthThingsPlaces;
    int levelThings = 1;
    void generateVisualThing();
    void checkThingsLevel(const std::vector<int> &achievements);
    void generateHealthThing();
public:

    ThingsManager(Field *field, std::map<CellPoint, Thing> visualThingsPlaces = std::map<CellPoint, Thing>(),
                  std::map<CellPoint, Thing> healthThingsPlaces = std::map<CellPoint, Thing>());
    ThingsManager() = default;
    void tryGenerateThing(const MainHero &hero);
    std::pair<bool, Thing> checkCellHasSmth(CellPoint point);
    void deleteThingFromField(CellPoint point);
};