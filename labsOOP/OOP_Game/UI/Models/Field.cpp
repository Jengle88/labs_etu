#include "Field.h"
#include "../../Logger/LoggerPull.h"
#include "../../Tools/SaveDataReader.h"
#include "../../Rules/DifficultDataReader.h"


Field::Field(int height, int width, std::shared_ptr<DataManager> dataManager, FieldBuilder *builder, CellPoint start,
             CellPoint finish, Grid grid) {
    this->builder = builder;
    if (!grid.grid.empty())
        this->grid = grid;
    else
        this->grid = Grid(height, width);
    this->start = start;
    this->finish = finish;
    this->dataManager = dataManager;
    if (builder->isCorrectStartFinish(start, finish, grid)) {
        builder->chosenStartFinish = true;
    }
}

Field::Field(std::shared_ptr<DataManager> dataManager, FieldBuilder *builder) : dataManager(dataManager), builder(builder) {}

Field::Field(const Field &field) {
    this->grid = field.grid;
    start = field.start;
    finish = field.finish;
    heroPos = field.heroPos;
    hero = field.hero;
    dataManager = field.dataManager;
    enemies = field.enemies;
    counterSteps = field.counterSteps;
}

Field &Field::operator=(const Field &field) {
    if (&field == this)
        return *this;
    this->grid = field.grid;
    start = field.start;
    finish = field.finish;
    heroPos = field.heroPos;
    hero = field.hero;
    dataManager = field.dataManager;
    enemies = field.enemies;
    counterSteps = field.counterSteps;
    return *this;
}

Field::Field(Field &&field) {
    this->grid = std::move(field.grid);
    start = field.start;
    finish = field.finish;
    heroPos = field.heroPos;
    hero = std::move(field.hero);
    dataManager = field.dataManager;
    enemies = std::move(field.enemies);
    counterSteps = field.counterSteps;
    field.start = CellPoint();
    field.finish = CellPoint();
    field.heroPos = CellPoint();
    field.hero = MainHero();
    field.enemies.clear();
    counterSteps = 0;
}

Field &Field::operator=(Field &&field) {
    if (&field == this)
        return *this;
    this->grid = std::move(field.grid);
    start = field.start;
    finish = field.finish;
    heroPos = field.heroPos;
    hero = std::move(field.hero);
    dataManager = field.dataManager;
    enemies = std::move(field.enemies);
    counterSteps = field.counterSteps;
    field.start = CellPoint();
    field.finish = CellPoint();
    field.heroPos = CellPoint();
    field.hero = MainHero();
    field.enemies.clear();
    counterSteps = 0;
    return *this;
}

Field::~Field() {
    for (auto &item: enemies) {
        delete item.second;
    }
}



std::vector<std::string>
Field::prepareDataToSave(bool sizeOfField, bool startFinishPos, bool posOfWalls, bool posOfCharacters, bool cntSteps,
                         bool heroInfo) const {
    std::vector<std::string> data;
    if (sizeOfField) {
        data.emplace_back("// размеры поля\n");
        data.push_back("height " + std::to_string(grid.getHeight()) + "\n");
        data.push_back("width " + std::to_string(grid.getWidth()) + "\n");
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
        auto pointsOfWalls = grid.getPointsOfWalls();
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


bool Field::generateFullField(int countWalls) {
    builder->generateStartFinishWay(getHeight(), getWidth(), start, finish, grid);
    builder->generateWalls(countWalls, grid, grid.pointsOfWalls);
    return builder->isChosenStartFinish() && builder->isWayGenerated() && builder->isWallsGenerated();
}

void Field::rebuildField(const SaveDataAdapter &adapter) {
    if (!enemies.empty()) {
        for (auto &item: enemies) {
            delete item.second;
        }
        enemies.clear();
    }

    grid.rebuildGrid(adapter);
    counterSteps = adapter.getCntSteps();
    builder->wallsGenerated = true;

    start = adapter.getStart();
    grid.setElem(start, Cell(CellObject(TypeCell::START, TypeObject::NOTHING, false)));
    finish = adapter.getFinish();
    grid.setElem(finish, Cell(CellObject(TypeCell::FINISH, TypeObject::NOTHING, false)));
    builder->chosenStartFinish = true;
    builder->wayGenerated = true;

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
    grid.setElem(heroPos, Cell(CellObject(TypeCell::EMPTY, TypeObject::HERO, false)));

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

void Field::createHero() {
    hero = MainHero(dataManager->getHero());
    LoggerPull::writeData("gameLogs", LoggerDataAdapter<MainHero>(hero, "Главный герой загружен"));
}

void Field::createMonster(CellPoint monsterStartPoint) {
    enemies[monsterStartPoint] = new Monster(dataManager->getModelCharacter("Monster"));
    grid.setElem(monsterStartPoint,
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
    grid.setElem(archerStartPoint,
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
    grid.setElem(gargoyleStartPoint,
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
    } while (!this->grid.isValidIndexes(x, y) ||
             grid.getElem(CellPoint(x, y)).getValue().getTypeCell() != TypeCell::EMPTY ||
             grid.getElem(CellPoint(x, y)).getValue().getTypeObject() != TypeObject::NOTHING
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
    auto prevPointData = grid.getElem(from);
    auto newPointData = grid.getElem(to);
    grid.setElem(from, Cell(CellObject(prevPointData.getValue().getTypeCell(),
                                        prevPointData.getValue().getTypeObject() == TypeObject::HERO ? TypeObject::HERO
                                                                                                     : TypeObject::NOTHING,
                                       prevPointData.getValue().isThing())));
    grid.setElem(to, Cell(CellObject(newPointData.getValue().getTypeCell(), TypeObject::ENEMY,
                                     newPointData.getValue().isThing())));
}

void Field::moveEnemies() {
    auto tempEnemies = enemies;
    for (const auto &enemy: tempEnemies) {
        auto possibleSteps = enemy.second->makeMove(enemy.first, heroPos);
        std::shuffle(possibleSteps.begin(), possibleSteps.end(), std::mt19937(std::random_device()()));
        for (auto &possibleStep: possibleSteps) {
            if (!grid.isValidIndexes(possibleStep.getX(), possibleStep.getY()))
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
    return grid.getElem(point);
}

void Field::setElem(CellPoint point, CellObject object) {
    grid.setElem(point, Cell(object));
}

int Field::getHeight() const {
    return grid.height;
}

int Field::getWidth() const {
    return grid.width;
}


FieldIterator Field::getFieldIterator() {
    return FieldIterator(&(this->grid));
}

CellPoint Field::getHeroPos() const {
    return heroPos;
}

void Field::setHeroOnStart() {
    grid.setElem(start, Cell(CellObject(TypeCell::START, TypeObject::HERO, false)));
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
    return grid;
}

void Field::setRules(int maxCntEnemy, int timeBetweenGenerateEnemy) {
    this->maxCntEnemy = maxCntEnemy;
    this->timeBetweenGenerateEnemy = timeBetweenGenerateEnemy;

}

const std::shared_ptr<DataManager> & Field::getDataManager() const {
    return dataManager;
}



