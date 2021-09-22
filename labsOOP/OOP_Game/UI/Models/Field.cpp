#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "Field.h"

Field::Field() {
}

//Field::Field(Grid field, CellPoint start, CellPoint finish) {
////    this->field = field;
//    std::cerr << "fill this->field\n";
//    this->field = Grid(field.getHeight(), field.getWidth());// Заменить на copy-конструктор
//    std::cerr << "filling this->field done\n";
//    for (int i = 0; i < field.getHeight(); ++i) {
//        for (int j = 0; j < field.getWidth(); ++j) {
//            this->field.setElem(CellPoint(j, i), field.getElem(CellPoint(j, i)));
//        }
//    }
//    this->start = start;
//    this->finish = finish;
//    if (isCorrectStartFinish(start, finish)) {
//        chosenStartFinish = true;
//    }
//}

bool Field::isValidIndexes(int x, int y) const {
    return 0 <= x && x < field.getWidth() && 0 <= y && y < field.getHeight();
}

bool Field::isCorrectStartFinish(CellPoint start, CellPoint finish) const {
    return isValidIndexes(start.getX(), start.getY()) &&
           isValidIndexes(finish.getX(), finish.getY()) &&
           isCorrectDistStartFinish(start, finish);
}

bool Field::isCorrectDistStartFinish(CellPoint start, CellPoint finish) const {
    return abs(start.getX() - finish.getX()) +
           abs(start.getY() - finish.getY()) >= DIST_START_FINISH;
}

void Field::generateStartFinishWay() {
    srand(time(0));
    while (!isCorrectDistStartFinish(this->start, this->finish)) {
        this->start = generateBorderPoint(); // нельзя выносить за while, тк возможна генерация в середине сетки,
        this->finish = generateBorderPoint(); // что сократит макс кол-во длины на половину
    }
    chosenStartFinish = true;
    field.setElem(start,
                  Cell(CellObject(TypeCell::START, TypeObject::NOTHING)));
    generateWay(this->start, this->finish);
    field.setElem(finish,
                  Cell(CellObject(TypeCell::FINISH, TypeObject::NOTHING)));
    wayGenerated = true;
}

CellPoint Field::generateBorderPoint() {
    switch (rand() % 4) {
        case 0:
            return {0,
                    rand() % this->field.getHeight()};
        case 1:
            return {this->field.getWidth() - 1,
                    rand() % this->field.getHeight()};
        case 2:
            return {rand() % this->field.getWidth(),
                    0};
        case 3:
            return {rand() % this->field.getWidth(),
                    this->field.getHeight() - 1};
    }
    return {0, 0};
}

void Field::generateWay(const CellPoint start, const CellPoint finish) {
    auto calcDist = [](int stx, int sty, int finx, int finy) {
        return abs(stx - finx) + abs(sty - finy);
    }; // функция подсчёта расстояния между точками

    auto rightWay = [this, &calcDist, &finish](int stx, int sty, int curDist) {
        return 0 <= stx && stx < field.getWidth() && 0 <= sty &&
               sty < field.getHeight() && calcDist(stx, sty, finish.getX(), finish.getY()) < curDist;
    }; // функция для контроля приближения к финишной точке


    int dist = calcDist(start.getX(), start.getY(), finish.getX(), finish.getY());
    srand(time(0));
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
                    field.setElem(CellPoint(stx, sty), Cell(
                            CellObject(TypeCell::WAY, TypeObject::NOTHING)));
                }
                break;
            case 1:
                if (rightWay(stx, sty + deltaY, dist)) { // нужно, чтобы блокировать способ, который уже не нужен
                    sty += deltaY;
                    dist = calcDist(stx, sty, finx, finy);
                    field.setElem(CellPoint(stx, sty), Cell(
                            CellObject(TypeCell::WAY, TypeObject::NOTHING)));
                }
        }
    }
}

void Field::generateWalls(int countWalls) {
    if (!wayGenerated)
        throw std::exception(); // путь не сгенерирован

    if ((double) countWalls / (field.getWidth() * field.getHeight()) * 100 > PERCENT_WALLS) {
        countWalls = double(PERCENT_WALLS) / 100 * (field.getWidth() * field.getHeight());
        std::cerr << "Слишком много стен. Количество уменьшено до " << countWalls << '\n';
    }

    int cntSetWalls = 0;
    srand(time(0));
    while (cntSetWalls < countWalls) {
        CellPoint point = CellPoint(rand() % field.getWidth(), rand() % field.getHeight());
        if (field.getElem(point).getValue().getTypeCell() == TypeCell::EMPTY) {
            field.setElem(point, Cell(CellObject(TypeCell::WALL, TypeObject::NOTHING)));
            cntSetWalls++;
        }
    }
    this->countWalls = countWalls;
    wallsGenerated = true;
}

void Field::printField() {
    for (int i = 0; i < field.getWidth() + 2; ++i) {
        std::cout << '_';
    }
    std::cout << '\n';
    for (int i = 0; i < field.getHeight(); ++i) {
        std::cout << '|';
        for (int j = 0; j < field.getWidth(); ++j) {
            switch (field.getElem(CellPoint(j, i)).getValue().getTypeCell()) {
                case TypeCell::WAY:
                    std::cout << '*';
                    break;
                case TypeCell::WALL:
                    std::cout << '.';
                    break;
                case TypeCell::START:
                    std::cout << 'S';
                    break;
                case TypeCell::FINISH:
                    std::cout << 'F';
                    break;
                case TypeCell::EMPTY:
                    std::cout << ' ';
                    break;
            }
        }
        std::cout << '|';
        std::cout << '\n';
    }
    for (int i = 0; i < field.getWidth() + 2; ++i) {
        std::cout << '_';
    }
    std::cout << '\n';
}

Field::Field(int height, int width, CellPoint start, CellPoint finish) {
    this->field.init(height, width);// Заменить на copy-конструктор
    this->start = start;
    this->finish = finish;
    if (isCorrectStartFinish(start, finish)) {
        chosenStartFinish = true;
    }
}

void Field::generateFullField(int countWalls) {
    this->generateStartFinishWay();
//    this->generateWay(CellPoint(), CellPoint());
    this->generateWalls(countWalls);
}

int Field::getHeight() const {
    return field.height;
}

int Field::getWidth() const {
    return field.width;
}

FieldIterator Field::getFieldIterator() {
    return FieldIterator(&(this->field));
}