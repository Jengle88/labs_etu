#include "../Tools/CellPoint.h"

class Character {
    double health;
    double attackPower;
    double protection;
public:
    Character(double health, double attackPower, double protection) : health(health), attackPower(attackPower), protection(protection) {}
    virtual double requestAttack(Character &enemy);
    virtual bool requestDodge();
    virtual double requestProtect(double attackPower);

};
