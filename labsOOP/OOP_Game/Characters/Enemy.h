#pragma once
#include <vector>
#include "Character.h"

class Enemy {
public:
    virtual std::vector<double> requestAttack(Character &enemy) = 0; // возвращает информацию, был ли критический удар, уклонение и изменение здоровья
    virtual bool requestProtect(double attackPower) = 0; // возвращает информацию, было ли уклонение
    virtual bool requestDodge() const = 0; // возвращает информацию, уклонился ли
    virtual bool isCriticalCase() const = 0;
    virtual double calcReflectionArmor() const = 0;
    virtual std::vector<CellPoint> makeMove(CellPoint from, CellPoint heroPos) const = 0; // Паттерн: Strategy
    virtual bool willFollowToHero() const = 0;
    virtual int getCharacterType() const = 0;
    virtual double getHealth() const = 0;
    virtual bool checkPositiveHealth() const = 0;
    virtual ~Enemy() = default;
};
