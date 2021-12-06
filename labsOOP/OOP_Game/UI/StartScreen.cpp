//
// Created by evgeny on 05.12.2021.
//

#include "StartScreen.h"
#include "../Tools/Printer.h"

StartScreen::StartScreen() {
    menuItemNames.resize(menuItemNamesIDs.size());
    for (int i = 0; i < menuItemNamesIDs.size(); ++i) {
        menuItemNames[i] = menuItemNamesIDs[i].first;
    }
}

void StartScreen::showUpdatedScreen(int selectedThing) const {
    Printer::printMenuWithChoice(menuItemNames, selectedThing);
}

std::string StartScreen::getScreenName() const {
    return "startScreen";
}

std::string StartScreen::getMenuItemName(int item) const {
    if (0 <= item && item < menuItemNames.size())
        return menuItemNames[item];
    return "";
}

int StartScreen::getMenuSize() const {
    return menuItemNames.size();
}

void StartScreen::clearScreen() const {
    system("clear");
}
