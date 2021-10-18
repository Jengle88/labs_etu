#include "Field.h"

#include <random>
#include "../../Characters/Archer.h"
#include "../../Characters/Gargoyle.h"

Field::Field() {}


Field::Field(int height, int width, CellPoint start, CellPoint finish, Grid grid) {
    if (!grid.grid.empty())
        this->field = grid;
    else
        this->field = Grid(height, width);
    this->start = start;
    this->finish = finish;
    if (isCorrectStartFinish(start, finish)) {
        chosenStartFinish = true;
    }
}

Field::Field(const Field &field) {
    this->field = field.field;
    this->start = field.start;
    this->finish = field.finish;
    this->wayGenerated = field.wayGenerated;
    this->wallsGenerated = field.wallsGenerated;
    this->chosenStartFinish = field.chosenStartFinish;
    this->countWalls = field.countWalls;
}

Field &Field::operator=(const Field &field) {
    if (&field == this)
        return *this;
    this->field = field.field;
    start = field.start;
    finish = field.finish;
    wayGenerated = field.wayGenerated;
    wallsGenerated = field.wallsGenerated;
    chosenStartFinish = field.chosenStartFinish;
    countWalls = field.countWalls;
    return *this;
}

Field::Field(Field &&field) {
    this->field = std::move(field.field);
    this->start = field.start;
    this->finish = field.finish;
    this->chosenStartFinish = field.chosenStartFinish;
    this->wayGenerated = field.wayGenerated;
    this->wallsGenerated = field.wallsGenerated;
    this->countWalls = field.countWalls;
    field.start = CellPoint();
    field.finish = CellPoint();
    field.chosenStartFinish = false;
    field.wayGenerated = false;
    field.wallsGenerated = false;
    field.countWalls = 0;
}

Field &Field::operator=(Field &&field) {
    if (&field == this)
        return *this;
    this->field = std::move(field.field);
    this->start = field.start;
    this->finish = field.finish;
    this->chosenStartFinish = field.chosenStartFinish;
    this->wayGenerated = field.wayGenerated;
    this->wallsGenerated = field.wallsGenerated;
    this->countWalls = field.countWalls;
    field.start = CellPoint();
    field.finish = CellPoint();
    field.chosenStartFinish = false;
    field.wayGenerated = false;
    field.wallsGenerated = false;
    field.countWalls = 0;
    return *this;
}

bool Field::isCorrectStartFinish(CellPoint start, CellPoint finish) const {
    return this->field.isValidIndexes(start.getX(), start.getY()) &&
           this->field.isValidIndexes(finish.getX(), finish.getY()) &&
           isCorrectDistStartFinish(start, finish);
}

bool Field::isCorrectDistStartFinish(CellPoint start, CellPoint finish) const {
    return abs(start.getX() - finish.getX()) +
           abs(start.getY() - finish.getY()) >= distStartFinish;
}


CellPoint Field::generateBorderPoint() const {
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

// Удалять вещи из ThingsManager
void Field::generateStartFinishWay() {
    distStartFinish = std::max((field.getWidth() + field.getHeight()) / 2, 2);
    while (!isCorrectDistStartFinish(this->start, this->finish)) {
        this->start = generateBorderPoint(); // нельзя выносить за while, тк возможна генерация в середине сетки,
        this->finish = generateBorderPoint(); // что сократит макс кол-во длины на половину
    }
    chosenStartFinish = true;
    field.setElem(start,
                  Cell(CellObject(TypeCell::START, TypeObject::NOTHING, false)));
    generateWayWithoutWalls(this->start, this->finish);
    field.setElem(finish,
                  Cell(CellObject(TypeCell::FINISH, TypeObject::NOTHING, false)));
    wayGenerated = true;
}

// Удалять вещи из ThingsManager
void Field::generateWayWithoutWalls(CellPoint start, CellPoint finish) {
    auto calcDist = [](int stx, int sty, int finx, int finy) {
        return abs(stx - finx) + abs(sty - finy);
    }; // функция подсчёта расстояния между точками

    auto rightWay = [this, &calcDist, &finish](int stx, int sty, int curDist) {
        return 0 <= stx && stx < field.getWidth() && 0 <= sty &&
               sty < field.getHeight() && calcDist(stx, sty, finish.getX(), finish.getY()) < curDist;
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
                    field.setElem(CellPoint(stx, sty), Cell(
                            CellObject(TypeCell::WAY, TypeObject::NOTHING, false)));
                }
                break;
            case 1:
                if (rightWay(stx, sty + deltaY, dist)) { // нужно, чтобы блокировать способ, который уже не нужен
                    sty += deltaY;
                    dist = calcDist(stx, sty, finx, finy);
                    field.setElem(CellPoint(stx, sty), Cell(
                            CellObject(TypeCell::WAY, TypeObject::NOTHING, false)));
                }
                break;
        }
    }
}

