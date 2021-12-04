#pragma once
#include <utility>
#include <map>
#include "../Tools/CellPoint.h"
#include "../Characters/MainHero.h"
#include "../UI/Models/Field.h"
#include "../Data/DataManager.h"

class ThingsManager {
    Field *field;
    std::map<CellPoint, ThingInterface*> visualThingsPlaces;
    std::map<CellPoint, ThingInterface*> nonVisualThingsPlaces;
    int cntHealThing;
    int timeBetweenGenerateVisualThing;
    int timeBetweenGenerateHealThing;
    int levelThings = 1;
    void generateVisualThing(DataManager *dataManager);
    void checkThingsLevel(std::map<std::string, int> &achievements);
    void generateHealthThing(DataManager *dataManager);
public:

    ThingsManager(Field *field, std::map<CellPoint, ThingInterface*> visualThingsPlaces = std::map<CellPoint, ThingInterface*>(),
                  std::map<CellPoint, ThingInterface*> healthThingsPlaces = std::map<CellPoint, ThingInterface*>());
    ThingsManager() = default;
    void tryGenerateThing(MainHero &hero, DataManager *dataManager);
    std::pair<bool, ThingInterface*> checkCellHasSmth(CellPoint point);
    void deleteThingFromField(CellPoint point);
    void setRules(int cntHealThing, int timeBetweenGenerateVisualThing, int timeBetweenGenerateHealThing);
};