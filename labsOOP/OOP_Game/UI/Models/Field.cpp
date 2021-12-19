#include "Field.h"
#include "../../Logger/LoggerPull.h"
#include "../../Tools/SaveDataReader.h"
#include "../../Rules/DifficultDataReader.h"
;

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

Field::Field(DataManager* dataManager) : dataManager(dataManager) {}

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

std::vector<std::string>
Field::prepareDataToSave(bool sizeOfField, bool startFinishPos, bool posOfWalls, bool posOfCharacters, bool cntSteps,
                         bool heroInfo) const {
    std::vector<std::string> data;
    if (sizeOfField) {
        data.emplace_back("// размеры поля\n");
        data.push_back("height " + std::to_string(field.getHeight()) + "\n");
        data.push_back("width " + std::to_string(field.getWidth()) + "\n");
    }
    if (startFinishPos) {
        data.emplace_back("// позиции старта/финиша xy\n");
        data.push_back("start " + std::to_string(start.getX()) + " " + std::to_string(start.getY()) + "\n");
        data.push_back("finish " + std::to_string(finish.getX()) + " " + std::to_string(finish.getY()) + "\n");
    }
    if (posOfWalls) {
        data.emplace_back("// позиции непроходимых клеток xy\n");
        data.emplace_back("wallsPos\n");
        data.push_back(SaveDataReader::START_TAG + "\n");
        auto pointsOfWalls = field.getPointsOfWalls();
        for (const auto &point: pointsOfWalls) {
            data.push_back(std::to_string(point.getX()) + " " + std::to_string(point.getY()) + "\n");
        }
        data.push_back(SaveDataReader::END_TAG + "\n");
    }
    if (posOfCharacters) {
        data.emplace_back("// позиция героя (здоровье, позиция xy)\n");
        data.push_back(hero.getName() + " " + std::to_string(hero.getHealth()) +
                       " " + std::to_string(heroPos.getX()) + " " + std::to_string(heroPos.getY()) + "\n");
        data.emplace_back("// позиции врагов (здоровье, позиция xy)\n");
        data.emplace_back("enemiesPosHealth\n");
        data.push_back(SaveDataReader::START_TAG + "\n");
        for (const auto &enemy: enemies) {
            data.push_back(enemy.second->getName() + " " + std::to_string(enemy.second->getHealth()) +
                           " " + std::to_string(enemy.first.getX()) + " " + std::to_string(enemy.first.getY()) + "\n");
        }
        data.push_back(SaveDataReader::END_TAG + "\n");
    }
    if (cntSteps) {
        data.emplace_back("// количество шагов\n");
        data.push_back("cntSteps " + std::to_string(counterSteps) + "\n");
    }
    if (heroInfo) {
        data.emplace_back("// вещи игрока (уровень)\n");
        data.emplace_back("heroThings\n");
        data.push_back(SaveDataReader::START_TAG + "\n");
        auto heroInventory = hero.getInventory();
        for (const auto &thing: heroInventory) {
            data.push_back(thing->getStrType() + " " + std::to_string(thing->getLevelThing()) + "\n");
        }
        data.push_back(SaveDataReader::END_TAG + "\n");
        data.emplace_back("// достижения игрока (количество)\n");
        data.emplace_back("heroAchievement\n");
        data.push_back(SaveDataReader::START_TAG + "\n");
        auto heroAchievements = hero.getCountKilledEnemy();
        for (const auto &achievement: heroAchievements) {
            data.push_back(achievement.first + " " + std::to_string(achievement.second) + "\n");
        }
        data.push_back(SaveDataReader::END_TAG + "\n");
    }

    return data;
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
    LoggerPull::writeData("gameLogs",
                          LoggerDataAdapter<std::string>("Были переданы стандартные сгенерированные точки"),
                          LoggerPull::LoggingType::Warning);
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

    LoggerPull::writeData("gameLogs", LoggerDataAdapter<CellPoint>(this->start, "Точка старта"));
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<CellPoint>(this->finish, "Точка финиша"));

    generateWayWithoutWalls(this->start, this->finish);
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Путь между стартом и финишем был сгенерирован"));
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
        LoggerPull::writeData("gameLogs",
                              LoggerDataAdapter<std::string>(
                                      "Попытка создать непроходимые клетки при не сгенерированном пути"),
                              LoggerPull::LoggingType::Error);
        throw std::logic_error(
                "Попытка создать непроходимые клетки при не сгенерированном пути"); // путь не сгенерирован
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
            field.pointsOfWalls.push_back(point);
            cntPlacedWalls++;
        }
    }
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Непроходимые клетки были сгенерированы"));
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
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<MainHero>(hero, "Главный герой загружен"));
}

