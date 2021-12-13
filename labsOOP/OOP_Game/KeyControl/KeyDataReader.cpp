#include "KeyboardDataReader.h"

std::string KeyboardDataReader::startTag = "<start>";
std::string KeyboardDataReader::endTag = "<end>";

std::unordered_map<std::string, std::unordered_map<std::string, char>>
KeyboardDataReader::readKeyboardSetting(const std::string &nameFile) {
    std::unordered_map<std::string, std::unordered_map<std::string, char>> keyboardSettings;
    std::fstream in(nameFile, std::ios_base::in);
    int cntLayer = 0;
    std::string screenName;
    if (readLine(in)[0] == startTag) {
        cntLayer++;
        while (cntLayer >= 1) {
            auto line = readLine(in);
            if (line[0] == startTag) {
                cntLayer++;
                continue;
            }
            else if (line[0] == endTag) {
                cntLayer--;
                continue;
            }
            if (cntLayer == 1) {
                screenName = line[0];
            } else if (cntLayer == 2) {
                keyboardSettings[screenName][line[0]] = line[1][0];
            }
        }

    }
    in.close();
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
