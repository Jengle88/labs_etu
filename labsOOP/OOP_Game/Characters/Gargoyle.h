#pragma once
#include "Character.h"
#include "Enemy.h"
#include "../Rules/CharacterProperties.h"

class Gargoyle: public Character, public Enemy {
    struct GargoyleProperties{
        static std::string GARGOYLE_NAME;
        static double GARGOYLE_CRITICAL_FACTOR;
        static double GARGOYLE_DODGE_FACTOR;
        static int GARGOYLE_RANGE_VISIBILITY;
        static double GARGOYLE_PERCENT_FOR_FOLLOW_TO_HERO;
        static int GARGOYLE_MOVE;
        static double GARGOYLE_MAX_HEALTH;
        static double GARGOYLE_DAMAGE;
        static double GARGOYLE_PROTECTION;
        static double GARGOYLE_LUCK;
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

    static void setDefaultProperties(const CharacterProperties &characterProperties);

};
