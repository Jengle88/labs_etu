#pragma once
#include "../../Tools/Grid.h"
#include "../../Tools/FieldIterator.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#define PERCENT_WALLS 45

class Field {
	Grid field;
	CellPoint start;
	CellPoint finish;
    CellPoint heroPos;
	bool wayGenerated = false;
    bool wallsGenerated = false;
    bool chosenStartFinish = false;
    int countWalls = 0;
    int distStartFinish = 2;

    bool isCorrectStartFinish(CellPoint start, CellPoint finish) const;
	bool isCorrectDistStartFinish(CellPoint start, CellPoint finish) const;
	bool isValidIndexes(int x, int y) const;
    CellPoint generateBorderPoint();
    void generateStartFinishWay();
    void generateWayWithoutWalls(CellPoint start, CellPoint finish);
    void generateWalls(int countWalls);

public:
    Field();
    Field(int height, int width, CellPoint start = CellPoint(0,0), CellPoint finish = CellPoint(0,0), Grid grid = Grid());
    Field(const Field& field);
    Field& operator=(const Field& field);
    Field(Field && field);
    Field& operator=(Field&& field);

    bool generateFullField(int countWalls);
    void cleanStartFinishWay();
    void moveHero(CellPoint to);

    void printField(); // нужно для DEMO

    Cell getElem(CellPoint point) const;
    void setElem(CellPoint point, CellObject object);
    int getHeight() const;
    int getWidth() const;
    bool getStatusWay() const;
    bool getStatusWalls() const;
    bool getStatusStartFinish() const;
    FieldIterator getFieldIterator();
    CellPoint getHeroPos();
    void setHeroOnStart();

    friend class FieldScreen;
};











