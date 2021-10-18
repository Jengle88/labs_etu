#pragma once
#include "Enemy.h"
#include "Character.h"

#define ARCHER_CRITICAL_FACTOR 2
#define ARCHER_DODGE_FACTOR 0.6
#define ARCHER_MAX_HEALTH 80
#define ARCHER_RANGE_VISIBILITY 4
#define ARCHER_PERCENT_FOR_FOLLOW_TO_HERO 1000
#define ARCHER_LUCK 1.25
#define ARCHER_MOVE 1

class Archer final: public Character, public Enemy {
    double luck = ARCHER_LUCK;
    bool isCriticalCase(double lucky) const override;
    double calcReflectionArmor() const override;
    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    bool willFollowToHero() const override;

public:

    Archer(double health, double attackPower, double protection);
    std::vector<double> requestAttack(Character &enemy) override;
    using Character::getHealth;
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
    int getCharacterType() const override;
    ~Archer() override = default;

};