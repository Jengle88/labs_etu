#include "Archer.h"

Archer::Archer(double health, double attackPower, double protection)
        : Character(CharacterType::SKELETON_ARCHER, health, attackPower, protection, ARCHER_LUCK) {}

std::vector<double> Archer::requestAttack(Character &enemy) {
    return Character::requestAttack(enemy, ARCHER_CRITICAL_FACTOR, ARCHER_DODGE_FACTOR);
}

bool Archer::requestProtect(double attackPower) {
    return Character::requestProtect(attackPower, ARCHER_DODGE_FACTOR);
}

bool Archer::requestDodge() const {
    return Character::requestDodge();
}

bool Archer::isCriticalCase() const {
    return Character::isCriticalCase();
}

double Archer::calcReflectionArmor() const {
    return Character::calcReflectionArmor();
}

bool Archer::willFollowToHero() const {
    if (rand() % 100 < ARCHER_PERCENT_FOR_FOLLOW_TO_HERO)
        return true;
    return false;
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

bool Archer::inRangeVisibility(CellPoint monsterPos, CellPoint objectPos) {
    return abs(monsterPos.getX() - objectPos.getX()) <= ARCHER_RANGE_VISIBILITY && //попадает в прямоугольник видимости
           abs(monsterPos.getY() - objectPos.getY()) <= ARCHER_RANGE_VISIBILITY;

}

int Archer::getCharacterType() const {
    return this->characterType;
}

double Archer::getHealth() const {
    return Character::getHealth();
}

bool Archer::checkPositiveHealth() const {
    return health > 0;
}

