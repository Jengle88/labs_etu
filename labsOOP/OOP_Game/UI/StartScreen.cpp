#include "StartScreen.h"
#include "../Tools/Printer.h"

StartScreen::StartScreen() {
    menuItemNames.resize(menuItemNamesIDs.size());
    for (int i = 0; i < menuItemNamesIDs.size(); ++i) {
        menuItemNames[i] = menuItemNamesIDs[i].first;
    }
}

void StartScreen::showUpdatedScreen(int selectedMenuItem) const {
    Printer::printMenuWithChoice(menuItemNames, selectedMenuItem);
}

std::string StartScreen::getScreenName() const {
    return "startScreen";
}

int StartScreen::getMenuSize() const {
    return menuItemNames.size();
}

void StartScreen::clearScreen() const {
    system("clear");
}
