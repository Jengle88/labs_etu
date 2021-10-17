#pragma once
#include <vector>
#include "../Tools/CellPoint.h"

#define ROOT_EPSILON_FOR_CRITICAL 1e-2
#define CRITICAL_FACTOR 1.75
#define DODGE_FACTOR 0.6
#define MAX_HEALTH 100
#define LOW_HEALTH_PERCENT 30
#define MAX_COUNT_HEALTH_THINGS 3

enum EnemyType {
    MONSTER,
    SKELETON_ARCHER,
    GARGOYLE,
    ENEMY_TYPE_SIZE
};

class Character {
protected:
    double health;
    double attackPower;
    double protection;
    virtual bool isCriticalCase(double lucky) = 0;
    double calcReflectionArmor();
public:
    Character(double health, double attackPower, double protection);
    Character();
    virtual std::vector<double> requestAttack(Character &enemy) = 0; // возвращает информацию, был ли критический удар, уклонение и изменение здоровья
    virtual bool requestProtect(double attackPower) = 0; // возвращает информацию, было ли уклонение
    virtual bool requestDodge() = 0; // возвращает информацию, уклонился ли
    double getHealth() const;

};
