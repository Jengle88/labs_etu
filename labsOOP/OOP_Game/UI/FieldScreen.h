#pragma once
#include "Models/Field.h"
#include "../Objects/ThingsManager.h"
#include "../Tools/Printer.h"
#include "FightScreen.h"

//enum MoveSide{
//    UP = 'w',
//    LEFT = 'a',
//    RIGHT = 'd',
//    DOWN = 's',
//    TAKE = 'e',
//    FIGHT = 'f',
//    FINISH_OUT = 'q',
//    EXIT = '`'
//};

class FieldScreen {
    Field *field;
    ThingsManager thingsManager;
    DataManager *dataManager;
    std::tuple<int, int, int> showStartingParamsAndGenerateField(DataManager *dataManager);
    bool registerMovement(char &action, std::string& gameAction);
    void requestMoveHero(CellPoint from, CellPoint to, std::string& gameAction);
    void requestTakeObject(CellPoint point);
    int requestStartFight(CellPoint point);
    bool requestMoveOut() const;

public:
    FieldScreen();
    ~FieldScreen();
    std::tuple<int, int, int> showStartFieldScreen(DataManager *dataManager);
    void gameStatusObserver();
    void showMessage(const std::string& message) const;
    void showUpdatedScreen(Field *field) const;
    void showEnemyInfo(std::map<CellPoint, Enemy *> *enemies) const;
    void showInventory(MainHero *hero, bool withSerialNumber = false) const;
    void showHeroAchievement(std::map<std::basic_string<char>, int> &achievement) const;
    std::string generateTitleForThingAction(const std::string &nameThing, const std::map<std::string, double> &properties,
                                char takeKey);
    void clearScreen() const;
};