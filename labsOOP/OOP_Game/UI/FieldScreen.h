#pragma once
#include "Models/Field.h"
#include "../Objects/ThingsManager.h"

enum MoveSide{
    UP = 'w',
    LEFT = 'a',
    RIGHT = 'd',
    DOWN = 's',
    EXIT = '`'
};

class FieldScreen {
    Field *field;
    ThingsManager thingsManager;
    void showStartingParams();
    void showUpdatedScreen() const;

    bool registerMovement(char &action);
    void requestMoveObject(CellPoint from, CellPoint to);
//    void requestGenerateObject(const CellPoint pos, const CellObject newObject); // на будущее
public:
    FieldScreen();
    ~FieldScreen();
    void showStartFieldScreen();
    void gameStatusObserver();

};