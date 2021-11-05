#include "Field.h"
#include "../../Tools/Logger.hpp"

Field::Field(int height, int width, DataManager *dataManager, CellPoint start, CellPoint finish, Grid grid) {
    if (!grid.grid.empty())
        this->field = grid;
    else
        this->field = Grid(height, width);
    this->start = start;
    this->finish = finish;
    this->dataManager = dataManager;
    if (isCorrectStartFinish(start, finish)) {
        chosenStartFinish = true;
    }
}

Field::Field(const Field &field) {
    this->field = field.field;
    start = field.start;
    finish = field.finish;
    heroPos = field.heroPos;
    hero = field.hero;
    dataManager = field.dataManager;
    enemies = field.enemies;
    wayGenerated = field.wayGenerated;
    wallsGenerated = field.wallsGenerated;
    chosenStartFinish = field.chosenStartFinish;
    countWalls = field.countWalls;
    distStartFinish = field.distStartFinish;
    counterSteps = field.counterSteps;
}

Field &Field::operator=(const Field &field) {
    if (&field == this)
        return *this;
    this->field = field.field;
    start = field.start;
    finish = field.finish;
    heroPos = field.heroPos;
    hero = field.hero;
    dataManager = field.dataManager;
    enemies = field.enemies;
    wayGenerated = field.wayGenerated;
    wallsGenerated = field.wallsGenerated;
    chosenStartFinish = field.chosenStartFinish;
    countWalls = field.countWalls;
    distStartFinish = field.distStartFinish;
    counterSteps = field.counterSteps;
    return *this;
}

Field::Field(Field &&field) {
    this->field = std::move(field.field);
    start = field.start;
    finish = field.finish;
    heroPos = field.heroPos;
    hero = std::move(field.hero);
    dataManager = field.dataManager;
    enemies = std::move(field.enemies);
    wayGenerated = field.wayGenerated;
    wallsGenerated = field.wallsGenerated;
    chosenStartFinish = field.chosenStartFinish;
    countWalls = field.countWalls;
    distStartFinish = field.distStartFinish;
    counterSteps = field.counterSteps;
    field.start = CellPoint();
    field.finish = CellPoint();
    field.heroPos = CellPoint();
    field.hero = MainHero();
    field.enemies.clear();
    field.wayGenerated = false;
    field.wallsGenerated = false;
    field.chosenStartFinish = false;
    field.countWalls = 0;
    distStartFinish = 0;
    counterSteps = 0;
}

Field &Field::operator=(Field &&field) {
    if (&field == this)
        return *this;
    this->field = std::move(field.field);
    start = field.start;
    finish = field.finish;
    heroPos = field.heroPos;
    hero = std::move(field.hero);
    dataManager = field.dataManager;
    enemies = std::move(field.enemies);
    wayGenerated = field.wayGenerated;
    wallsGenerated = field.wallsGenerated;
    chosenStartFinish = field.chosenStartFinish;
    countWalls = field.countWalls;
    distStartFinish = field.distStartFinish;
    counterSteps = field.counterSteps;
    field.start = CellPoint();
    field.finish = CellPoint();
    field.heroPos = CellPoint();
    field.hero = MainHero();
    field.enemies.clear();
    field.wayGenerated = false;
    field.wallsGenerated = false;
    field.chosenStartFinish = false;
    field.countWalls = 0;
    distStartFinish = 0;
    counterSteps = 0;
    return *this;
}

