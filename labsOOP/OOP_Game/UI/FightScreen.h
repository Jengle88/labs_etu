#include "../Characters/MainHero.h"
#include "../Characters/Enemy.h"
#include "../Data/DataManager.h"
#include <unistd.h>

//на 0.3 сек
#define COOl_DOWN 300000UL
enum FightStatus {
    LEAVE_FIGHT = -1,
    KILLED_ENEMY = 1,
    KILLED_HERO = 0
};
enum FightAction {
    ATTACK = 'a',
    USE = 'e'
};

class FightScreen {
    MainHero& mainHero;
    Enemy& enemy;
    DataManager dataManager;
public:
    FightScreen(MainHero& mainHero, Enemy& enemy);
    int fightObserver(/*MainHero &mainHero, Enemy& enemy*/);
    void showUpdatedScreen();
    bool requestAction(char action);

};
