#pragma once
#include "Grid.h"

class FieldIterator {
    Grid * rootGrid;
    int posX;
    int posY;
    explicit FieldIterator(Grid * pGrid) : rootGrid(pGrid), posX(0), posY(0) {};
    friend class Field; // т.к. Field должен возвращать итератор
public:
    FieldIterator() = delete;

    Cell getElem() const;
    void setElem(Cell cell);
    CellPoint getCurrentPosition() const;

    void moveDelta(int deltaX, int deltaY);
    void moveTo(int posX, int posY);

    FieldIterator& operator++();
    FieldIterator operator++(int);
    FieldIterator& operator--();
    FieldIterator operator--(int);
};
