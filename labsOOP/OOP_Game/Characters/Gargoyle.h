#pragma once

#include "Character.h"
#include "Enemy.h"

#define GARGOYLE_CRITICAL_FACTOR 2
#define GARGOYLE_DODGE_FACTOR 0.6
#define GARGOYLE_MAX_HEALTH 95
#define GARGOYLE_RANGE_VISIBILITY 5
#define GARGOYLE_PERCENT_FOR_FOLLOW_TO_HERO 1000
#define GARGOYLE_LUCK 1.5
#define GARGOYLE_MOVE 1

class Gargoyle: public Character, public Enemy {
    double luck = GARGOYLE_LUCK;
    bool isCriticalCase(double lucky) const override;
    double calcReflectionArmor() const override;
    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    bool willFollowToHero() const override;

public:
    Gargoyle(double health, double attackPower, double protection);
    std::vector<double> requestAttack(Character &enemy) override;
    using Character::getHealth;
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
    int getCharacterType() const override;
    ~Gargoyle() override = default;
};
