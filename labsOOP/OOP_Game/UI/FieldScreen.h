#pragma once
#include "Models/Field.h"
#include "../Objects/ThingsManager.h"
#include <termios.h>
#include <unistd.h>
#include "../Tools/Printer.h"
#include "FightScreen.h"

enum MoveSide{
    UP = 'w',
    LEFT = 'a',
    RIGHT = 'd',
    DOWN = 's',
    TAKE = 'e',
    FIGHT = 'f',
    FINISH_OUT = 'q',
    EXIT = '`'
};

class FieldScreen {
    Field *field;
    ThingsManager thingsManager;
    DataManager *dataManager;
    void showStartingParamsAndGenerateField(DataManager *dataManager);
    void showUpdatedScreen() const;
    bool registerMovement(char &action, std::string& gameAction);
    void requestMoveHero(CellPoint from, CellPoint to, std::string& gameAction);
    void requestTakeObject(CellPoint point);
    int requestStartFight(CellPoint point);
    bool requestMoveOut() const;
    std::string generateTitleForThingAction(const std::string& nameThing, const std::vector<double>& properties);
public:
    FieldScreen();
    ~FieldScreen();
    void showStartFieldScreen(DataManager *dataManager);
    void gameStatusObserver();

};