void Field::createMonster(CellPoint monsterStartPoint) {
    enemies[monsterStartPoint] = new Monster(dataManager->getModelCharacter("Monster"));
    field.setElem(monsterStartPoint,
                  Cell(CellObject(getElem(monsterStartPoint).getValue().getTypeCell(), TypeObject::ENEMY,
                                  getElem(monsterStartPoint).getValue().isThing())));
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<CellPoint>(monsterStartPoint, "Сгенерирован монстр"));
}

void Field::createMonster() {
    CellPoint monsterStartPoint;
    do {
        monsterStartPoint = generateRandomFreePoint();
    } while (enemies.count(monsterStartPoint));
    createMonster(monsterStartPoint);
}

void Field::createArcher(CellPoint archerStartPoint) {
    enemies[archerStartPoint] = new Archer(dataManager->getModelCharacter("Archer"));
    field.setElem(archerStartPoint,
                  Cell(CellObject(getElem(archerStartPoint).getValue().getTypeCell(), TypeObject::ENEMY,
                                  getElem(archerStartPoint).getValue().isThing())));
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<CellPoint>(archerStartPoint, "Сгенерирован скелет-лучник"));

}

void Field::createArcher() {
    CellPoint archerStartPoint;
    do {
        archerStartPoint = generateRandomFreePoint();
    } while (enemies.count(archerStartPoint));
    createArcher(archerStartPoint);
}

void Field::createGargoyle(CellPoint gargoyleStartPoint) {
    enemies[gargoyleStartPoint] = new Gargoyle(dataManager->getModelCharacter("Gargoyle"));
    field.setElem(gargoyleStartPoint,
                  Cell(CellObject(getElem(gargoyleStartPoint).getValue().getTypeCell(), TypeObject::ENEMY,
                                  getElem(gargoyleStartPoint).getValue().isThing())));
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<CellPoint>(gargoyleStartPoint, "Сгенерирована горгулья"));
}

void Field::createGargoyle() {
    CellPoint gargoyleStartPoint;
    do {
        gargoyleStartPoint = generateRandomFreePoint();
    } while (enemies.count(gargoyleStartPoint));
    createGargoyle(gargoyleStartPoint);
}

