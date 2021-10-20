#pragma once
#include "Character.h"
#include "Enemy.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

#define MONSTER_CRITICAL_FACTOR 1.25
#define MONSTER_DODGE_FACTOR 0.8
#define MONSTER_RANGE_VISIBILITY 3
#define MONSTER_PERCENT_FOR_FOLLOW_TO_HERO 70 // значения варьируются от 0 до 100
#define MONSTER_MOVE 1
#define MONSTER_MAX_HEALTH 60
#define MONSTER_LUCK 0.6
#define MONSTER_DAMAGE 1
#define MONSTER_PROTECTION 2

class Monster : public virtual Character, public virtual Enemy {
    double luck = MONSTER_LUCK;
    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    bool isCriticalCase() const override;
    double calcReflectionArmor() const override;
    bool willFollowToHero() const override;
public:
    Monster(double health, double attackPower, double protection);
    ~Monster() override = default;
    std::vector<double> requestAttack(Character &enemy) override;
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
    int getCharacterType() const override;
    double getHealth() const override;
    bool checkPositiveHealth() const override;
};
