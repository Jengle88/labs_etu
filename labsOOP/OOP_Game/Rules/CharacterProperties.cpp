#include "CharacterProperties.h"

std::string CharacterProperties::getName() const {
    return name;
}

double CharacterProperties::getHealth() const {
    return health;
}

double CharacterProperties::getAttackPower() const {
    return attackPower;
}

double CharacterProperties::getProtection() const {
    return protection;
}

double CharacterProperties::getLuck() const {
    return luck;
}

int CharacterProperties::getVisibility() const {
    return visibility;
}

double CharacterProperties::getCriticalFactor() const {
    return criticalFactor;
}

double CharacterProperties::getDodgeFactor() const {
    return dodgeFactor;
}

int CharacterProperties::getPercentForFollowToHero() const {
    return percentForFollowToHero;
}

int CharacterProperties::getLengthMove() const {
    return lengthMove;
}
