#include <iostream>
#include <vector>
#include <algorithm>
#include "KeyboardControl.h"

const std::unordered_map<std::string, std::unordered_map<std::string, int>> KeyboardControl::actionBind = {
        {"fieldScreen", {
                                {"moveUp", MOVE_UP},
                                {"moveLeft", MOVE_LEFT},
                                {"moveRight", MOVE_RIGHT},
                                {"moveDown", MOVE_DOWN},
                                {"takeThing", TAKE_THING},
                                {"startFight", START_FIGHT},
                                {"finishOut", FINISH_OUT},
                                {"exitField", EXIT_FIELD},
                                {"accept", ACCEPT},
                                {"cancel", CANCEL}
                        }},
        {"fightScreen", {
                                {"attackEnemy", ATTACK_ENEMY},
                                {"selectThingUp", SELECT_THING_UP},
                                {"selectThingDown", SELECT_THING_DOWN},
                                {"useThing", USE_THING},
                                {"exitFight", EXIT_FIGHT},
                        }}
};

int KeyboardControl::requestKeyAction(const std::string &screen) const {
    char key = getchar();
    if (heroKeysControl.count(screen) == 0)
        return -1;
    if (heroKeysControl.at(screen).count(key)) {
        return heroKeysControl.at(screen).at(key);
    }
    return -1;
}

int KeyboardControl::requestKeyInt() const {
    int num;
    std::cin >> num;
    if (std::cin.fail()) {
        requestTrashIgnore();
        clearInputState();
        throw std::invalid_argument("Не получилось считать число!");
    }
    return num;
}

std::string KeyboardControl::requestKeyLine() const {
    std::string str;
    getline(std::cin, str);
    return str;
}

bool KeyboardControl::checkRightAction(int action) const {
    return 0 <= action && action < SIZE_HERO_KEYS_CONTROL;
}

bool KeyboardControl::resetBindChar(const std::string &screen, char key, int action) {
    if (heroKeysControl.count(screen) == 0 || heroKeysControl[screen].count(key) == 0)
        return false;
    if (checkRightAction(action)) {
        heroKeysControl[screen][key] = action;
        return true;
    }
    return false;
}

bool KeyboardControl::checkAllKeyBound() const {
    std::vector<bool> actions(SIZE_HERO_KEYS_CONTROL);
    for (const auto &screen: heroKeysControl) {
        for (const auto &key: screen.second) {
            actions[key.second] = true;
        }
    }
    bool ok = true;
    for (const auto &item: actions) {
        ok &= item;
    }
    return ok;
}

void KeyboardControl::requestKeyIgnore() const {
    char z = getchar();
}

KeyboardControl::KeyboardControl(
        const std::unordered_map<std::string, std::unordered_map<std::string, char>> &keyboardSettings) {
    for (const auto &keyboardSetting: keyboardSettings) {
        for (const auto &setting: keyboardSetting.second) {
            heroKeysControl[keyboardSetting.first][setting.second] = actionBind.at(keyboardSetting.first).at(setting.first);
        }
    }
}

char KeyboardControl::getKey(const std::string &screen, int action) const {
    if (heroKeysControl.count(screen) == 0 || !checkRightAction(action)) {
        return '?';
    }
    auto begin = heroKeysControl.at(screen).begin();
    auto end = heroKeysControl.at(screen).end();
    for (auto iter = begin; iter != end; ++iter) {
        if (iter->second == action)
            return iter->first;
    }
    return '?';
}

void KeyboardControl::clearInputState() const {
    std::cin.clear();
}

void KeyboardControl::requestTrashIgnore() const {
    std::cin.ignore(32767, '\n');
}
