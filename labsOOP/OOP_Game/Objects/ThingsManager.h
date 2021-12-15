#pragma once
#include <utility>
#include <map>
#include "../Tools/CellPoint.h"
#include "../Characters/MainHero.h"
#include "../UI/Models/Field.h"
#include "../Data/DataManager.h"

class ThingsManager {
    Field *field;
    std::map<CellPoint, Thing*> visualThingsPlaces;
    std::map<CellPoint, Thing*> nonVisualThingsPlaces;
    int cntHealThing;
    int timeBetweenGenerateVisualThing;
    int timeBetweenGenerateHealThing;
    int levelThings = 1;
    void generateVisualThing(DataManager *dataManager);
    void checkThingsLevel(std::map<std::string, int> &achievements);
    void generateHealthThing(DataManager *dataManager);
public:

    explicit ThingsManager(Field *field, std::map<CellPoint, Thing*> visualThingsPlaces = std::map<CellPoint, Thing*>(),
                  std::map<CellPoint, Thing*> healthThingsPlaces = std::map<CellPoint, Thing*>());
    ThingsManager() = default;
    void tryGenerateThing(MainHero &hero, DataManager *dataManager);
    std::pair<bool, Thing*> checkCellHasSmth(CellPoint point);
    void deleteThingFromField(CellPoint point);
    void setRules(int cntHealThing, int timeBetweenGenerateVisualThing, int timeBetweenGenerateHealThing);
};