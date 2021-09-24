#include "Models/Field.h"

class FieldScreen {
    Field field;
    bool fieldReady;

    void showFieldScreen(int heightField, int widthField, int countWalls);
    void updateScreen();
    void requestMoveObject();
    void requestGenerateObject();

};