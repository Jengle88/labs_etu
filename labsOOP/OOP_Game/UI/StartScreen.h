#pragma once

#include <vector>
#include <string>

class StartScreen {
    enum ItemID {
        START_NEW_GAME,
        LOAD_GAME,
        SETTINGS,
        EXIT
    };
    std::vector<std::pair<std::string, int>> menuItemNamesIDs = {
            {"Start New Game", START_NEW_GAME},
            {"Load Game (not ready yet)", LOAD_GAME},
            {"Settings", SETTINGS},
            {"Exit", EXIT}
    };
    std::vector<std::string> menuItemNames; // удобно для вывода
public:
    StartScreen();
    void showUpdatedScreen(int selectedThing);
    void clearScreen();


};


