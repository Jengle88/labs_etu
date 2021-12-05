#include "KeyboardDataReader.h"

std::unordered_map<std::string, std::unordered_map<std::string, char>>
KeyboardDataReader::readKeyboardSetting(const std::string &nameFile) {
    std::unordered_map<std::string, std::unordered_map<std::string, char>> keyboardSettings;
    std::fstream in(nameFile, std::ios_base::in);
    int countScreen = std::stoi(readLine(in)[0]);
    for (int i = 0; i < countScreen; ++i) {
        auto screen = readLine(in);
        std::unordered_map<std::string, char> screenKeyboardSetting;
        int cntSettings = std::stoi(screen[1]);
        for (int j = 0; j < cntSettings; ++j) {
            auto keySettings = readLine(in);
            screenKeyboardSetting[keySettings[0]] = keySettings[1][0];
        }
        keyboardSettings[screen[0]] = screenKeyboardSetting;
    }
    return keyboardSettings;
}

std::vector<std::string> KeyboardDataReader::readLine(std::fstream &input) {
    std::vector<std::string> res;
    std::string str;
    getline(input, str);
    std::vector<int> separatePos;
    for (int i = 1; i < str.size(); ++i) {
        if (str[i] == ' ')
            separatePos.push_back(i);
    }
    int separateArrIndex = 0;
    res.emplace_back("");
    if (separateArrIndex + 1 < separatePos.size()) {
        res.back().reserve(separatePos[separateArrIndex + 1] - separatePos[separateArrIndex]);
    }
    for (int i = 0; i < str.size(); ++i) {
        if (separateArrIndex != separatePos.size() && separatePos[separateArrIndex] == i) {
//            i++;
            res.emplace_back("");
            if (separateArrIndex + 1 < separatePos.size()) {
                res.back().reserve(separatePos[separateArrIndex + 1] - separatePos[separateArrIndex]);
            }
            separateArrIndex++;
        } else
            res.back().push_back(str[i]);
    }
    if (res.back().empty())
        return {};
    else
        return res;
}
