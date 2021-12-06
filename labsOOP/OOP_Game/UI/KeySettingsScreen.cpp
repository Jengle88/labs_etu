#include <vector>
#include "KeySettingsScreen.h"

std::map<std::string, std::map<int, std::string>> KeySettingsScreen::actionBind;


void KeySettingsScreen::showUpdatedScreen(int selectedMenuItem) const {
    Printer::printMessage("Изменения будут применены после выхода\n");
    std::vector<std::string> keymap(sizeKeysControls);
    for (const auto &action: actionBind) {
        for (const auto &key: action.second) {
            std::string tempStr = key.second;
            tempStr.push_back(keysActionControl->at(action.first).at(key.first));
            keymap[key.first] = tempStr;
        }
    }
    Printer::printMenuWithChoice(keymap, selectedMenuItem);
}

std::string KeySettingsScreen::getScreenName() const {
    return "keySettingsScreen";
}

int KeySettingsScreen::getMenuSize() const {
    return sizeKeysControls;
}

void KeySettingsScreen::clearScreen() const {
    std::system("clear");
}

KeySettingsScreen::KeySettingsScreen(const std::unordered_map<std::string, std::unordered_map<int, char>> *keysActionControl,
                                     const std::unordered_map<std::string, std::unordered_map<std::string, int>>& actionBind)
                                     : keysActionControl(keysActionControl) {
    for (const auto &action: actionBind) {
        for (const auto &key: action.second) {
            maxSizeNameKeyBound = std::max(maxSizeNameKeyBound, (int)(action.first.size() + std::string(": ").size() + key.first.size()));
        }
    }
    maxSizeNameKeyBound += 3;
    for (const auto &action: actionBind) {
        for (const auto &key: action.second) {
            std::string tempStr;
            tempStr.resize(maxSizeNameKeyBound, ' ');
            int i;
            for (i = 0; i < action.first.size(); ++i) {
                tempStr[i] = action.first[i];
            }
            tempStr[i++] = ':';
            tempStr[i++] = ' ';
            int prevI = i;
            for (i; i - prevI < key.first.size(); ++i) {
                tempStr[i] = key.first[i - prevI];
            }
            i++;
            for (i; i < tempStr.size() - 1; ++i) {
                tempStr[i] = '.';
            }
            KeySettingsScreen::actionBind[action.first][key.second] = tempStr;
        }
    }
    sizeKeysControls = 0;
    for (const auto &keysControl: *keysActionControl) {
        sizeKeysControls += keysControl.second.size();
    }
}

std::string KeySettingsScreen::findNameScreenByAction(int action) const {
    for (const auto &actionControl: *keysActionControl) {
        if (actionControl.second.count(action))
            return actionControl.first;
    }
    return "";
}

void KeySettingsScreen::showMessage(const std::string &message) const {
    Printer::printMessage(message);
}
