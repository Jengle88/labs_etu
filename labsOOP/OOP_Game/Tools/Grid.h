#pragma once
#include "../UI/Models/Cell.h"
#include <exception>
#include <algorithm>
#include <iostream>

#define UP_LIMIT_HEIGHT (int)1e4
#define DOWN_LIMIT_HEIGHT (int)2
#define UP_LIMIT_WIDTH (int)1e4
#define DOWN_LIMIT_WIDTH (int)2

class Grid {
	int height;
	int width;
	Cell** grid;
	bool isValidIndexes(int x, int y) const;
    bool isValidXPos(int x) const;
    bool isValidYPos(int y) const;
	bool isValidHeight(int height) const;
	bool isValidWidth(int width) const;
	bool isValidSizes(int height, int width) const;
public:
	Grid();
	Grid(int height, int width, Cell **grid = nullptr);
    Grid(const Grid& grid);
    Grid& operator=(const Grid& grid);
    Grid(Grid&& grid);
    Grid& operator=(Grid&& grid);
    ~Grid();

	int getHeight() const;
	int getWidth() const;
	void setElem(CellPoint point, Cell cell);
	Cell getElem(CellPoint point) const;
	void clear();
	void resizeGrid(int height, int width, Cell **newGrid = nullptr);

    friend class Field;
    friend class FieldIterator;

};
