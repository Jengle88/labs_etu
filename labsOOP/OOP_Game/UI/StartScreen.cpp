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

void StartScreen::showUpdatedScreen(int selectedThing) {
    Printer::printMenuWithChoice(menuItemNames, selectedThing);
}

void StartScreen::clearScreen() {
    system("clear");
}
