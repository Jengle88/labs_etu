#include "Gargoyle.h"

Gargoyle::Gargoyle(std::vector<std::string> model, std::string name, double health, double attackPower, double protection, double luck)
            : Character(model, name, health, attackPower, protection, luck) {}

std::vector<double> Gargoyle::requestAttack(Character &enemy) {
    return Character::requestAttack(enemy, GargoyleProperties::GARGOYLE_CRITICAL_FACTOR);
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
    if (rand() % 100 < GargoyleProperties::GARGOYLE_PERCENT_FOR_FOLLOW_TO_HERO)
        return true;
    return false;
}

std::vector<CellPoint> Gargoyle::makeMove(CellPoint from, CellPoint heroPos) const { // Паттерн: Strategy
    std::vector<CellPoint> res;
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
    for (int i = -GargoyleProperties::GARGOYLE_MOVE; i <= GargoyleProperties::GARGOYLE_MOVE; ++i) {
        for (int j = -GargoyleProperties::GARGOYLE_MOVE; j <= GargoyleProperties::GARGOYLE_MOVE; ++j) {
            if (i != 0 && j != 0) {
                res.emplace_back(from.getX() + i,from.getY() + j);
            }
        }
    }
    return res;
}

bool Gargoyle::inRangeVisibility(CellPoint monsterPos, CellPoint objectPos) {
    return abs(monsterPos.getX() - objectPos.getX()) <= GargoyleProperties::GARGOYLE_RANGE_VISIBILITY && //попадает в прямоугольник видимости
           abs(monsterPos.getY() - objectPos.getY()) <= GargoyleProperties::GARGOYLE_RANGE_VISIBILITY;
}

double Gargoyle::getHealth() const {
    return Character::getHealth();
}

double Gargoyle::getDodgeFactor() const {
    return GargoyleProperties::GARGOYLE_DODGE_FACTOR;
}

Gargoyle* Gargoyle::clone() const {
    return new Gargoyle(model, name, health, attackPower, protection);
}

bool Gargoyle::checkPositiveHealth() const {
    return health > 0;
}

std::vector<std::string> Gargoyle::getModel() const {
    return Character::getModel();
}

std::string Gargoyle::getName() const {
    return Character::getName();
}

