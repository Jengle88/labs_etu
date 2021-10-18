#include "FightScreen.h"
#include "FieldScreen.h"

FightScreen::FightScreen(MainHero* mainHero, DataManager dataManager, Enemy *enemy) : mainHero(mainHero), dataManager(dataManager), enemy(enemy) {}

bool FightScreen::fightObserver(MainHero &mainHero, Enemy &enemy) {
    while (mainHero.checkPositiveHealth() && enemy.checkPositiveHealth()) {
        requestAction(getchar());

    }

    return mainHero.checkPositiveHealth();
}

void FightScreen::showUpdatedScreen() {

}

void FightScreen::requestAction(char action) {
    int numberThing = -1;
    switch (action) {
        case FightAction::ATTACK:
            mainHero->requestAttack(dynamic_cast<Character&>(*enemy));
            enemy->requestAttack(dynamic_cast<Character&>(*mainHero));
            break;
        case FightAction::USE:
            std::cin >> numberThing;
            if (!mainHero->useThing(numberThing)) {
                // TODO добавить сообщение об ошибке
            }
    }

}
