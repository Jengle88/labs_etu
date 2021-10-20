#include "FightScreen.h"

FightScreen::FightScreen(MainHero &mainHero, Enemy &enemy) : mainHero(mainHero),
                                                             dataManager(DataManager()),
                                                             enemy(enemy) {}

int FightScreen::fightObserver() {
    showUpdatedScreen();
    Printer::printHealthInfo(std::max(mainHero.getHealth(), 0.0),
                             std::max(dynamic_cast<Character &>(enemy).getHealth(), 0.0));
    while (mainHero.checkPositiveHealth() && enemy.checkPositiveHealth()) {
        char action = getchar();
        std::system("clear");
        if(!requestAction(action)) {
            getchar(); // считываем перенос строки
            return FightStatus::LEAVE_FIGHT;
        }
        showUpdatedScreen();
        Printer::printHealthInfo(std::max(mainHero.getHealth(), 0.0),
                                 std::max(dynamic_cast<Character &>(enemy).getHealth(), 0.0));
    }

    if (mainHero.checkPositiveHealth())
        mainHero.writeKill(enemy.getCharacterType());
    std::cout << "Вы победили!\nНажмите любую кнопку, чтобы продолжить.";
    getchar();
    return mainHero.checkPositiveHealth();
}

void FightScreen::showUpdatedScreen() {
    auto fightModel = dataManager.getHero(mainHero.hasThing(ThingObject::SWORD),
                                          mainHero.hasThing(ThingObject::ARMOR));
    int distBetweenCharacters = 7; // пространство между героем и врагом на экране
    std::for_each(fightModel.begin(), fightModel.end(),
                  [&distBetweenCharacters](std::string &str) { str += std::string(distBetweenCharacters, ' '); });
    auto enemyModel = dataManager.getEnemy(enemy.getCharacterType());
    for (int i = 0; i < fightModel.size(); ++i) {
        fightModel[i] += enemyModel[i];
    }
    for (auto &fightRow: fightModel) {
        std::cout << fightRow << '\n';
    }
    Printer::printInventory(&mainHero, true);

}

bool FightScreen::requestAction(char action) {
    int numberThing = -1;
    std::vector<double> heroAttackInfo;
    std::vector<double> enemyAttackInfo;
    switch (tolower(action)) {
        case FightAction::ATTACK:
            heroAttackInfo = mainHero.requestAttack(dynamic_cast<Character &>(enemy)); // TODO Вывод инфы об уроне
            Printer::printAttackInfo(CharacterType::MAIN_HERO, heroAttackInfo[0], heroAttackInfo[1] > 0, heroAttackInfo[2] > 0);
//            usleep(COOl_DOWN); // Торможение на 0.3 сек
            enemyAttackInfo = enemy.requestAttack(dynamic_cast<Character &>(mainHero));
            Printer::printAttackInfo(enemy.getCharacterType(), enemyAttackInfo[0], enemyAttackInfo[1] > 0, enemyAttackInfo[2] > 0);
            break;
        case FightAction::USE:
            std::cin >> numberThing;
            if (!mainHero.useThing(numberThing - 1)) {
                std::cout << "Предмета нет или он не может быть использован\n";
            }
            break;
        case MoveSide::EXIT:
            return false;
    }
    std::cin.ignore(32767, '\n');
    return true;
}
