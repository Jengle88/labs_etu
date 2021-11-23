#include "Archer.h"

std::string Archer::ArcherProperties::ARCHER_NAME;
double Archer::ArcherProperties::ARCHER_CRITICAL_FACTOR;
double Archer::ArcherProperties::ARCHER_DODGE_FACTOR;
int Archer::ArcherProperties::ARCHER_RANGE_VISIBILITY;
double Archer::ArcherProperties::ARCHER_PERCENT_FOR_FOLLOW_TO_HERO;
int Archer::ArcherProperties::ARCHER_MOVE;
double Archer::ArcherProperties::ARCHER_MAX_HEALTH;
double Archer::ArcherProperties::ARCHER_DAMAGE;
double Archer::ArcherProperties::ARCHER_PROTECTION;
double Archer::ArcherProperties::ARCHER_LUCK;

Archer::Archer(std::vector<std::string> model, std::string name, double health, double attackPower, double protection, double luck)
        : Character(model, name, health, attackPower, protection, luck) {}

std::vector<double> Archer::requestAttack(Character &enemy) {
    return Character::requestAttack(enemy, ArcherProperties::ARCHER_CRITICAL_FACTOR);
}

bool Archer::requestProtect(double attackPower) {
    return Character::requestProtect(attackPower);
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
    if (rand() % 100 < ArcherProperties::ARCHER_PERCENT_FOR_FOLLOW_TO_HERO)
        return true;
    return false;
}

std::vector<CellPoint> Archer::makeMove(CellPoint from, CellPoint heroPos) const { // Паттерн: Strategy
    std::vector<CellPoint> res;
    if (Archer::inRangeVisibility(from, heroPos) && willFollowToHero()) {
        int deltaX = -(from.getX() - heroPos.getX()) /
                     std::max(1, abs(from.getX() - heroPos.getX()));
        int deltaY = -(from.getY() - heroPos.getY()) /
                     std::max(1, abs(from.getY() - heroPos.getY()));
        res.emplace_back(from.getX() + deltaX, from.getY());
        res.emplace_back(from.getX(), from.getY() + deltaY);
        return res;
    }
    for (int i = -ArcherProperties::ARCHER_MOVE; i <= ArcherProperties::ARCHER_MOVE; ++i) {
        for (int j = -ArcherProperties::ARCHER_MOVE; j <= ArcherProperties::ARCHER_MOVE; ++j) {
            if (i == 0 ^ j == 0) {
                res.emplace_back(from.getX() + i, from.getY() + j);
            }
        }
    }
    return res;
}

bool Archer::inRangeVisibility(CellPoint monsterPos, CellPoint objectPos) {
    return abs(monsterPos.getX() - objectPos.getX()) <= ArcherProperties::ARCHER_RANGE_VISIBILITY &&
           //попадает в прямоугольник видимости
           abs(monsterPos.getY() - objectPos.getY()) <= ArcherProperties::ARCHER_RANGE_VISIBILITY;

}

double Archer::getHealth() const {
    return Character::getHealth();
}

double Archer::getDodgeFactor() const {
    return ArcherProperties::ARCHER_DODGE_FACTOR;
}

Archer *Archer::clone() const {
    return new Archer(model, name, health, attackPower, protection);
}

bool Archer::checkPositiveHealth() const {
    return health > 0;
}

std::vector<std::string> Archer::getModel() const {
    return Character::getModel();
}

std::string Archer::getName() const {
    return Character::getName();
}

void
Archer::setDefaultProperties(const std::string &name, double health, double attackPower, double protection, double luck,
                             int visibility, double criticalFactor, double dodgeFactor, int percentForFollowToHero,
                             int lengthMove) {
    ArcherProperties::ARCHER_NAME = name;
    ArcherProperties::ARCHER_MAX_HEALTH = health;
    ArcherProperties::ARCHER_PROTECTION = protection;
    ArcherProperties::ARCHER_DAMAGE = attackPower;
    ArcherProperties::ARCHER_LUCK = luck;
    ArcherProperties::ARCHER_RANGE_VISIBILITY = visibility;
    ArcherProperties::ARCHER_CRITICAL_FACTOR = criticalFactor;
    ArcherProperties::ARCHER_DODGE_FACTOR = dodgeFactor;
    ArcherProperties::ARCHER_PERCENT_FOR_FOLLOW_TO_HERO = percentForFollowToHero;
    ArcherProperties::ARCHER_MOVE = lengthMove;
}

