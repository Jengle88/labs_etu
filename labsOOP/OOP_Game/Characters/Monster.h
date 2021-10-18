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
#define MONSTER_PERCENT_FOR_FOLLOW_TO_HERO 1000
#define MONSTER_LUCK 1
#define MONSTER_MOVE 1

class Monster : public Character, public Enemy {
    double luck = MONSTER_LUCK;
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
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
    using Character::getHealth;
    int getCharacterType() const override;
    bool checkPositiveHealth() const override;
    ~Monster() override = default;
};
