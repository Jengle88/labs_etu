#pragma once

#include <vector>
#include <string>

enum MenuItemID {
    START_NEW_GAME,
    LOAD_GAME,
    SETTINGS,
    EXIT
};

class StartScreen {
    std::vector<std::pair<std::string, int>> menuItemNamesIDs = {
            {"Start New Game",            START_NEW_GAME},
            {"Load Game (not ready yet)", LOAD_GAME},
            {"Settings",                  SETTINGS},
            {"Exit",                      EXIT}
    };
    std::vector<std::string> menuItemNames; // удобно для вывода
public:
    StartScreen();
    void showUpdatedScreen(int selectedThing) const;
    std::string getScreenName() const;
    std::string getMenuItemName(int item) const;
    int getMenuSize() const;
    void clearScreen() const;


};


