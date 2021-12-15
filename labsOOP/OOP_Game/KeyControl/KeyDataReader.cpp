#include "KeyDataReader.h"

const std::string KeyDataReader::START_TAG = "<start>";
const std::string KeyDataReader::END_TAG = "<end>";

std::unordered_map<std::string, std::unordered_map<std::string, char>>
KeyDataReader::readKeysSettings(const std::string &nameFile) {
    std::unordered_map<std::string, std::unordered_map<std::string, char>> keySettings;
    std::fstream in(nameFile, std::ios_base::in);
    int cntLayer = 0;
    std::string screenName;
    if (readLine(in)[0] == START_TAG) {
        cntLayer++;
        while (cntLayer >= 1) {
            auto line = readLine(in);
            if (line[0] == START_TAG) {
                cntLayer++;
                continue;
            }
            else if (line[0] == END_TAG) {
                cntLayer--;
                continue;
            }
            if (cntLayer == 1) {
                screenName = line[0];
            } else if (cntLayer == 2) {
                keySettings[screenName][line[0]] = line[1][0];
            }
        }

    }
    in.close();
    return keySettings;
}

std::vector<std::string> KeyDataReader::readLine(std::fstream &input) {
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
