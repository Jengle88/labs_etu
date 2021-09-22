#pragma once

#include "Grid.h"

class FieldIterator {
    Grid * rootGrid;
    int posX;
    int posY;
    explicit FieldIterator(Grid * pGrid) : rootGrid(pGrid), posX(0), posY(0) {};
    friend class Field;
public:
    FieldIterator() = delete;
    void moveUp();
    void moveDown();
    void moveDownAndStart();

    void moveRight();
    void moveLeft();
    void moveTo(int deltaX, int deltaY);
    Cell getElem() const;
};
