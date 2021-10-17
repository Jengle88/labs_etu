#pragma once
#include "Character.h"
#include "Enemy.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

#define MONSTER_CRITICAL_FACTOR 1.25
#define MONSTER_DODGE_FACTOR 0.8
#define MONSTER_MAX_HEALTH 60
#define MONSTER_RANGE_VISIBILITY 3
#define MONSTER_PERCENT_FOR_FOLLOW_TO_HERO 80

class Monster : virtual public Character, virtual public Enemy {
//    using Character::calcReflectionArmor;
//    using Character::isCriticalCase;
    bool isCriticalCase(double lucky) const override;
    double calcReflectionArmor() const override; // по-хорошему, изменить под использования реализации в Character
    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    bool willFollowToHero() const override;
public:
    Monster(double health, double attackPower, double protection);
    std::vector<double> requestAttack(Character &enemy) override;
    using Character::getHealth;
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
};
