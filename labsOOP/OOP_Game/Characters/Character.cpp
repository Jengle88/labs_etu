#include "Character.h"

Character::Character(int characterType, double health, double attackPower, double protection, double luck)
        : characterType(characterType), health(health), attackPower(attackPower), protection(protection), luck(luck) {}

Character::Character() {}

double Character::calcReflectionArmor() const {
    return 1 / (this->protection + 2) + 0.5; // функция 1/(x+2) + 0.5 для расчёта множителя отражения удара доспехом
}

double Character::getHealth() const {
    return health;
}

bool Character::isCriticalCase() const {
    double checkCriticalAttack = std::sin(
            (rand() % 100 + 1 / double(std::max(rand(), 1) % 100)) *
            luck); // luck >= 1, поэтому проблем нет
    return ((checkCriticalAttack - int(checkCriticalAttack)) <= ROOT_EPSILON);
}