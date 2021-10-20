#pragma once
#include <vector>
#include "../Tools/CellPoint.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

#define ROOT_EPSILON 1e-2
#define CHARACTER_CRITICAL_FACTOR 1.75
#define CHARACTER_DODGE_FACTOR 0.6
#define CHARACTER_MAX_HEALTH 100
#define CHARACTER_DAMAGE 1
#define CHARACTER_PROTECTION 1
#define CHARACTER_LUCK 1

#define LOW_HEALTH_PERCENT 30

enum CharacterType {
    CHARACTER,
    MONSTER,
    SKELETON_ARCHER,
    GARGOYLE,
    MAIN_HERO,
    CHARACTER_TYPE_SIZE
};

class Character {
protected:
    int characterType;
    double health;
    double attackPower;
    double protection;
    double luck = 1; // >= 1
    virtual bool isCriticalCase() const;
    virtual double calcReflectionArmor() const;
public:
    Character(int characterType, double health, double attackPower, double protection, double luck);
    Character() = default;
    virtual std::vector<double> requestAttack(Character &enemy, double criticalFactor); // возвращает информацию, был ли критический удар, уклонение и изменение здоровья
    virtual bool requestProtect(double attackPower); // возвращает информацию, было ли уклонение
    virtual bool requestDodge() const; // возвращает информацию, уклонился ли
    virtual Character* clone() const; // Паттерн: Прототип
    virtual double getDodgeFactor() const;
    double getHealth() const;
};
