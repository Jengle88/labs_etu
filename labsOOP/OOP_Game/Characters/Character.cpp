#include <iostream>
#include "Character.h"

Character::Character(int characterType, double health, double attackPower, double protection, double luck)
        : characterType(characterType), health(health), attackPower(attackPower), protection(protection), luck(luck) {}

std::vector<double> Character::requestAttack(Character &enemy, double criticalFactor) {
    std::vector<double> actionTable(3); // таблица событий при ударе
    bool wasCriticalAttack = isCriticalCase();
    double startEnemyHealth = enemy.getHealth();
    bool wasDodge;
    if (wasCriticalAttack) {
        wasDodge = enemy.requestProtect(this->attackPower * criticalFactor);
    }
    else {
        wasDodge = enemy.requestProtect(this->attackPower);
    }
    return {startEnemyHealth - enemy.getHealth(), double(wasDodge), double(wasCriticalAttack)}; // был ли крит, было ли уклонение, уменьшение здоровья
}

bool Character::requestProtect(double attackPower) {
    bool wasDodge = this->requestDodge();
    if (wasDodge) {
        this->health -= attackPower * calcReflectionArmor() * this->getDodgeFactor();
    }
    else  {
        this->health -= attackPower * calcReflectionArmor();
    }
    return wasDodge;
}

bool Character::requestDodge() const {
    return isCriticalCase();
}

bool Character::isCriticalCase() const {
    double checkCriticalAttack = std::sin(
            (rand() % 100 + 1 / double(std::max(rand(), 1) % 100)) *
            luck); // luck >= 1, поэтому проблем нет
    return ((checkCriticalAttack - int(checkCriticalAttack)) <= ROOT_EPSILON);
}

double Character::calcReflectionArmor() const {
    return 1 / (this->protection + 2) + 0.5; // функция 1/(x+2) + 0.5 для расчёта множителя отражения удара доспехом
}

double Character::getHealth() const {
    return health;
}
