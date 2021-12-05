#include "FightScreen.h"
#include "../GameHandler.h"

FightScreen::FightScreen(const std::vector<std::string>& heroModel, const std::vector<std::string>& enemyModel)
                                                            : heroModel(heroModel), enemyModel(enemyModel) {}

void FightScreen::showUpdatedScreen(MainHero &mainHero, int selectedThing) {
    auto fightModel = heroModel;
    int distBetweenCharacters = 7; // пространство между героем и врагом на экране
    std::for_each(fightModel.begin(), fightModel.end(),
                  [&distBetweenCharacters](std::string &str) { str += std::string(distBetweenCharacters, ' '); });
    for (int i = 0; i < fightModel.size(); ++i) {
        fightModel[i] += enemyModel[i];
    }
    showFighterModels(fightModel);
    showInventory(&mainHero, selectedThing);
}

void FightScreen::showHealthInfo(MainHero &mainHero, Enemy &enemy) const {
    Printer::printHealthInfo(std::max(mainHero.getHealth(), 0.0), std::max(dynamic_cast<Character &>(enemy).getHealth(), 0.0));
}

void FightScreen::showMessage(const std::string &message) const {
    Printer::printMessage(message);
}

void FightScreen::clearScreen() const {
    std::system("clear");
}

void FightScreen::showInventory(MainHero *hero, int selectedThing) const {
    auto inventory = hero->getInventory();
    std::vector<std::string> thingsName(inventory.size());
    for (int i = 0; i < inventory.size(); ++i) {
        thingsName[i] = inventory[i]->getNameThing();
    }
    Printer::printMenuWithChoice(thingsName, selectedThing);
}



void FightScreen::showFighterModels(const std::vector<std::string> &models) const {
    Printer::printModels(models);
}

void FightScreen::showAttackInfo(const std::string &nameCharacter, double damage, bool wasDodge, bool wasCritical) const {
    Printer::printAttackInfo(nameCharacter, damage, wasDodge, wasCritical);
}
