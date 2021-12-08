#pragma once

#include <map>
#include <unordered_map>
#include "KeyControl.h"

class KeyboardControl : public KeyControl {
    std::unordered_map<std::string, std::unordered_map<char, int>> heroKeysControl;
    static const std::unordered_map<std::string, std::unordered_map<std::string, int>> actionBind;
public:
    explicit KeyboardControl(const std::unordered_map<std::string, std::unordered_map<std::string, char>>& keyboardSettings);
    int requestKeyAction(const std::string &screen) override;
    char requestKeyChar() override;
    std::string requestKeyLine() override;
    void requestKeyIgnore() override;
    int requestKeyInt() override;
    bool checkRightAction(int action) const override;
    bool checkAllKeyBound() const override;
    bool resetBindChar(const std::string &screen, char newKey, int action) override;
    char getKey(const std::string &screen, int action) override;
    void requestTrashIgnore() override;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> getAllActionKeys() const override;
    std::unordered_map<std::string, std::unordered_map<char, int>> getAllKeysBound() const override;
    void clearInputState() override;
};


