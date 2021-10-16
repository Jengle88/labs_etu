#include "../Tools/CellPoint.h"

#define ROOT_EPLISON_FOR_CRITICAL 1e-2
#define CRITICAL_FACTOR 1.75
#define DODGE_FACTOR 0.6

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
    virtual void requestAttack(Character &enemy) = 0;
    virtual void requestProtect(double attackPower) = 0;

};
