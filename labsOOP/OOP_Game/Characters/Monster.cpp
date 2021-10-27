#include "Monster.h"

Monster::Monster(std::vector<std::string> model, std::string name, double health, double attackPower, double protection, double luck)
        : Character(model, name, health, attackPower, protection, luck) {}

std::vector<double> Monster::requestAttack(Character &enemy) {
    return Character::requestAttack(enemy, MonsterProperties::MONSTER_CRITICAL_FACTOR);
}

bool Monster::requestProtect(double attackPower) {
    return Character::requestProtect(attackPower);
}

bool Monster::requestDodge() const {
    return Character::requestDodge();
}

bool Monster::isCriticalCase() const {
    return Character::isCriticalCase();
}

double Monster::calcReflectionArmor() const {
    return Character::calcReflectionArmor();
}

bool Monster::willFollowToHero() const {
    if (rand() % 100 < MonsterProperties::MONSTER_PERCENT_FOR_FOLLOW_TO_HERO)
        return true;
    return false;
}

std::vector<CellPoint> Monster::makeMove(CellPoint from, CellPoint heroPos) const { // Паттерн: Strategy
    std::vector<CellPoint> res;
    res.reserve(4);
    if (Monster::inRangeVisibility(from, heroPos) && willFollowToHero()) {
        int deltaX = -(from.getX() - heroPos.getX()) /
                     std::max(1, abs(from.getX() - heroPos.getX()));
        int deltaY = -(from.getY() - heroPos.getY()) /
                     std::max(1, abs(from.getY() - heroPos.getY()));
        res.emplace_back(from.getX() + deltaX, from.getY());
        res.emplace_back(from.getX(), from.getY() + deltaY);
        return res;
    }
    for (int i = -MonsterProperties::MONSTER_MOVE; i <= MonsterProperties::MONSTER_MOVE; ++i) {
        for (int j = -MonsterProperties::MONSTER_MOVE; j <= MonsterProperties::MONSTER_MOVE; ++j) {
            if (i == 0 ^ j == 0) {
                res.emplace_back(from.getX() + i,from.getY() + j);
            }
        }
    }
    return res;
}

bool Monster::inRangeVisibility(CellPoint monsterPos, CellPoint objectPos) {
    return abs(monsterPos.getX() - objectPos.getX()) <= MonsterProperties::MONSTER_RANGE_VISIBILITY && //попадает в прямоугольник видимости
           abs(monsterPos.getY() - objectPos.getY()) <= MonsterProperties::MONSTER_RANGE_VISIBILITY;
}

double Monster::getHealth() const {
    return Character::getHealth();
}

double Monster::getDodgeFactor() const {
    return MonsterProperties::MONSTER_DODGE_FACTOR;
}

Monster *Monster::clone() const {
    return new Monster(model, name, health, attackPower, protection);
}

bool Monster::checkPositiveHealth() const {
    return health > 0;
}

std::vector<std::string> Monster::getModel() const {
    return Character::getModel();
}

std::string Monster::getName() const {
    return Character::getName();
}