// Удалять вещи из ThingsManager
void Field::generateWalls(int countWalls) {
    if (!wayGenerated)
        throw -1; // путь не сгенерирован
    if ((double) countWalls / (field.getWidth() * field.getHeight()) * 100 > PERCENT_WALLS) {
        countWalls = double(PERCENT_WALLS) / 100 * (field.getWidth() * field.getHeight());
        std::cerr << "Слишком много стен. Количество уменьшено до " << countWalls << '\n';
    }
    int cntPlacedWalls = 0;
    while (cntPlacedWalls < countWalls) {
        CellPoint point = CellPoint(rand() % field.getWidth(), rand() % field.getHeight());
        if (field.getElem(point).getValue().getTypeCell() == TypeCell::EMPTY) {
            field.setElem(point, Cell(CellObject(TypeCell::WALL, TypeObject::NOTHING, false)));
            cntPlacedWalls++;
        }
    }
    this->countWalls = countWalls;
    wallsGenerated = true;
}

bool Field::generateFullField(int countWalls) {
    this->generateStartFinishWay();
    this->generateWalls(countWalls);
    return this->getStatusStartFinish() && this->getStatusWay() && this->getStatusWalls();
}

void Field::moveHero(CellPoint to) {
    if (getElem(to).getValue().getTypeCell() != TypeCell::WALL) {
        setElem(heroPos, CellObject(getElem(heroPos).getValue().getTypeCell(), TypeObject::NOTHING,
                                    getElem(heroPos).getValue().isThing()));
        setElem(to,
                CellObject(getElem(to).getValue().getTypeCell(), TypeObject::HERO, getElem(to).getValue().isThing()));
        heroPos = to;
    }
}

void Field::printField() {
    for (int i = 0; i < field.getWidth() + 2; ++i) {
        std::cout << '_';
    }
    std::cout << '\n';
    for (int i = 0; i < field.getHeight(); ++i) {
        std::cout << '|';
        for (int j = 0; j < field.getWidth(); ++j) {
            std::cout << field.getElem(CellPoint(j, i)).getValue().getCellAsChar();
        }
        std::cout << '|';
        std::cout << '\n';
    }
    for (int i = 0; i < field.getWidth() + 2; ++i) {
        std::cout << '_';
    }
    std::cout << '\n';
}

Cell Field::getElem(CellPoint point) const {
    return field.getElem(point);
}

void Field::setElem(CellPoint point, CellObject object) {
    field.setElem(point, Cell(object));
}

int Field::getHeight() const {
    return field.height;
}

int Field::getWidth() const {
    return field.width;
}

bool Field::getStatusWay() const {
    return wayGenerated;
}

bool Field::getStatusWalls() const {
    return wallsGenerated;
}

bool Field::getStatusStartFinish() const {
    return chosenStartFinish;
}

FieldIterator Field::getFieldIterator() {
    return FieldIterator(&(this->field));
}

CellPoint Field::getHeroPos() const {
    return heroPos;
}

void Field::setHeroOnStart() {
    field.setElem(start, Cell(CellObject(TypeCell::START, TypeObject::HERO, false)));
    heroPos = start;
}

