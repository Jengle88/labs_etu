#include "Character.h"

double Character::calcReflectionArmor() const {
    return 1 / (this->protection + 2) + 0.5; // функция 1/(x+2) + 0.5 для расчёта множителя отражения удара доспехом
}

Character::Character(double health, double attackPower, double protection, double luck) : health(health), attackPower(attackPower), protection(protection), luck(luck) {}

Character::Character() {}

double Character::getHealth() const {
    return health;
}
bool Character::isCriticalCase(double luck) const {
    srand(time(0)); // сделать глобально в начале игры????
    double checkCriticalAttack = std::sin(
            (rand() % 100 + 1 / double(rand() % 100)) * luck); // есть ли способ проще? //luck >= 1, поэтому проблем нет
    return ((checkCriticalAttack - int(checkCriticalAttack)) <= ROOT_EPSILON);
}