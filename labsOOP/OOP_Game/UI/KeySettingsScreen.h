#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include "../Tools/Printer.h"

class KeySettingsScreen {
    std::unordered_map<std::string, std::unordered_map<int, char>> keysActionControl;
    static std::map<std::string, std::map<int, std::string>> actionBind;
    int sizeKeysControls = 0;
    int maxSizeNameKeyBound = 0;
public:
    explicit KeySettingsScreen(const std::unordered_map<std::string, std::unordered_map<int, char>> &keysActionControl,
                               const std::unordered_map<std::string, std::unordered_map<std::string, int>>& actionBind);
    void showUpdatedScreen(int selectedThing) const;
    std::string getScreenName() const;
    int getMenuSize() const;
    void clearScreen() const;
};


