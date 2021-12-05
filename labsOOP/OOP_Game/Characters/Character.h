#pragma once
#include <vector>
#include "../Tools/CellPoint.h"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <ostream>

#define ROOT_EPSILON 1e-2
#define LOW_HEALTH_PERCENT 30

class Character {
protected:
    struct DefaultCharacterProperties{
        constexpr static char CHARACTER_NAME[] = "Character";
        constexpr static double CHARACTER_CRITICAL_FACTOR = 1.75; // множитель увеличения урона при критической атаке
        constexpr static double CHARACTER_DODGE_FACTOR = 0.6; // чем меньше, тем меньше будет урон после частичного уклонения
    };
    std::string name;
    double health;
    double attackPower;
    double protection;
    double luck; // >= 1
    std::vector<std::string> model;
    virtual bool isCriticalCase() const;
    virtual double calcReflectionArmor() const;
public:
    friend std::ostream &operator<<(std::ostream &os, const Character &character);

    Character(std::vector<std::string> model, std::string name, double health, double attackPower, double protection,
              double luck);
    Character() = default;
    virtual std::vector<double> requestAttack(Character &enemy, double criticalFactor); // возвращает информацию, был ли критический удар, уклонение и изменение здоровья
    virtual bool requestProtect(double attackPower); // возвращает информацию, было ли уклонение
    virtual bool requestDodge() const; // возвращает информацию, уклонился ли
    virtual double getDodgeFactor() const;
    virtual double getHealth() const;
    virtual std::string getName() const;
    virtual std::vector<std::string> getModel() const;
    virtual Character* clone() const; // Паттерн: Прототип
};