void Field::createRandomEnemy() {
    if (counterSteps % timeBetweenGenerateEnemy == 0 && enemies.size() + 1 <= maxCntEnemy) {
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

bool Field::moveHero(CellPoint to) {
    auto cellInfo = getElem(to).getValue();
    if (cellInfo.getTypeCell() != TypeCell::WALL && cellInfo.getTypeObject() != TypeObject::ENEMY) {
        setElem(heroPos, CellObject(getElem(heroPos).getValue().getTypeCell(), TypeObject::NOTHING,
                                    getElem(heroPos).getValue().isThing()));
        setElem(to,
                CellObject(getElem(to).getValue().getTypeCell(), TypeObject::HERO, getElem(to).getValue().isThing()));
        heroPos = to;
        return true;
    } else
        return false;
}

void Field::moveEnemy(const CellPoint from, const CellPoint to) {
    auto enemy = enemies[from];
    enemies.erase(from);
    enemies[to] = enemy;
    auto prevPointData = field.getElem(from);
    auto newPointData = field.getElem(to);
    field.setElem(from, Cell(CellObject(prevPointData.getValue().getTypeCell(),
                                        prevPointData.getValue().getTypeObject() == TypeObject::HERO ? TypeObject::HERO
                                                                                                     : TypeObject::NOTHING,
                                        prevPointData.getValue().isThing())));
    field.setElem(to, Cell(CellObject(newPointData.getValue().getTypeCell(), TypeObject::ENEMY,
                                      newPointData.getValue().isThing())));
}

void Field::moveEnemies() {
    auto tempEnemies = enemies;
    for (const auto &enemy: tempEnemies) {
        auto possibleSteps = enemy.second->makeMove(enemy.first, heroPos);
        std::shuffle(possibleSteps.begin(), possibleSteps.end(), std::mt19937(std::random_device()()));
        for (auto &possibleStep: possibleSteps) {
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
    setElem(from, CellObject(getElem(from).getValue().getTypeCell(), TypeObject::NOTHING,
                             getElem(from).getValue().isThing()));
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
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<std::string>("Главный герой установлен на позицию старта"));
}

MainHero &Field::getHero() {
    return this->hero;
}

Enemy &Field::getEnemyFromPoint(CellPoint point) {
    return static_cast<Enemy &>(*enemies[point]);
}


void Field::incCountSteps() {
    counterSteps++;
}

long Field::getCountSteps() const {
    return counterSteps;
}

std::map<CellPoint, Enemy *> &Field::getEnemies() {
    return enemies;
}

const Grid &Field::getGrid() const {
    return field;
}

void Field::setRules(int maxCntEnemy, int timeBetweenGenerateEnemy) {
    this->maxCntEnemy = maxCntEnemy;
    this->timeBetweenGenerateEnemy = timeBetweenGenerateEnemy;

}

void Field::rebuildField(const SaveDataAdapter &adapter) {
    if (!enemies.empty()) {
        for (auto &item: enemies) {
            delete item.second;
        }
        enemies.clear();
    }

    field.rebuildGrid(adapter);
    countWalls = adapter.getWalls().size();
    counterSteps = adapter.getCntSteps();
    wallsGenerated = true;

    start = adapter.getStart();
    field.setElem(start, Cell(CellObject(TypeCell::START, TypeObject::NOTHING, false)));
    finish = adapter.getFinish();
    field.setElem(finish, Cell(CellObject(TypeCell::FINISH, TypeObject::NOTHING, false)));
    chosenStartFinish = true;
    wayGenerated = true;

    heroPos = adapter.getHeroPos();
    moveHero(adapter.getHeroPos());
    hero.setHealth(adapter.getHeroHealth());
    std::vector<Thing *> heroThings;
    heroThings.reserve(adapter.getHeroThings().size());
    for (const auto &thing: adapter.getHeroThings()) {
        heroThings.push_back(dataManager->getThing(thing.second, DifficultDataReader::getTypeObjectFromStr(thing.first)));
    }
    hero.setInventory(heroThings);
    hero.resetModel(dataManager->getHero(
            hero.hasThing(ThingObject::SWORD),
            hero.hasThing(ThingObject::ARMOR)));
    field.setElem(heroPos, Cell(CellObject(TypeCell::EMPTY, TypeObject::HERO, false)));

    for (const auto &enemiesPos: adapter.getEnemiesPos()) {
        if (enemiesPos.first == "Monster") {
            createMonster(enemiesPos.second.second);
        } else if (enemiesPos.first == "Archer") {
            createArcher(enemiesPos.second.second);
        } else if (enemiesPos.first == "Gargoyle") {
            createGargoyle(enemiesPos.second.second);
        }
        enemies[enemiesPos.second.second]->setHealth(enemiesPos.second.first);
    }
}

const DataManager *Field::getDataManager() const {
    return dataManager;
}



