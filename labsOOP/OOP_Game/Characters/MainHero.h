#include <vector>
#include <cmath>
#include "Character.h"
#include "../Objects/Thing.h"



class MainHero : public Character {
    double stamina;
    double luck; // >= 1
    std::vector<Thing> things;
    bool isCriticalCase(double luck) override;
    void requestProtect(double attackPower) override;
    double requestDodge();
    void recalcCharacteristics(std::vector<double> thingProperties);
public:
    MainHero(double health, double attackPower, double protection, double stamina, double luck) : Character(health, attackPower, protection), stamina(stamina), luck(std::max(luck, 1.0)) {}
    MainHero() {}
    void requestAttack(Character &enemy) override;
    void takeThing(Thing thing);
    void ejectThing(int pos);
    void replaceThing(int pos, Thing thing);

};
