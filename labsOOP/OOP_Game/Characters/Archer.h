#pragma once
#include "Enemy.h"
#include "Character.h"
#include "../Rules/CharacterProperties.h"

class Archer: public Character, public Enemy {
    struct ArcherProperties{
        static std::string ARCHER_NAME;
        static double ARCHER_CRITICAL_FACTOR;
        static double ARCHER_DODGE_FACTOR;
        static int ARCHER_RANGE_VISIBILITY;
        static double ARCHER_PERCENT_FOR_FOLLOW_TO_HERO;
        static int ARCHER_MOVE;
        static double ARCHER_MAX_HEALTH;
        static double ARCHER_DAMAGE;
        static double ARCHER_PROTECTION;
        static double ARCHER_LUCK;
    };
    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    bool isCriticalCase() const override;
    double calcReflectionArmor() const override;
    bool willFollowToHero() const override;
public:
    Archer(std::vector<std::string> model,
           std::string name = ArcherProperties::ARCHER_NAME,
           double health = ArcherProperties::ARCHER_MAX_HEALTH,
           double attackPower = ArcherProperties::ARCHER_DAMAGE,
           double protection = ArcherProperties::ARCHER_PROTECTION,
           double luck = ArcherProperties::ARCHER_LUCK);
    ~Archer() override = default;
    std::vector<double> requestAttack(Character &enemy) override;
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
    double getHealth() const override;
    double getDodgeFactor() const override;
    std::string getName() const override;
    std::vector<std::string> getModel() const override;
    Archer* clone() const override;
    bool checkPositiveHealth() const override;

    static void setDefaultProperties(const CharacterProperties &characterProperties);

};