Field::~Field() {
    for (auto &item: enemies) {
        delete item.second;
    }
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
    Logger::writeMessageToFile("gameLogs", "Были переданы стандартные сгенерированные точки", Logger::LoggingType::Warning);
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
    Logger::writeDataToFile("gameLogs", this->start, Logger::LoggingType::Info, "Точка старта");
    Logger::writeDataToFile("gameLogs", this->finish, Logger::LoggingType::Info, "Точка финиша");
    generateWayWithoutWalls(this->start, this->finish);
    Logger::writeMessageToFile("gameLogs","Путь между стартом и финишем был сгенерирован");
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

void Field::generateWalls(int countWalls) {
    if (!wayGenerated) {
        Logger::writeMessageToFile("gameLogs", "Попытка создать непроходимые клетки при не сгенерированном пути", Logger::LoggingType::Error);
        throw -1; // путь не сгенерирован
    }
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
    Logger::writeMessageToFile("gameLogs", "Непроходимые клетки были сгенерированы");
    this->countWalls = countWalls;
    wallsGenerated = true;
}

bool Field::generateFullField(int countWalls) {
    this->generateStartFinishWay();
    this->generateWalls(countWalls);
    return this->getStatusStartFinish() && this->getStatusWay() && this->getStatusWalls();
}

void Field::createHero() {
    hero = MainHero(dataManager->getHero());
    Logger::writeDataToFile("gameLogs", hero, Logger::LoggingType::Info, "Главный герой загружен");
}

void Field::createMonster() {
    CellPoint monsterStartPoint;
    do {
        monsterStartPoint = generateRandomFreePoint();
    } while (enemies.count(monsterStartPoint));
    enemies[monsterStartPoint] = new Monster(dataManager->getModelCharacter("Monster"));
    Logger::writeDataToFile("gameLogs", monsterStartPoint, Logger::LoggingType::Info, "Сгенерирован монстр");
}

void Field::createArcher() {
    CellPoint archerStartPoint;
    do {
        archerStartPoint = generateRandomFreePoint();
    } while (enemies.count(archerStartPoint));
    enemies[archerStartPoint] = new Archer(dataManager->getModelCharacter("Archer"));
    Logger::writeDataToFile("gameLogs", archerStartPoint, Logger::LoggingType::Info, "Сгенерирован скелет-лучник");
}

void Field::createGargoyle() {
    CellPoint gargoyleStartPoint;
    do {
        gargoyleStartPoint = generateRandomFreePoint();
    } while (enemies.count(gargoyleStartPoint));
    enemies[gargoyleStartPoint] = new Gargoyle(dataManager->getModelCharacter("Gargoyle"));
    Logger::writeDataToFile("gameLogs", gargoyleStartPoint, Logger::LoggingType::Info, "Сгенерирована гаргулья");
}

void Field::createRandomEnemy() {
    if (counterSteps % TIME_BETWEEN_GENERATE_ENEMY == 0 && enemies.size() < MAX_COUNT_ENEMIES) {
        switch (rand() % 3) {
            case 0:
                createMonster();
                break;
            case 1:
                createArcher();
                break;
            case 2:
                createGargoyle();
                break;
        }
    }
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

void Field::moveHero(CellPoint to) {
    auto cellInfo = getElem(to).getValue();
    if (cellInfo.getTypeCell() != TypeCell::WALL && cellInfo.getTypeObject() != TypeObject::ENEMY) {
        setElem(heroPos, CellObject(getElem(heroPos).getValue().getTypeCell(), TypeObject::NOTHING,
                                    getElem(heroPos).getValue().isThing()));
        setElem(to,
                CellObject(getElem(to).getValue().getTypeCell(), TypeObject::HERO, getElem(to).getValue().isThing()));
        heroPos = to;
    }
}

void Field::moveEnemy(const CellPoint from, const CellPoint to) {
    auto enemy = enemies[from];
    enemies.erase(from);
    enemies[to] = enemy;
    auto prevPointData = field.getElem(from);
    auto newPointData = field.getElem(to);
    field.setElem(from, Cell(CellObject(prevPointData.getValue().getTypeCell(),
                                        prevPointData.getValue().getTypeObject() == TypeObject::HERO ? TypeObject::HERO : TypeObject::NOTHING,
                                        prevPointData.getValue().isThing())));
    field.setElem(to, Cell(CellObject(newPointData.getValue().getTypeCell(), TypeObject::ENEMY, newPointData.getValue().isThing())));
}

void Field::moveEnemies() {
    auto tempEnemies = enemies;
    for (const auto &enemy: tempEnemies) {
        auto possibleSteps = enemy.second->makeMove(enemy.first, heroPos);
        std::shuffle(possibleSteps.begin(),  possibleSteps.end(), std::mt19937(std::random_device()()));
        for (auto & possibleStep : possibleSteps) {
            if (!field.isValidIndexes(possibleStep.getX(), possibleStep.getY()))
                continue;
            auto tempElem = getElem(possibleStep).getValue();
            if (tempElem.getTypeCell() != TypeCell::WALL &&
                tempElem.getTypeObject() != TypeObject::HERO &&
                tempElem.getTypeObject() != TypeObject::ENEMY
                    ) {
                moveEnemy(enemy.first, possibleStep);
                break;
            }
        }
    }
}

void Field::killEnemy(CellPoint from) {
    delete enemies[from];
    enemies.erase(from);
    setElem(from, CellObject(getElem(from).getValue().getTypeCell(), TypeObject::NOTHING, getElem(from).getValue().isThing()));
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
    Logger::writeMessageToFile("gameLogs", "Главный герой установлен на позицию старта");
}

MainHero& Field::getHero() {
    return this->hero;
}

Enemy& Field::getEnemyFromPoint(CellPoint point) {
    return static_cast<Enemy &>(*enemies[point]);
}

void Field::incCountSteps() {
    counterSteps++;
}

long Field::getCountSteps() const {
    return counterSteps;
}