void Field::createHero(double health, double attackPower, double protection, double luck) {
    hero = MainHero(CharacterType::MAIN_HERO, health, attackPower, protection, luck);
}

CellPoint Field::generateRandomFreePoint() {
    int x, y;
    do {
        x = rand() % this->getWidth();
        y = rand() % this->getHeight();
    } while (!this->field.isValidIndexes(x, y) ||
             field.getElem(CellPoint(x, y)).getValue().getTypeCell() != TypeCell::EMPTY ||
             field.getElem(CellPoint(x, y)).getValue().getTypeObject() != TypeObject::NOTHING
            );
    return {x, y};
}

MainHero& Field::getHero() {
    return this->hero;
}

void Field::moveEnemies() {
    for (const auto &enemy: enemies) {
        auto possibleSteps = enemy.second->makeMove(enemy.first, heroPos);
        std::shuffle(possibleSteps.begin(),  possibleSteps.end(), std::mt19937(std::random_device()()));
        for (int i = 0; i < possibleSteps.size(); ++i) {
            if (!field.isValidIndexes(possibleSteps[i].getX(), possibleSteps[i].getY()))
                continue;
            auto tempElem = getElem(possibleSteps[i]).getValue();
            if (tempElem.getTypeCell() != TypeCell::WALL &&
                tempElem.getTypeObject() != TypeObject::HERO &&
                tempElem.getTypeObject() != TypeObject::ENEMY
            ) {
                moveEnemy(enemy.first, possibleSteps[i]);
                break;
            }
        }
    }
}

void Field::moveEnemy(const CellPoint from, const CellPoint to) {
    auto enemy = enemies[from];
    enemies.erase(from);
    enemies[to] = enemy;
    auto prevPointData = field.getElem(from);
    auto newPointData = field.getElem(to);
    field.setElem(from, Cell(CellObject(prevPointData.getValue().getTypeCell(), TypeObject::NOTHING, prevPointData.getValue().isThing())));
    field.setElem(to, Cell(CellObject(newPointData.getValue().getTypeCell(), TypeObject::ENEMY, newPointData.getValue().isThing())));
}

void Field::createMonster(double health, double attackPower, double protection) {
    CellPoint monsterStartPoint;
    do {
        monsterStartPoint = generateRandomFreePoint();
    } while (Monster::inRangeVisibility(monsterStartPoint, heroPos) || enemies.count(monsterStartPoint));
    enemies[monsterStartPoint] = new Monster(health, attackPower, protection);
}

Field::~Field() {
    for (const auto &item: enemies) {
        delete item.second;
    }
}

void Field::incCountSteps() {
    counterSteps++;
}

long Field::getCountSteps() const {
    return counterSteps;
}

void Field::createRandomEnemy() {
    if (counterSteps % TIME_BETWEEN_GENERATE_ENEMY == 0 && enemies.size() < MAX_COUNT_ENEMIES) {
        switch (rand() % 3) {
            case 0:
                createMonster(MONSTER_MAX_HEALTH, 1, 2);
                break;
            case 1:
                createArcher(ARCHER_MAX_HEALTH, 2, 1);
                break;
            case 2:
                createGargoyle(GARGOYLE_MAX_HEALTH, 3, 2);
        }
    }
}

void Field::createArcher(double health, double attackPower, double protection) {
    CellPoint archerStartPoint;
    do {
        archerStartPoint = generateRandomFreePoint();
    } while (Archer::inRangeVisibility(archerStartPoint, heroPos) || enemies.count(archerStartPoint));
    enemies[archerStartPoint] = new Archer(health, attackPower, protection);
}

void Field::createGargoyle(double health, double attackPower, double protection) {
    CellPoint gargoyleStartPoint;
    do {
        gargoyleStartPoint = generateRandomFreePoint();
    } while (Gargoyle::inRangeVisibility(gargoyleStartPoint, heroPos) || enemies.count(gargoyleStartPoint));
    enemies[gargoyleStartPoint] = new Gargoyle(health, attackPower, protection);
}


