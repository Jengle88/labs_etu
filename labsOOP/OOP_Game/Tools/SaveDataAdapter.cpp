#include "SaveDataAdapter.h"

int SaveDataAdapter::getHeightField() const {
    return heightField;
}

int SaveDataAdapter::getWidthField() const {
    return widthField;
}

const CellPoint &SaveDataAdapter::getStart() const {
    return start;
}

const CellPoint &SaveDataAdapter::getFinish() const {
    return finish;
}

const std::vector<CellPoint> &SaveDataAdapter::getWalls() const {
    return walls;
}

const CellPoint &SaveDataAdapter::getHeroPos() const {
    return heroPos;
}

double SaveDataAdapter::getHeroHealth() const {
    return heroHealth;
}

const std::vector<std::pair<std::string, std::pair<double, CellPoint>>> &SaveDataAdapter::getEnemiesPos() const {
    return enemiesPos;
}

int SaveDataAdapter::getCntSteps() const {
    return cntSteps;
}

const std::vector<std::pair<std::string, std::pair<int, CellPoint>>> &SaveDataAdapter::getThingsPos() const {
    return thingsPos;
}

int SaveDataAdapter::getHeroLevel() const {
    return heroLevel;
}

const std::vector<std::pair<std::string, int>> &SaveDataAdapter::getHeroThings() const {
    return heroThings;
}

const std::vector<std::pair<std::string, int>> &SaveDataAdapter::getHeroAchievements() const {
    return heroAchievements;
}

void SaveDataAdapter::setHeightField(int heightField) {
    SaveDataAdapter::heightField = heightField;
}

void SaveDataAdapter::setWidthField(int widthField) {
    SaveDataAdapter::widthField = widthField;
}

void SaveDataAdapter::setStart(const CellPoint &start) {
    SaveDataAdapter::start = start;
}

void SaveDataAdapter::setFinish(const CellPoint &finish) {
    SaveDataAdapter::finish = finish;
}

void SaveDataAdapter::setWalls(const std::vector<CellPoint> &walls) {
    SaveDataAdapter::walls = walls;
}

void SaveDataAdapter::setHeroPos(const CellPoint &heroPos) {
    SaveDataAdapter::heroPos = heroPos;
}

void SaveDataAdapter::setHeroHealth(double heroHealth) {
    SaveDataAdapter::heroHealth = heroHealth;
}

void
SaveDataAdapter::setEnemiesPos(const std::vector<std::pair<std::string, std::pair<double, CellPoint>>> &enemiesPos) {
    SaveDataAdapter::enemiesPos = enemiesPos;
}

void SaveDataAdapter::setCntSteps(int cntSteps) {
    SaveDataAdapter::cntSteps = cntSteps;
}

void SaveDataAdapter::setThingsPos(const std::vector<std::pair<std::string, std::pair<int, CellPoint>>> &thingsPos) {
    SaveDataAdapter::thingsPos = thingsPos;
}

void SaveDataAdapter::setHeroLevel(int levelOfThings) {
    SaveDataAdapter::heroLevel = levelOfThings;
}

void SaveDataAdapter::setHeroThings(const std::vector<std::pair<std::string, int>> &heroThings) {
    SaveDataAdapter::heroThings = heroThings;
}

void SaveDataAdapter::setHeroAchievements(const std::vector<std::pair<std::string, int>> &heroAchievements) {
    SaveDataAdapter::heroAchievements = heroAchievements;
}
