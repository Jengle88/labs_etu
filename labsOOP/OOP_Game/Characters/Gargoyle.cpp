#include "Gargoyle.h"

Gargoyle::Gargoyle(double health, double attackPower, double protection)
            : Character(CharacterType::GARGOYLE, health, attackPower, protection, GARGOYLE_LUCK) {}

std::vector<double> Gargoyle::requestAttack(Character &enemy) {
    return Character::requestAttack(enemy, GARGOYLE_CRITICAL_FACTOR);
}

bool Gargoyle::requestProtect(double attackPower) {
    return Character::requestProtect(attackPower);
}

bool Gargoyle::requestDodge() const {
    return Character::requestDodge();
}

bool Gargoyle::isCriticalCase() const {
    return Character::isCriticalCase();
}

double Gargoyle::calcReflectionArmor() const {
    return Character::calcReflectionArmor();
}

bool Gargoyle::willFollowToHero() const {
    if (rand() % 100 < GARGOYLE_PERCENT_FOR_FOLLOW_TO_HERO)
        return true;
    return false;
}

std::vector<CellPoint> Gargoyle::makeMove(CellPoint from, CellPoint heroPos) const { // Паттерн: Strategy
    std::vector<CellPoint> res;
    res.reserve(8);
    if (Gargoyle::inRangeVisibility(from, heroPos) && willFollowToHero()) {
        int deltaX = -(from.getX() - heroPos.getX()) /
                     std::max(1, abs(from.getX() - heroPos.getX()));
        int deltaY = -(from.getY() - heroPos.getY()) /
                     std::max(1, abs(from.getY() - heroPos.getY()));
        res.emplace_back(from.getX() + deltaX, from.getY());
        res.emplace_back(from.getX(), from.getY() + deltaY);
        res.emplace_back(from.getX() + deltaX, from.getY() + deltaY);
        return res;
    }
    for (int i = -GARGOYLE_MOVE; i <= GARGOYLE_MOVE; ++i) {
        for (int j = -GARGOYLE_MOVE; j <= GARGOYLE_MOVE; ++j) {
            if (i != 0 && j != 0) {
                res.emplace_back(from.getX() + i,from.getY() + j);
            }
        }
    }
    return res;
}

bool Gargoyle::inRangeVisibility(CellPoint monsterPos, CellPoint objectPos) {
    return abs(monsterPos.getX() - objectPos.getX()) <= GARGOYLE_RANGE_VISIBILITY && //попадает в прямоугольник видимости
           abs(monsterPos.getY() - objectPos.getY()) <= GARGOYLE_RANGE_VISIBILITY;
}

int Gargoyle::getCharacterType() const {
    return this->characterType;
}

double Gargoyle::getHealth() const {
    return Character::getHealth();
}

double Gargoyle::getDodgeFactor() const {
    return GARGOYLE_DODGE_FACTOR;
}

bool Gargoyle::checkPositiveHealth() const {
    return health > 0;
}

