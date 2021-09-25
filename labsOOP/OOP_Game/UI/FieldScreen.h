#pragma once
#include "Models/Field.h"
#include <termios.h>
#include <unistd.h>
class FieldScreen {
    Field *field;
    void showStartingParams();
    void showUpdatedScreen() const;

    void registerMovement(char &action, int (*getch)());
    void requestMoveObject(CellPoint from, CellPoint to);
    void requestGenerateObject(const CellPoint pos, const CellObject newObject);
public:
    FieldScreen();
    void showStartFieldScreen();
    void gameStatusObserver();

};