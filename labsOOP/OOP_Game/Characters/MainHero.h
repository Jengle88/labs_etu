#include "Character.h"

class MainHero : public Character {
    double health;
    double attackPower;
    double stamina;
    double luck;
public:
    MainHero(double health, double attackPower, double protection, double stamina, double luck) : Character(health, attackPower, protection), stamina(stamina), luck(luck) {}
    double requestAttack(Character &enemy) override;
    bool requestDodge() override;
    double requestProtect(double attackPower) override;
};
