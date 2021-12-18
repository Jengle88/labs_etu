#pragma once

#include <string>
#include <vector>
#include "../Tools/Printer.h"

enum FileRemoveState {
    FILE_NOT_FOUND = 0,
    FILE_SUCCESS_REMOVE = 1,
};
class LoadScreen {
    const std::vector<std::string>* nameFiles; // удобно для вывода
public:
    LoadScreen(const std::vector<std::string>* nameFiles);
    void showUpdatedScreen(int selectedMenuItem, int fileRemovedState = -1) const;
    std::string getScreenName() const;
    void reloadNameFiles(const std::vector<std::string> *nameFiles);
    int getMenuSize() const;
    void showMessage(const std::string& message) const;
    void clearScreen() const;
};


