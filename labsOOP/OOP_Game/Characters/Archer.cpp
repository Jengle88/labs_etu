#include "Archer.h"

Archer::Archer(double health, double attackPower, double protection)
        : Character(CharacterType::SKELETON_ARCHER, health, attackPower, protection, ARCHER_LUCK) {}

bool Archer::isCriticalCase() const {
    return Character::isCriticalCase();
}

double Archer::calcReflectionArmor() const {
    return Character::calcReflectionArmor();
}

std::vector<double> Archer::requestAttack(Character &enemy) {
    std::vector<double> actionTable(3); // таблица событий при ударе
    bool wasCriticalAttack = isCriticalCase();
    double startEnemyHealth = enemy.getHealth();
    bool wasDodge;
    if (wasCriticalAttack)
        wasDodge = enemy.requestProtect(this->attackPower * ARCHER_CRITICAL_FACTOR);
    else
        wasDodge = enemy.requestProtect(this->attackPower);
    return {startEnemyHealth - enemy.getHealth(), double(wasDodge), double(wasCriticalAttack)};

}

bool Archer::requestProtect(double attackPower) {
    bool wasDodge = this->requestDodge();
    if (wasDodge)
        this->health -= attackPower * calcReflectionArmor() * ARCHER_DODGE_FACTOR;
    else
        this->health -= attackPower * calcReflectionArmor();
    return wasDodge;
}

bool Archer::requestDodge() const {
    return isCriticalCase();
}

std::vector<CellPoint> Archer::makeMove(CellPoint from, CellPoint heroPos) const { // Паттерн: Strategy
    std::vector<CellPoint> res;
    res.reserve(4);
    if (Archer::inRangeVisibility(from, heroPos) && willFollowToHero()) {
        int deltaX = -(from.getX() - heroPos.getX()) /
                     std::max(1, abs(from.getX() - heroPos.getX()));
        int deltaY = -(from.getY() - heroPos.getY()) /
                     std::max(1, abs(from.getY() - heroPos.getY()));
        res.emplace_back(from.getX() + deltaX, from.getY());
        res.emplace_back(from.getX(), from.getY() + deltaY);
        return res;
    }
    for (int i = -ARCHER_MOVE; i <= ARCHER_MOVE; ++i) {
        for (int j = -ARCHER_MOVE; j <= ARCHER_MOVE; ++j) {
            if (i == 0 ^ j == 0) {
                res.emplace_back(from.getX() + i,from.getY() + j);
            }
        }
    }
    return res;
}

bool Archer::willFollowToHero() const {
    if (rand() % 100 < ARCHER_PERCENT_FOR_FOLLOW_TO_HERO)
        return true;
    return false;
}

bool Archer::inRangeVisibility(CellPoint monsterPos, CellPoint objectPos) {
    return abs(monsterPos.getX() - objectPos.getX()) <= ARCHER_RANGE_VISIBILITY && //попадает в прямоугольник видимости
           abs(monsterPos.getY() - objectPos.getY()) <= ARCHER_RANGE_VISIBILITY;

}

int Archer::getCharacterType() const {
    return this->characterType;
}

bool Archer::checkPositiveHealth() const {
    return health > 0;
}

double Archer::getHealth() const {
    return Character::getHealth();
}

