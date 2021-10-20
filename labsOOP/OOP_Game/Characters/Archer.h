#pragma once
#include "Enemy.h"
#include "Character.h"

#define ARCHER_CRITICAL_FACTOR 2
#define ARCHER_DODGE_FACTOR 0.6
#define ARCHER_RANGE_VISIBILITY 4
#define ARCHER_PERCENT_FOR_FOLLOW_TO_HERO 70 // значения варьируются от 0 до 100
#define ARCHER_MOVE 1
#define ARCHER_MAX_HEALTH 80
#define ARCHER_LUCK 0.55
#define ARCHER_DAMAGE 2
#define ARCHER_PROTECTION 1

class Archer final: public virtual Character, public virtual Enemy {
    double luck = ARCHER_LUCK;
    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    bool isCriticalCase() const override;
    double calcReflectionArmor() const override;
    bool willFollowToHero() const override;

public:

    Archer(double health, double attackPower, double protection);
    ~Archer() override = default;
    std::vector<double> requestAttack(Character &enemy) override;
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
    int getCharacterType() const override;
    double getHealth() const override;
    double getDodgeFactor() const override;
    Archer* clone() const override;
    bool checkPositiveHealth() const override;
};