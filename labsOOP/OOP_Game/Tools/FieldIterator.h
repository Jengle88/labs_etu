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

    FieldIterator& operator++();
    FieldIterator operator++(int);
    FieldIterator& operator--();
    FieldIterator operator--(int);
    void moveDelta(int deltaX, int deltaY);
    void moveTo(int posX, int posY);

    Cell getElem() const;
    void setElem(Cell cell);
    CellPoint getCurrentPosition() const;
};
