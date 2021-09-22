#include <algorithm>
#include <iostream>
#include "Grid.h"

Grid::Grid(int height, int width): height(height), width(width) {
//    if (!isValidHeight(height))
//        this->height = std::min(UP_LIMIT_HEIGHT, std::max(DOWN_LIMIT_HEIGHT, height));
//    if (!isValidWidth(width))
//        this->width = std::min(UP_LIMIT_WIDTH, std::max(DOWN_LIMIT_WIDTH, width));
//    grid = new Cell*[height];
//	for (int i = 0; i < height; ++i) {
//		grid[i] = new Cell[width];
//	}
    // TODO
}

Grid::Grid(int height, int width, Cell **grid): height(height), width(width) {
    // TODO
}

Grid::Grid() {
    height = 0;
    width = 0;
    grid = nullptr;
}

void Grid::init(int height, int width) {
    this->height = std::min(UP_LIMIT_HEIGHT, std::max(DOWN_LIMIT_HEIGHT, height));
    this->width = std::min(UP_LIMIT_WIDTH, std::max(DOWN_LIMIT_WIDTH, width));
    this->grid = new Cell*[this->height];
    for (int i = 0; i < this->height; ++i) {
        this->grid[i] = new Cell[this->width];
    }
}

Grid::~Grid() {
    for (int i = 0; i < height; ++i) {
		delete[] grid[i];
	}
	delete[] grid;
}

void Grid::clear() {
    for (int i = 0; i < this->height; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
    height = 0;
    width = 0;
    grid = nullptr;
}

void Grid::resizeGrid(int height, int width, Cell **newGrid) {
    if (!isValidSizes(height, width)) {
        throw std::exception();
    }
    clear();
    grid = new Cell*[height];
    for (int i = 0; i < height; ++i) {
        grid[i] = new Cell[width];
        if (newGrid != nullptr) {
            for (int j = 0; j < width; ++j) {
                grid[i][j] = newGrid[i][j];
            }
        }
    }
    this->height = height;
    this->width = width;
}

void Grid::setElem(CellPoint point, Cell cell) {
	if (isValidIndexes(point.getX(), point.getY())) {
		grid[point.getY()][point.getX()] = cell;
	} else {
		throw std::exception();
	}
}

Cell Grid::getElem(CellPoint point) const {
	if(isValidIndexes(point.getX(), point.getY())) {
		return grid[point.getY()][point.getX()];
	} else {
		throw std::exception();
	}
}

int Grid::getHeight() const {
    return height;
}

int Grid::getWidth() const {
    return width;
}

bool Grid::isValidIndexes(int x, int y) const {
	return isValidXPos(x) && isValidYPos(y);
}

bool Grid::isValidSizes(int height, int width) const {
	return isValidHeight(height) && isValidWidth(width);
}

bool Grid::isValidHeight(int height) const {
    return DOWN_LIMIT_HEIGHT <= height && height < UP_LIMIT_HEIGHT;
}

bool Grid::isValidWidth(int width) const {
    return DOWN_LIMIT_WIDTH <= width && width < UP_LIMIT_WIDTH;
}

bool Grid::isValidXPos(int x) const {
    return 0 <= x && x < this->width;
}


bool Grid::isValidYPos(int y) const {
    return 0 <= y && y < this->height;
}

Grid::Grid(const Grid &grid) {
    this->grid = new Cell*[grid.height];
    for (int i = 0; i < grid.height; ++i) {
        this->grid[i] = new Cell[grid.width];
    }
}

Grid &Grid::operator=(const Grid &grid) {
    if (&grid == this)
        return *this;

    for (int i = 0; i < this->height; ++i) {
        delete[] this->grid[i];
    }
    delete[] this->grid;

    this->grid = new Cell*[grid.height];
    for (int i = 0; i < grid.height; ++i) {
        this->grid[i] = new Cell[grid.width];
        for (int j = 0; j < grid.width; ++j) {
            this->grid[i][j] = grid.grid[i][j];
        }
    }
    height = grid.height;
    width = grid.width;
    return *this;
}

Grid::Grid(Grid &&grid): grid(grid.grid), height(grid.height), width(grid.width)  {
    grid.grid = nullptr;
    grid.height = 0;
    grid.width = 0;
}

Grid& Grid::operator=(Grid &&grid) {
    if (&grid == this)
        return *this;

    for (int i = 0; i < this->height; ++i) {
        delete[] this->grid[i];
    }
    delete[] this->grid;

    this->grid = grid.grid;
    this->height = grid.height;
    this->width = grid.width;
    grid.grid = nullptr;
    grid.height = 0;
    grid.width = 0;
    return *this;
}


