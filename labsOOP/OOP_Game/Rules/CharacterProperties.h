#pragma once

#include <string>

class CharacterProperties {
    // -1 - параметр не используется
    std::string name = "";
    double health = 0;
    double attackPower = 0;
    double protection = 0;
    double luck = 0;
    int visibility = 0;
    double criticalFactor = 0;
    double dodgeFactor = 0;
    int percentForFollowToHero = 0;
    int lengthMove = 0;
public:
    CharacterProperties(const std::string &name, double health, double attackPower, double protection, double luck,
                   int visibility, double criticalFactor, double dodgeFactor, int percentForFollowToHero,
                   int lengthMove) : name(name), health(health), attackPower(attackPower),
                                                             protection(protection), luck(luck), visibility(visibility),
                                                             criticalFactor(criticalFactor), dodgeFactor(dodgeFactor),
                                                             percentForFollowToHero(percentForFollowToHero),
                                                             lengthMove(lengthMove) {}

    std::string getName() const;
    double getHealth() const;
    double getAttackPower() const;
    double getProtection() const;
    double getLuck() const;
    int getVisibility() const;
    double getCriticalFactor() const;
    double getDodgeFactor() const;
    int getPercentForFollowToHero() const;
    int getLengthMove() const;
};
