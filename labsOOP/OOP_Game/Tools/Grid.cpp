#include "Grid.h"

Grid::Grid(int height, int width): height(height), width(width) {
	grid = new Cell*[height];
	for (int i = 0; i < height; ++i) {
		grid[i] = new Cell[width];
	}
}

Grid::Grid(int height, int width, Cell **grid) {
	this->grid = new Cell*[height];
	for (int i = 0; i < height; ++i) {
		this->grid[i] = new Cell[width];
		for (int j = 0; j < width; ++j) {
			this->grid[i][j] = grid[i][j];
		}
	}
}

Grid::~Grid() {
	for (int i = 0; i < height; ++i) {
		delete[] grid[i];
	}
	delete[] grid;
}

void Grid::setElem(CellPoint point, Cell cell) {
	if (isValidIndexes(point.getX(), point.getY())) {
		grid[point.getX()][point.getY()] = cell;
	} else {
		throw std::exception();
	}
}

Cell Grid::getElem(CellPoint point) const {
	if(isValidIndexes(point.getX(), point.getY())) {
		return grid[point.getX()][point.getY()];
	} else {
		throw std::exception();
	}
}

bool Grid::isValidIndexes(int height, int width) const {
	return 0 <= height && height < this->height && 0 <= width && width < this->width;
}

bool Grid::isValidSizes(int height, int width) const {
	return DOWN_LIMIT_HEIGHT <= height && height < UP_LIMIT_HEIGHT &&
			DOWN_LIMIT_WIDTH <= width && width < UP_LIMIT_WIDTH;
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

Grid::Grid() {
	height = 0;
	width = 0;
	grid = nullptr;
}

int Grid::getHeight() const {
	return height;
}

int Grid::getWidth() const {
	return width;
}


