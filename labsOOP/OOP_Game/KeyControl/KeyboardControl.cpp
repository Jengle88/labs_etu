#include <iostream>
#include <vector>
#include <algorithm>
#include "KeyboardControl.h"

const std::unordered_map<std::string, std::unordered_map<std::string, int>> KeyboardControl::actionBind = {
        {"startScreen", {
                {"selectMenuUp", START_SELECT_MENU_UP},
                {"selectMenuDown", START_SELECT_MENU_DOWN},
                {"goToMenu", START_GO_TO_MENU}
        }},
        {"fieldScreen", {
                {"moveUp", FIELD_MOVE_UP},
                {"moveLeft", FIELD_MOVE_LEFT},
                {"moveRight", FIELD_MOVE_RIGHT},
                {"moveDown", FIELD_MOVE_DOWN},
                {"takeThing", FIELD_TAKE_THING},
                {"startFight", FIELD_START_FIGHT},
                {"finishOut", FIELD_FINISH_OUT},
                {"exitField", FIELD_EXIT_FIELD},
                {"acceptGenerate", FIELD_ACCEPT_GENERATE},
                {"cancelGenerate", FIELD_CANCEL_GENERATE}
        }},
        {"fightScreen", {
                {"attackEnemy", FIGHT_ATTACK_ENEMY},
                {"selectThingUp", FIGHT_SELECT_THING_UP},
                {"selectThingDown", FIGHT_SELECT_THING_DOWN},
                {"useThing", FIGHT_USE_THING},
                {"exitFight", FIGHT_EXIT_FIGHT},
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
            heroKeysControl[keyboardSetting.first][setting.second] = actionBind.at(keyboardSetting.first).at(
                    setting.first);
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

//std::unordered_map<std::string, std::unordered_map<std::string, char>> KeyboardControl::getAllActionKeys() const {
//    std::unordered_map<std::string, std::unordered_map<std::string, char>> keymap;
//    std::vector<char> keysBound(HeroKeysControl::SIZE_HERO_KEYS_CONTROL);
//    for (const auto &actionKeys: heroKeysControl) {
//        for (const auto &key: actionKeys.second) {
//            keysBound[key.second] = key.first;
//        }
//    }
//    for (const auto &actionKeys: actionBind) {
//        for (const auto &key: actionKeys.second) {
//            keymap[actionKeys.first][key.first] = keysBound[key.second];
//        }
//    }
//    return keymap;
//}
//
//std::unordered_map<std::string, std::unordered_map<int, char>> KeyboardControl::getAllKeysBound() const {
//    std::unordered_map<std::string, std::unordered_map<int, char>> keysBound;
//    for (const auto &keyControl: heroKeysControl) {
//        for (const auto &item: keyControl.second) {
//            keysBound[keyControl.first][item.second] = item.first;
//        }
//    }
//    return keysBound;
//}

std::unordered_map<std::string, std::unordered_map<std::string, int>> KeyboardControl::getAllActionKeys() const {
    return actionBind;
}

std::unordered_map<std::string, std::unordered_map<char, int>> KeyboardControl::getAllKeysBound() const {
    return heroKeysControl;
}
