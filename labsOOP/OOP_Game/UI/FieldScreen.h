#include "Models/Field.h"

class FieldScreen {
    Field *field;
    bool fieldReady;

    FieldScreen();
    void showStartingParams();
    void showFieldScreen() const;
    void showUpdatedScreen() const;
    void registerMovement();
    void requestMoveObject(CellPoint from, CellPoint to) const;
    void requestGenerateObject(CellPoint pos, CellObject newObject);

};