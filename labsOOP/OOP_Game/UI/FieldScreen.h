#pragma once
#include "Models/Field.h"

enum MoveSide{
    UP = 'w',
    LEFT = 'a',
    RIGHT = 'd',
    DOWN = 's',
    EXIT = '`'
};

class FieldScreen {
    Field *field;
    void showStartingParams();
    void showUpdatedScreen() const;

    bool registerMovement(char &action);
    void requestMoveObject(CellPoint from, CellPoint to);
//    void requestGenerateObject(const CellPoint pos, const CellObject newObject); // на будущее
public:
    FieldScreen();
    void showStartFieldScreen();
    void gameStatusObserver();

};