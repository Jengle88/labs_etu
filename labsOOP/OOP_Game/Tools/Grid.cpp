#include "Grid.h"

Grid::Grid() {
    height = 0;
    width = 0;
    grid = std::vector<std::vector<Cell>>();
}

Grid::Grid(int height, int width, std::vector<std::vector<Cell>> grid/*Cell **grid*/) {
    this->height = std::min(UP_LIMIT_HEIGHT, std::max(DOWN_LIMIT_HEIGHT, height));
    this->width = std::min(UP_LIMIT_WIDTH, std::max(DOWN_LIMIT_WIDTH, width));
    this->grid.resize(this->height);
//    this->grid = new Cell*[this->height];
	for (int i = 0; i < this->height; ++i) {
//		this->grid[i] = new Cell[this->width];
        this->grid[i].resize(this->width);
        if (!grid.empty()) {
            for (int j = 0; j < this->width; ++j) {
                this->grid[i][j] = grid[i][j];
            }
        }
	}
//    if (!grid.empty()) {
//        for (int i = 0; i < this->height; ++i) {
//            for (int j = 0; j < this->width; ++j) {
//                this->grid[i][j] = grid[i][j];
//            }
//        }
//    }
}

Grid::Grid(const Grid &grid): height(grid.height), width(grid.width) {
//    this->grid = new Cell*[grid.height];
    this->grid.resize(grid.height);
    for (int i = 0; i < grid.height; ++i) {
//        this->grid[i] = new Cell[grid.width];
        this->grid[i].resize(grid.width);
        for (int j = 0; j < grid.width; ++j) {
            this->grid[i][j] = grid.grid[i][j];
        }
    }
//    height = grid.height;
//    width = grid.width;
}

Grid &Grid::operator=(const Grid &grid) {
    if (&grid == this)
        return *this;
//    for (int i = 0; i < this->height; ++i) {
//        delete[] this->grid[i];
//    }
//    delete[] this->grid;
//    this->grid = new Cell*[grid.height];
    this->grid.resize(grid.height);
    for (int i = 0; i < grid.height; ++i) {
//        this->grid[i] = new Cell[grid.width];
        this->grid[i].resize(grid.width);
        for (int j = 0; j < grid.width; ++j) {
            this->grid[i][j] = grid.grid[i][j];
        }
    }
    height = grid.height;
    width = grid.width;
    return *this;
}

Grid::Grid(Grid &&grid): grid(std::move(grid.grid)), height(grid.height), width(grid.width)  {
//    grid.grid = nullptr;
    grid.grid.clear();
    grid.height = 0;
    grid.width = 0;
}

Grid& Grid::operator=(Grid &&grid) {
    if (&grid == this)
        return *this;
//    for (int i = 0; i < this->height; ++i) {
//        delete[] this->grid[i];
//    }
//    delete[] this->grid;
    this->grid = std::move(grid.grid);
    this->height = grid.height;
    this->width = grid.width;
//    grid.grid = nullptr;
    grid.grid.clear();
    grid.height = 0;
    grid.width = 0;
    return *this;
}

Grid::~Grid() {
//    for (int i = 0; i < height; ++i) {
//		delete[] grid[i];
//	}
//	delete[] grid;
}

bool Grid::isValidIndexes(int x, int y) const {
    return isValidXPos(x) && isValidYPos(y);
}

bool Grid::isValidSizes(int height, int width) const {
    return isValidHeight(height) && isValidWidth(width);
}

bool Grid::isValidHeight(int height) {
    return DOWN_LIMIT_HEIGHT <= height && height <= UP_LIMIT_HEIGHT;
}

bool Grid::isValidWidth(int width) {
    return DOWN_LIMIT_WIDTH <= width && width <= UP_LIMIT_WIDTH;
}

bool Grid::isValidXPos(int x) const {
    return 0 <= x && x < this->width;
}


bool Grid::isValidYPos(int y) const {
    return 0 <= y && y < this->height;
}

int Grid::getHeight() const {
    return height;
}

int Grid::getWidth() const {
    return width;
}

void Grid::setElem(CellPoint point, Cell cell) {
    if (isValidIndexes(point.getX(), point.getY())) {
        grid[point.getY()][point.getX()] = cell;
    } else {
        throw -1;
    }
}

Cell Grid::getElem(CellPoint point) const {
    if(isValidIndexes(point.getX(), point.getY())) {
        return grid[point.getY()][point.getX()];
    } else {
        throw -1;
    }
}

void Grid::clear() {
//    for (int i = 0; i < this->height; ++i) {
//        delete[] grid[i];
//    }
//    delete[] grid;
    grid.clear();
    height = 0;
    width = 0;
//    grid = nullptr;
}

void Grid::resizeCleanGrid(int height, int width, std::vector<std::vector<Cell>> grid) {
    if (!isValidSizes(height, width)) {
        throw -1;
    }
    this->grid.resize(height);
    for (int i = 0; i < height; ++i) {
        this->grid[i].resize(width);
        if (!grid.empty()) {
            for (int j = 0; j < grid.size(); ++j) {
                this->grid[i][j] = grid[i][j];
            }
        }
    }
//    clear();
//    grid = new Cell*[height];
//    for (int i = 0; i < height; ++i) {
//        grid[i] = new Cell[width];
//        if (newGrid != nullptr) {
//            for (int j = 0; j < width; ++j) {
//                grid[i][j] = newGrid[i][j];
//            }
//        }
//    }
    this->height = height;
    this->width = width;
}