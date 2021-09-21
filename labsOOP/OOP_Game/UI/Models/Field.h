#include "../../Tools/Grid.h"

#define PERCENT_WALLS 45

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
public:
    Field();
//    Field(Grid field, CellPoint start = CellPoint(0, 0), CellPoint finish  = CellPoint(0, 0));
    Field(int height, int width, CellPoint start = CellPoint(0,0), CellPoint finish = CellPoint(0,0));
    void generateStartFinish();
    void generateWayToFinish();
    void generateWalls(int countWalls);
    void printField();
};

