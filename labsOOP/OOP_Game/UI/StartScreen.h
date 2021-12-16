#pragma once

#include <vector>
#include <string>

enum MenuItemID {
    START_NEW_GAME,
    LOAD_GAME,
    KEY_SETTINGS,
    EXIT
};

class StartScreen {
    std::vector<std::pair<std::string, int>> menuItemNamesIDs = {
            {"Start New Game",            START_NEW_GAME},
            {"Load Game (not ready yet)", LOAD_GAME},
            {"Key Settings",              KEY_SETTINGS},
            {"Exit",                      EXIT}
    };
    std::vector<std::string> menuItemNames; // удобно для вывода
public:
    StartScreen();
    void showUpdatedScreen(int selectedMenuItem) const;
    std::string getScreenName() const;
    int getMenuSize() const;
    void clearScreen() const;
};


