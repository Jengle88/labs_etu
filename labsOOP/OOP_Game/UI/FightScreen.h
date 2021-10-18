#include "../Characters/MainHero.h"
#include "../Characters/Enemy.h"
#include "../Data/DataManager.h"

enum FightAction {
    ATTACK = 'a',
    USE = 'e'
};

class FightScreen {
    MainHero* mainHero;
    DataManager dataManager;
    Enemy* enemy;
public:
    FightScreen(MainHero* mainHero, DataManager dataManager, Enemy* enemy);
    bool fightObserver(MainHero &mainHero, Enemy& enemy);
    void showUpdatedScreen();
    void requestAction(char action);

};
