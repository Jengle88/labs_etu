#pragma once

#include <map>
#include <unordered_map>
#include "KeyControl.h"

class KeyboardControl : public KeyControl {
    std::unordered_map<std::string, std::unordered_map<char, int>> heroKeysControl;
    static const std::unordered_map<std::string, std::unordered_map<std::string, int>> actionBind;
public:
    explicit KeyboardControl(const std::unordered_map<std::string, std::unordered_map<std::string, char>>& keyboardSettings);
    int requestKeyAction(const std::string &screen) const override;
    std::string requestKeyLine() const override;
    void requestKeyIgnore() const override;
    int requestKeyInt() const override;
    bool checkRightAction(int action) const override;
    bool checkAllKeyBound() const override;
    bool resetBindChar(const std::string &screen, char key, int action) override;
    char getKey(const std::string &screen, int action) const override;
    void requestTrashIgnore() const override;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> getAllActionKeys() const override;
    std::unordered_map<std::string, std::unordered_map<char, int>> getAllKeysBound() const override;
//    std::unordered_map<std::string, std::unordered_map<std::string, char>> getAllActionKeys() const override;
//    std::unordered_map<std::string, std::unordered_map<int, char>> getAllKeysBound() const override;
    void clearInputState() const override;
};


