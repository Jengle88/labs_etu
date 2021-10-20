#pragma once
#include "Character.h"
#include "Enemy.h"

#define GARGOYLE_CRITICAL_FACTOR 2
#define GARGOYLE_DODGE_FACTOR 0.6
#define GARGOYLE_RANGE_VISIBILITY 5
#define GARGOYLE_PERCENT_FOR_FOLLOW_TO_HERO 70 // значения варьируются от 0 до 100
#define GARGOYLE_MOVE 1
#define GARGOYLE_MAX_HEALTH 95
#define GARGOYLE_LUCK 0.75
#define GARGOYLE_DAMAGE 2
#define GARGOYLE_PROTECTION 2

class Gargoyle: public virtual Character, public virtual Enemy {
    double luck = GARGOYLE_LUCK;
    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    bool isCriticalCase() const override;
    double calcReflectionArmor() const override;
    bool willFollowToHero() const override;

public:
    Gargoyle(double health, double attackPower, double protection);
    ~Gargoyle() override = default;
    std::vector<double> requestAttack(Character &enemy) override;
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
    int getCharacterType() const override;
    double getHealth() const override;
    double getDodgeFactor() const override;
    Gargoyle* clone() const override;
    bool checkPositiveHealth() const override;
};
