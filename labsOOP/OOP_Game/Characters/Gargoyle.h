#pragma once
#include "Character.h"
#include "Enemy.h"

class Gargoyle: public Character, public Enemy {
    struct GargoyleProperties{
        constexpr static char GARGOYLE_NAME[] = "Gargoyle";
        constexpr static double GARGOYLE_CRITICAL_FACTOR = 2;
        constexpr static double GARGOYLE_DODGE_FACTOR = 0.6;
        constexpr static double GARGOYLE_RANGE_VISIBILITY = 5;
        constexpr static double GARGOYLE_PERCENT_FOR_FOLLOW_TO_HERO = 70;
        constexpr static double GARGOYLE_MOVE = 1;
        constexpr static double GARGOYLE_MAX_HEALTH = 95;
        constexpr static double GARGOYLE_DAMAGE = 2;
        constexpr static double GARGOYLE_PROTECTION = 2;
        constexpr static double GARGOYLE_LUCK = 0.75;
    };

    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    bool isCriticalCase() const override;
    double calcReflectionArmor() const override;

    bool willFollowToHero() const override;
public:

    Gargoyle(std::vector<std::string> model,
                std::string name = GargoyleProperties::GARGOYLE_NAME,
                double health = GargoyleProperties::GARGOYLE_MAX_HEALTH,
                double attackPower = GargoyleProperties::GARGOYLE_DAMAGE,
                double protection = GargoyleProperties::GARGOYLE_PROTECTION,
                double luck = GargoyleProperties::GARGOYLE_LUCK);
    ~Gargoyle() override = default;
    std::vector<double> requestAttack(Character &enemy) override;
    std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const override;
    static bool inRangeVisibility(CellPoint monsterPos, CellPoint objectPos);
    double getHealth() const override;
    double getDodgeFactor() const override;
    std::string getName() const override;
    std::vector<std::string> getModel() const override;
    Gargoyle* clone() const override;
    bool checkPositiveHealth() const override;
};
