#include "FightScreen.h"
#include "../Logger/LoggerPull.h"

FightScreen::FightScreen(MainHero &mainHero, Enemy &enemy, DataManager* dataManager) : mainHero(mainHero),
                                                             dataManager(dataManager),
                                                             enemy(enemy),
                                                             heroModel(mainHero.getModel()),
                                                             enemyModel(enemy.getModel())
                                                             {}

int FightScreen::fightObserver() {
    showUpdatedScreen();
    LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Отображён экран боя"));
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

    if (mainHero.checkPositiveHealth()) {
        mainHero.writeKill(enemy.getName());
        LoggerPull::writeData("gameLogs",LoggerDataAdapter<Character>(dynamic_cast<Character&>(enemy), "Герой победил данного врага"));
        std::cout << "Вы победили!\nНажмите любую кнопку, чтобы продолжить.";
        getchar();
    }
    return mainHero.checkPositiveHealth();
}

void FightScreen::showUpdatedScreen() {
    auto fightModel = heroModel;
    int distBetweenCharacters = 7; // пространство между героем и врагом на экране
    std::for_each(fightModel.begin(), fightModel.end(),
                  [&distBetweenCharacters](std::string &str) { str += std::string(distBetweenCharacters, ' '); });
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
            LoggerPull::writeData("gameLogs",LoggerDataAdapter<std::string>("Герой произвёл атаку"));
            heroAttackInfo = mainHero.requestAttack(dynamic_cast<Character &>(enemy));
            Printer::printAttackInfo("Hero", heroAttackInfo[0], heroAttackInfo[1] > 0, heroAttackInfo[2] > 0);
            LoggerPull::writeData("gameLogs",LoggerDataAdapter<MainHero&>(mainHero, "Статус героя"));
//            usleep(COOl_DOWN); // Торможение на 0.3 сек
            enemyAttackInfo = enemy.requestAttack(dynamic_cast<Character &>(mainHero));
            Printer::printAttackInfo(enemy.getName(), enemyAttackInfo[0], enemyAttackInfo[1] > 0, enemyAttackInfo[2] > 0);
            LoggerPull::writeData("gameLogs",LoggerDataAdapter<Character&>(dynamic_cast<Character&>(enemy), "Статус врага"));
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
