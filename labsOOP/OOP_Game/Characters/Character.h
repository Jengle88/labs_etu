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
#define LOW_HEALTH_PERCENT 30
#define MAX_COUNT_HEALTH_THINGS 3

enum CharacterType {
    MAIN_HERO,
    MONSTER,
    SKELETON_ARCHER,
    GARGOYLE,
    CHARACTER_TYPE_SIZE
};

class Character {
protected:
    int characterType;
    double health;
    double attackPower;
    double protection;
    double luck = 1; // >= 1
    virtual bool isCriticalCase(double luck) const;
    virtual double calcReflectionArmor() const;
public:
    Character(int characterType, double health, double attackPower, double protection, double luck);
    Character();
    virtual std::vector<double> requestAttack(Character &enemy) = 0; // возвращает информацию, был ли критический удар, уклонение и изменение здоровья
    virtual bool requestProtect(double attackPower) = 0; // возвращает информацию, было ли уклонение
    virtual bool requestDodge() const = 0; // возвращает информацию, уклонился ли
    double getHealth() const;

};
