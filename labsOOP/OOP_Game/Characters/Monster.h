#pragma once
#include "Character.h"
#include "Enemy.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

class Monster : public Character, public Enemy {
    struct MonsterProperties{
        constexpr static char   MONSTER_NAME[] = "Monster";
        constexpr static double MONSTER_CRITICAL_FACTOR = 1.25;
        constexpr static double MONSTER_DODGE_FACTOR = 0.8;
        constexpr static double MONSTER_RANGE_VISIBILITY = 3;
        constexpr static double MONSTER_PERCENT_FOR_FOLLOW_TO_HERO = 70;
        constexpr static double MONSTER_MOVE = 1;
        constexpr static double MONSTER_MAX_HEALTH = 60;
        constexpr static double MONSTER_DAMAGE = 1;
        constexpr static double MONSTER_PROTECTION = 2;
        constexpr static double MONSTER_LUCK = 0.6;
    };
    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    bool isCriticalCase() const override;
    double calcReflectionArmor() const override;
    bool willFollowToHero() const override;
public:
    Monster(std::vector<std::string> model,
            std::string name = MonsterProperties::MONSTER_NAME,
            double health = MonsterProperties::MONSTER_MAX_HEALTH,
            double attackPower = MonsterProperties::MONSTER_DAMAGE,
            double protection = MonsterProperties::MONSTER_PROTECTION,
            double luck = MonsterProperties::MONSTER_LUCK);
    ~Monster() override = default;
    std::vector<double> requestAttack(Character &enemy) override;
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
    double getHealth() const override;
    double getDodgeFactor() const override;
    std::string getName() const override;
    std::vector<std::string> getModel() const override;
    Monster *clone() const override;
    bool checkPositiveHealth() const override;
};