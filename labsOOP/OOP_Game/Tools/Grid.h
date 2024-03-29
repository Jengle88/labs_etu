#pragma once
#include "../UI/Models/Cell.h"
#include "SaveDataAdapter.h"
#include <algorithm>
#include <iostream>

#define UP_LIMIT_HEIGHT (int)50
#define DOWN_LIMIT_HEIGHT (int)5
#define UP_LIMIT_WIDTH (int)130
#define DOWN_LIMIT_WIDTH (int)5

class Grid {
	int height = 0;
	int width = 0;
	std::vector<std::vector<Cell>> grid;
    std::vector<CellPoint> pointsOfWalls;

    bool isValidXPos(int x) const;
    static bool isValidXPos(int x, int width);
    bool isValidYPos(int y) const;
    static bool isValidYPos(int y, int height);
    static bool isValidSizes(int height, int width);
    static bool isValidHeight(int height);
    static bool isValidWidth(int width);

    friend class FieldScreen; // для доступа к функциям проверки высоты и ширины
    friend class SaveDataReader;
    friend class Field; // т.к Field работает с Grid
    friend class FieldIterator; // т.к FieldIterator работает с Grid

public:
	Grid();
	Grid(int height, int width, std::vector<std::vector<Cell>> grid = std::vector<std::vector<Cell>>());
    ~Grid() = default;
    Grid(const Grid& grid);
    Grid& operator=(const Grid& grid);
    Grid(Grid&& grid);
    Grid& operator=(Grid&& grid);
    void rebuildGrid(const SaveDataAdapter& adapter);
	int getHeight() const;
	int getWidth() const;
	void setElem(CellPoint point, Cell cell);
	Cell getElem(CellPoint point) const;
    const std::vector<CellPoint>& getPointsOfWalls() const;
    bool isValidIndexes(int x, int y) const;
    static bool isValidIndexes(int x, int y, int height, int width);
};
