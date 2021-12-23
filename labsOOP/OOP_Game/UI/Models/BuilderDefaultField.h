#pragma once

#include "FieldBuilder.h"

class BuilderDefaultField : public FieldBuilder {
public:
    explicit BuilderDefaultField(int distStartFinish);

    CellPoint generateBorderPoint(int height, int width) const override;
    void generateStartFinishWay(int height, int width, CellPoint &start, CellPoint &finish, Grid &grid) override;
    void generateWayWithoutWalls(CellPoint start, CellPoint finish, Grid &grid) override;
    void generateWalls(int countWalls, Grid &grid, std::vector<CellPoint> &pointsOfWalls) override;

    bool isCorrectStartFinish(CellPoint start, CellPoint finish, Grid &grid) const override;
    bool isCorrectDistStartFinish(CellPoint start, CellPoint finish) const override;
    bool isWayGenerated() const override;
    bool isWallsGenerated() const override;
    bool isChosenStartFinish() const override;
};


