#include "BuilderDefaultField.h"
#include "../../Logger/LoggerPull.h"


CellPoint BuilderDefaultField::generateBorderPoint(int height, int width) const {
    switch (rand() % 4) {
        case 0:
            return {0,
                    rand() % height};
        case 1:
            return {width - 1,
                    rand() % height};
        case 2:
            return {rand() % width,
                    0};
        case 3:
            return {rand() % width,
                    height - 1};
    }
    LoggerPull::writeData("gameLogs",
                          LoggerDataAdapter<std::string>("Были переданы стандартные сгенерированные точки"),
                          LoggerPull::LoggingType::Warning);
    return {0, 0};
}

// Удалять вещи из ThingsManager
void
BuilderDefaultField::generateStartFinishWay(int height, int width, CellPoint &start, CellPoint &finish, Grid &grid) {
    distStartFinish = std::max((width + height) / 2, 2);
    while (!isCorrectDistStartFinish(start, finish)) {
        start = generateBorderPoint(height, width); // нельзя выносить за while, тк возможна генерация в середине сетки,
        finish = generateBorderPoint(height, width); // что сократит макс кол-во длины на половину
    }
    chosenStartFinish = true;
    grid.setElem(start,
                  Cell(CellObject(TypeCell::START, TypeObject::NOTHING, false)));

    LoggerPull::writeData("gameLogs", LoggerDataAdapter<CellPoint>(start, "Точка старта"));
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<CellPoint>(finish, "Точка финиша"));

    generateWayWithoutWalls(start, finish, grid);
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Путь между стартом и финишем был сгенерирован"));
    grid.setElem(finish,
                  Cell(CellObject(TypeCell::FINISH, TypeObject::NOTHING, false)));
    wayGenerated = true;
}

// Удалять вещи из ThingsManager
void BuilderDefaultField::generateWayWithoutWalls(CellPoint start, CellPoint finish, Grid &grid) {
    auto calcDist = [](int stx, int sty, int finx, int finy) {
        return abs(stx - finx) + abs(sty - finy);
    }; // функция подсчёта расстояния между точками

    auto rightWay = [grid, &calcDist, &finish](int stx, int sty, int curDist) {
        return 0 <= stx && stx < grid.getWidth() && 0 <= sty &&
               sty < grid.getHeight() && calcDist(stx, sty, finish.getX(), finish.getY()) < curDist;
    }; // функция для контроля приближения к финишной точке

    int dist = calcDist(start.getX(), start.getY(), finish.getX(), finish.getY());
    int deltaX = -(start.getX() - finish.getX()) /
                 std::max(1, abs(start.getX() - finish.getX()));
    int deltaY = -(start.getY() - finish.getY()) /
                 std::max(1, abs(start.getY() - finish.getY()));
    int stx = start.getX(), sty = start.getY(), finx = finish.getX(), finy = finish.getY();
    while (stx != finx || sty != finy) {
        switch (rand() % 2) {
            case 0:
                if (rightWay(stx + deltaX, sty, dist)) { // нужно, чтобы блокировать способ, который уже не нужен
                    stx += deltaX;
                    dist = calcDist(stx, sty, finx, finy);
                    grid.setElem(CellPoint(stx, sty), Cell(
                            CellObject(TypeCell::WAY, TypeObject::NOTHING, false)));
                }
                break;
            case 1:
                if (rightWay(stx, sty + deltaY, dist)) { // нужно, чтобы блокировать способ, который уже не нужен
                    sty += deltaY;
                    dist = calcDist(stx, sty, finx, finy);
                    grid.setElem(CellPoint(stx, sty), Cell(
                            CellObject(TypeCell::WAY, TypeObject::NOTHING, false)));
                }
                break;
        }
    }
}

void BuilderDefaultField::generateWalls(int countWalls, Grid &grid, std::vector<CellPoint> &pointsOfWalls) {
    if (!wayGenerated) {
        LoggerPull::writeData("gameLogs",
                              LoggerDataAdapter<std::string>(
                                      "Попытка создать непроходимые клетки при не сгенерированном пути"),
                              LoggerPull::LoggingType::Error);
        throw std::logic_error(
                "Попытка создать непроходимые клетки при не сгенерированном пути"); // путь не сгенерирован
    }
    if ((double) countWalls / (grid.getWidth() * grid.getHeight()) * 100 > PERCENT_WALLS) {
        countWalls = double(PERCENT_WALLS) / 100 * (grid.getWidth() * grid.getHeight());
        std::cerr << "Слишком много стен. Количество уменьшено до " << countWalls << '\n';
    }
    int cntPlacedWalls = 0;
    while (cntPlacedWalls < countWalls) {
        CellPoint point = CellPoint(rand() % grid.getWidth(), rand() % grid.getHeight());
        if (grid.getElem(point).getValue().getTypeCell() == TypeCell::EMPTY) {
            grid.setElem(point, Cell(CellObject(TypeCell::WALL, TypeObject::NOTHING, false)));
            pointsOfWalls.push_back(point);
            cntPlacedWalls++;
        }
    }
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Непроходимые клетки были сгенерированы"));
    wallsGenerated = true;
}

bool BuilderDefaultField::isCorrectStartFinish(CellPoint start, CellPoint finish, Grid &grid) const {
    return grid.isValidIndexes(start.getX(), start.getY()) &&
           grid.isValidIndexes(finish.getX(), finish.getY()) &&
           isCorrectDistStartFinish(start, finish);
}

bool BuilderDefaultField::isCorrectDistStartFinish(CellPoint start, CellPoint finish) const {
    return abs(start.getX() - finish.getX()) +
           abs(start.getY() - finish.getY()) >= distStartFinish;
}

bool BuilderDefaultField::isWayGenerated() const {
    return wayGenerated;
}

bool BuilderDefaultField::isWallsGenerated() const {
    return wallsGenerated;
}

bool BuilderDefaultField::isChosenStartFinish() const {
    return chosenStartFinish;
}

BuilderDefaultField::BuilderDefaultField(int distStartFinish) {
    this->distStartFinish = distStartFinish;
}
