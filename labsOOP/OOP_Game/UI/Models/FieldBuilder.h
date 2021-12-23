#pragma once
#include "../../Tools/CellPoint.h"
#include "../../Tools/SaveDataAdapter.h"
#include "../../Tools/Grid.h"

#define PERCENT_WALLS 35

class FieldBuilder {
protected:
    bool wayGenerated = false;
    bool wallsGenerated = false;
    bool chosenStartFinish = false;
    int distStartFinish;
public:
    // Генераторы

    virtual CellPoint generateBorderPoint(int height, int width) const = 0;
    virtual void generateStartFinishWay(int height, int width, CellPoint &start, CellPoint &finish, Grid &grid) = 0;
    virtual void generateWayWithoutWalls(CellPoint start, CellPoint finish, Grid &grid) = 0;
    virtual void generateWalls(int countWalls, Grid &grid, std::vector<CellPoint> &pointsOfWalls) = 0;

    //чекеры
    virtual bool isCorrectStartFinish(CellPoint start, CellPoint finish, Grid &grid) const = 0;
    virtual bool isCorrectDistStartFinish(CellPoint start, CellPoint finish) const = 0;

    virtual bool isWayGenerated() const = 0;
    virtual bool isWallsGenerated() const = 0;
    virtual bool isChosenStartFinish() const = 0;

    friend class Field;
};

