#include "Grid.h"
#include "../Logger/LoggerDataAdapter.h"
#include "../Logger/LoggerPull.h"

Grid::Grid() {
    height = 0;
    width = 0;
    grid = std::vector<std::vector<Cell>>();
}

Grid::Grid(int height, int width, std::vector<std::vector<Cell>> grid) {
    this->height = std::min(UP_LIMIT_HEIGHT, std::max(DOWN_LIMIT_HEIGHT, height));
    this->width = std::min(UP_LIMIT_WIDTH, std::max(DOWN_LIMIT_WIDTH, width));
    this->grid.resize(this->height);
	for (int i = 0; i < this->height; ++i) {
        this->grid[i].resize(this->width);
        if (!grid.empty()) {
            for (int j = 0; j < this->width; ++j) {
                this->grid[i][j] = grid[i][j];
            }
        }
	}
}

Grid::Grid(const Grid &grid): height(grid.height), width(grid.width), pointsOfWalls(grid.pointsOfWalls) {
    this->grid.resize(grid.height);
    for (int i = 0; i < grid.height; ++i) {
        this->grid[i].resize(grid.width);
        for (int j = 0; j < grid.width; ++j) {
            this->grid[i][j] = grid.grid[i][j];
        }
    }
}

Grid &Grid::operator=(const Grid &grid) {
    if (&grid == this)
        return *this;
    this->grid.resize(grid.height);
    for (int i = 0; i < grid.height; ++i) {
        this->grid[i].resize(grid.width);
        for (int j = 0; j < grid.width; ++j) {
            this->grid[i][j] = grid.grid[i][j];
        }
    }
    pointsOfWalls = grid.pointsOfWalls;
    height = grid.height;
    width = grid.width;
    return *this;
}

Grid::Grid(Grid &&grid): grid(std::move(grid.grid)), height(grid.height), width(grid.width), pointsOfWalls(std::move(grid.pointsOfWalls))  {
    grid.grid.clear();
    grid.height = 0;
    grid.width = 0;
}

Grid& Grid::operator=(Grid &&grid) {
    if (&grid == this)
        return *this;
    this->grid = std::move(grid.grid);
    this->pointsOfWalls = std::move(grid.pointsOfWalls);
    this->height = grid.height;
    this->width = grid.width;
    grid.grid.clear();
    grid.pointsOfWalls.clear();
    grid.height = 0;
    grid.width = 0;
    return *this;
}

bool Grid::isValidIndexes(int x, int y) const {
    return isValidXPos(x) && isValidYPos(y);
}

bool Grid::isValidIndexes(int x, int y, int height, int width) {
    return isValidXPos(x, width) && isValidYPos(y, height);
}

bool Grid::isValidXPos(int x) const {
    return 0 <= x && x < this->width;
}

bool Grid::isValidXPos(int x, int width) {
    return 0 <= x && x < width;
}

bool Grid::isValidYPos(int y) const {
    return 0 <= y && y < this->height;
}

bool Grid::isValidYPos(int y, int height) {
    return 0 <= y && y < height;
}

bool Grid::isValidSizes(int height, int width) {
    return isValidHeight(height) && isValidWidth(width);
}

bool Grid::isValidHeight(int height) {
    return DOWN_LIMIT_HEIGHT <= height && height <= UP_LIMIT_HEIGHT;
}

bool Grid::isValidWidth(int width) {
    return DOWN_LIMIT_WIDTH <= width && width <= UP_LIMIT_WIDTH;
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
        LoggerPull::writeData("gameLogs",
                              LoggerDataAdapter<std::string>("Были переданы невалидные индексы в setElem"),
                                      LoggerPull::LoggingType::Error);
        throw std::invalid_argument("Были переданы невалидные индексы в setElem");
    }
}

Cell Grid::getElem(CellPoint point) const {
    if(isValidIndexes(point.getX(), point.getY())) {
        return grid[point.getY()][point.getX()];
    } else {
        LoggerPull::writeData("gameLogs",
                              LoggerDataAdapter<std::string>("Были переданы невалидные индексы в getElem"),
                              LoggerPull::LoggingType::Error);
        throw std::invalid_argument("Были переданы невалидные индексы в getElem");
    }
}

const std::vector<CellPoint> &Grid::getPointsOfWalls() const {
    return pointsOfWalls;
}

void Grid::rebuildGrid(const SaveDataAdapter& adapter) {
    height = adapter.getHeightField();
    width = adapter.getWidthField();
    grid.clear();
    grid.resize(adapter.getHeightField(), std::vector<Cell>(adapter.getWidthField()));
    for (const auto &wallPos: adapter.getWalls()) {
        setElem(wallPos, Cell(CellObject(TypeCell::WALL, TypeObject::NOTHING, false)));
        pointsOfWalls.push_back(wallPos);
    }
}

