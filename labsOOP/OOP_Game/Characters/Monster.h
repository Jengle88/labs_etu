#pragma once
#include "Character.h"
#include "Enemy.h"
#include "../Rules/CharacterProperties.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

class Monster : public Character, public Enemy {
    struct MonsterProperties{
        static std::string MONSTER_NAME;
        static double MONSTER_CRITICAL_FACTOR;
        static double MONSTER_DODGE_FACTOR;
        static int MONSTER_RANGE_VISIBILITY;
        static double MONSTER_PERCENT_FOR_FOLLOW_TO_HERO;
        static int MONSTER_MOVE;
        static double MONSTER_MAX_HEALTH;
        static double MONSTER_DAMAGE;
        static double MONSTER_PROTECTION;
        static double MONSTER_LUCK;
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
    static void setDefaultProperties(const CharacterProperties &characterProperties);
};
