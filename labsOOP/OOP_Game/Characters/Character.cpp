#include "Character.h"

double Character::calcReflectionArmor() {
    return 1 / (this->protection + 2) + 0.5; // функция 1/(x+2) + 0.5 для расчёта множителя отражения удара доспехом
}

Character::Character(double health, double attackPower, double protection) : health(health), attackPower(attackPower), protection(protection) {}

Character::Character() {}

double Character::getHealth() const {
    return health;
}
