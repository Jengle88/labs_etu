#pragma once
#include <vector>
#include <cmath>
#include <map>
#include "Character.h"
#include "../Objects/Thing.h"
#include "../Rules/CharacterProperties.h"
#include <algorithm>


class MainHero : public Character {
    struct MainHeroProperties{
        static std::string MAIN_HERO_NAME;
        static double MAIN_HERO_CRITICAL_FACTOR; // множитель увеличения урона при критической атаке
        static double MAIN_HERO_DODGE_FACTOR; // чем меньше, тем меньше будет урон после частичного уклонения
        static int MAIN_HERO_RANGE_VISIBILITY;
        static double MAIN_HERO_MAX_HEALTH;
        static double MAIN_HERO_DAMAGE;
        static double MAIN_HERO_PROTECTION;
        static double MAIN_HERO_LUCK;
    };
    std::vector<Thing*> inventory;
    std::map<std::string, int> countKilledEnemy;
    bool requestProtect(double attackPower) override;
    bool requestDodge() const override;
    void recalcCharacteristics(std::map<std::string, double> thingProperties);
public:
    MainHero(std::vector<std::string> model,
                std::string name = MainHeroProperties::MAIN_HERO_NAME,
                double health = MainHeroProperties::MAIN_HERO_MAX_HEALTH,
                double attackPower = MainHeroProperties::MAIN_HERO_DAMAGE,
                double protection = MainHeroProperties::MAIN_HERO_PROTECTION,
                double luck = MainHeroProperties::MAIN_HERO_LUCK);
    MainHero() = default;

    // урон, уклонение и крит
    std::vector<double> requestAttack(Character &enemy);
    void takeThing(Thing *thing);
    void ejectThing(int pos);
    bool useThing(int pos);
    bool hasThing(int thingObject) const;
    void writeKill(std::string enemyName);
    const std::vector<Thing*> & getInventory() const;
    std::map<std::string, int> &getCountKilledEnemy();
    const std::map<std::string, int> &getCountKilledEnemy() const;
    std::string getName() const override;
    std::vector<std::string> getModel() const override;
    MainHero * clone() const override;
    double getDodgeFactor() const override;
    static int getRangeVisibility();
    bool checkPositiveHealth() const;
    void resetModel(std::vector<std::string> newModel);
    static void setDefaultProperties(const CharacterProperties &characterProperties);


    friend class ThingsManager;
};
