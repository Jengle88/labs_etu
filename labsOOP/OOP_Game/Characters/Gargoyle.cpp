#include "Gargoyle.h"

Gargoyle::Gargoyle(double health, double attackPower, double protection) : Character(CharacterType::GARGOYLE, health, attackPower, protection, GARGOYLE_LUCK) {}

bool Gargoyle::requestProtect(double attackPower) {
    bool wasDodge = this->requestDodge();
    if (wasDodge)
        this->health -= attackPower * calcReflectionArmor() * GARGOYLE_DODGE_FACTOR;
    else
        this->health -= attackPower * calcReflectionArmor();
    return wasDodge;
}

bool Gargoyle::requestDodge() const {
    return isCriticalCase();
}

std::vector<double> Gargoyle::requestAttack(Character &enemy) {
    std::vector<double> actionTable(3); // таблица событий при ударе
    bool wasCriticalAttack = isCriticalCase();
    double startEnemyHealth = enemy.getHealth();
    bool wasDodge;
    if (wasCriticalAttack)
        wasDodge = enemy.requestProtect(this->attackPower * GARGOYLE_CRITICAL_FACTOR);
    else
        wasDodge = enemy.requestProtect(this->attackPower);
    return {startEnemyHealth - enemy.getHealth(), double(wasDodge), double(wasCriticalAttack)}; // был ли крит, было ли уклонение, уменьшение здоровья
}

bool Gargoyle::isCriticalCase() const {
    return Character::isCriticalCase();
}

double Gargoyle::calcReflectionArmor() const {
    return Character::calcReflectionArmor();
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

bool Gargoyle::willFollowToHero() const {
    if (rand() % 100 < GARGOYLE_PERCENT_FOR_FOLLOW_TO_HERO)
        return true;
    return false;
}

int Gargoyle::getCharacterType() const {
    return this->characterType;
}

bool Gargoyle::inRangeVisibility(CellPoint monsterPos, CellPoint objectPos) {
    return abs(monsterPos.getX() - objectPos.getX()) <= GARGOYLE_RANGE_VISIBILITY && //попадает в прямоугольник видимости
           abs(monsterPos.getY() - objectPos.getY()) <= GARGOYLE_RANGE_VISIBILITY;
}

bool Gargoyle::checkPositiveHealth() const {
    return health > 0;
}

double Gargoyle::getHealth() const {
    return Character::getHealth();
}

