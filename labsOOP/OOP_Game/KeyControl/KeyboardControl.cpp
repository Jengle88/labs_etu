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
                {"exitFight", FIGHT_EXIT_FIGHT}
        }},
        {"keySettingsScreen", {
                {"selectMenuUp", KEYSETTINGS_SELECT_MENU_UP},
                {"selectMenuDown", KEYSETTINGS_SELECT_MENU_DOWN},
                {"changeBind", KEYSETTINGS_CHANGE_BIND},
                {"exitSettings", KEYSETTINGS_EXIT_SETTINGS}
        }}
};

KeyboardControl::KeyboardControl(
        const std::unordered_map<std::string, std::unordered_map<std::string, char>> &keyboardSettings) {
    for (const auto &keyboardSetting: keyboardSettings) {
        for (const auto &setting: keyboardSetting.second) {
            heroKeysControl[keyboardSetting.first][setting.second] = actionBind.at(keyboardSetting.first).at(
                    setting.first);
        }
    }
}

int KeyboardControl::requestKeyAction(const std::string &screen) {
    char key = std::cin.get();
    if (heroKeysControl.count(screen) == 0)
        return -1;
    if (heroKeysControl.at(screen).count(key)) {
        return heroKeysControl.at(screen).at(key);
    }
    return -1;
}

char KeyboardControl::requestKeyChar() {
    return std::cin.get();
}

int KeyboardControl::requestKeyInt() {
    int num;
    std::cin >> num;
    if (std::cin.fail()) {
        clearInputState();
        requestTrashIgnore();
        throw std::invalid_argument("Не получилось считать число!");
    }
    return num;
}

std::string KeyboardControl::requestKeyLine() {
    std::string str;
    getline(std::cin, str);
    return str;
}

bool KeyboardControl::checkRightAction(int action) const {
    return 0 <= action && action < SIZE_PLAYER_KEYS_CONTROL;
}

bool KeyboardControl::resetBindChar(const std::string &screen, int action, char newKey) {
    if (heroKeysControl.count(screen) == 0 || heroKeysControl[screen].count(newKey))
        return false;
    auto prevKeyPosition = std::find_if(heroKeysControl[screen].begin(), heroKeysControl[screen].end(), [action](const auto& item){
        return item.second == action;
    });
    heroKeysControl[screen].erase(prevKeyPosition);
    heroKeysControl[screen][newKey] = action;
    return true;
}

bool KeyboardControl::checkAllKeyBound() const {
    std::vector<bool> actions(SIZE_PLAYER_KEYS_CONTROL);
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

void KeyboardControl::requestKeyIgnore() {
    char z = std::cin.get(); // char z удобно для отладки, чтобы посмотреть считанный символ
}

char KeyboardControl::getKeyByAction(const std::string &screen, int action) {
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

void KeyboardControl::clearInputState() {
    std::cin.clear();
}

void KeyboardControl::requestTrashIgnore() {
    std::cin.ignore(32767, '\n');
}

std::unordered_map<std::string, std::unordered_map<std::string, int>> KeyboardControl::getAllActionsNameId() const {
    return actionBind;
}

std::unordered_map<std::string, std::unordered_map<char, int>> KeyboardControl::getAllBindKeysId() const {
    return heroKeysControl;
}
