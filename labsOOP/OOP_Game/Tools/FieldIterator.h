#pragma once
#include "Grid.h"

class FieldIterator { // паттерн Iterator
    Grid * rootGrid;
    int posX; // лучше так, чем переприсваивание в CellPoint
    int posY;
    explicit FieldIterator(Grid * pGrid) : rootGrid(pGrid), posX(0), posY(0) {};
    friend class Field; // т.к. Field должен возвращать итератор
public:
    FieldIterator() = delete;

    Cell getElem() const;
    CellPoint getCurrentPosition() const;

    virtual void moveDelta(int deltaX, int deltaY);
    virtual void moveTo(int posX, int posY);

    virtual FieldIterator& operator++();
    virtual FieldIterator operator++(int);
    virtual FieldIterator& operator--();
    virtual FieldIterator operator--(int);
};
