#pragma once
#include "../../Tools/Grid.h"
#include "../../Tools/FieldIterator.h"
#define PERCENT_WALLS 45
#define DIST_START_FINISH 15

class Field {
	Grid field;
	CellPoint start;
	CellPoint finish;
	bool wayGenerated = false;
    bool wallsGenerated = false;
    bool chosenStartFinish = false;
    int countWalls = 0;

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

    void generateFullField(int countWalls);
    void cleanStartFinishWay();

    void printField();

    int getHeight() const;
    int getWidth() const;
    bool getStatusWay() const;
    bool getStatusWalls() const;
    bool getStatusStartFinish() const;
    FieldIterator getFieldIterator();

};











