#include <fstream>
#include <algorithm>
#include "DifficultDataReader.h"

const std::unordered_map<std::string, int> DifficultDataReader::strToTypeObject = {
        {"armor",      ThingObject::ARMOR},
        {"sword",      ThingObject::SWORD},
        {"healPotion", ThingObject::POTION_HEAL}
};

std::vector<std::string> DifficultDataReader::readLine(std::fstream &input) {
    std::vector<std::string> res;
    std::string str;
    getline(input, str);
    std::vector<int> separatePos;
    for (int i = 1; i < str.size(); ++i) {
        if (str[i - 1] == ';' && str[i] == ' ')
            separatePos.push_back(i - 1);
    }
    int separateArrIndex = 0;
    res.emplace_back("");
    if (separateArrIndex + 1 < separatePos.size()) {
        res.back().reserve(separatePos[separateArrIndex + 1] - separatePos[separateArrIndex]);
    }
    for (int i = 0; i < str.size(); ++i) {
        if (separateArrIndex != separatePos.size() && separatePos[separateArrIndex] == i) {
            i++;
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

std::vector<std::unordered_map<std::string, std::string>> DifficultDataReader::readSetData(std::fstream &input, int n) {
    auto paramsName = readLine(input);
    std::vector<std::unordered_map<std::string, std::string>> arraySetData;
    for (int i = 0; i < n; ++i) {
        auto paramsValue = readLine(input);
        if (paramsName.size() != paramsValue.size())
            throw std::invalid_argument("В файле несоответствие количества параметров и их значений");
        std::unordered_map<std::string, std::string> tempMap;
        for (int j = 0; j < paramsName.size(); ++j) {
            tempMap[paramsName[j]] = paramsValue[j];
        }
        arraySetData.push_back(tempMap);
    }
    return arraySetData;
}

std::unordered_map<std::string, CharacterProperties>
DifficultDataReader::readCharactersParams(std::fstream &input, int n) {
    auto charactersData = readSetData(input, n);
    std::unordered_map<std::string, CharacterProperties> charactersProperties;
    for (auto &item: charactersData) {
        CharacterProperties properties(
                item["name"],
                stoi(item["health"]),
                atof(item["attackPower"].c_str()),
                atof(item["protection"].c_str()),
                atof(item["luck"].c_str()),
                stoi(item["visibility"]),
                atof(item["criticalFactor"].c_str()),
                atof(item["dodgeFactor"].c_str()),
                stoi(item["percentForFollowToHero"]),
                stoi(item["lengthMove"])
        );
        charactersProperties.insert_or_assign(item["name"], properties);
    }
    return charactersProperties;
}

std::unordered_map<std::string, ThingProperties> DifficultDataReader::readThingsProperties(std::fstream &input, int n) {
    auto thingsData = readSetData(input, n);
    std::unordered_map<std::string, ThingProperties> thingsProperties;
    for (auto &item: thingsData) {
        ThingProperties properties(
                item.at("name"),
                std::map<std::string, double> {
                        {"damage",      atof(item["damage"].c_str()) },
                        {"protection",  atof(item["protection"].c_str()) },
                        {"luck",        atof(item["luck"].c_str()) },
                        {"health",      atof(item["health"].c_str()) }
                },
                stoi(item.at("level")),
                strToTypeObject.at(item.at("typeObject"))
        );
        thingsProperties.insert_or_assign(item["name"], properties);

    }
    return thingsProperties;
}

std::unordered_map<std::string, int> DifficultDataReader::readCntKilledEnemies(std::fstream &input, int n) {
    auto cntKilledEnemyData = readSetData(input, n);
    std::unordered_map<std::string, int> countersKilledEnemy;
    for (const auto &item: cntKilledEnemyData) {
        countersKilledEnemy[item.at("name")] = stoi(item.at("cnt"));
    }
    return countersKilledEnemy;
}

std::pair<std::string, DifficultPreset> DifficultDataReader::readRule(std::fstream &input) {
    std::pair<std::string, DifficultPreset> data;
    input >> data.first;
    input.get();
    if (std::count(data.first.begin(), data.first.end(), '-') == data.first.size()) // если стоит разделитель
        input >> data.first;
    std::string str;
    while (true) {
        auto preview = readLine(input);
        if(preview.size() == 0 || std::count(preview[0].begin(), preview[0].end(), '-') == preview[0].size())
            break; // если разделитель или пустая строка, то выходим
        if (preview[0] == "Characters") {
            data.second.setCharactersParams(readCharactersParams(input, stoi(preview[1])));
        } else if (preview[0] == "Things") {
            data.second.setThingsParams(readThingsProperties(input, stoi(preview[1])));
        } else if (preview[0] == "cntKilledEnemy") {
            data.second.setCntKilledEnemy(readCntKilledEnemies(input, stoi(preview[1])));
        } else {
            if (preview[0] == "cntEnemyOnField")
                data.second.setCntEnemyOnField(stoi(preview[1]));
            else if (preview[0] == "levelAllThings")
                data.second.setLevelAllThings(stoi(preview[1]));
            else if (preview[0] == "cntHealThing")
                data.second.setCntHealThing(stoi(preview[1]));
            else if (preview[0] == "timeBetweenGenerateEnemy")
                data.second.setTimeBetweenGenerateEnemy(stoi(preview[1]));
            else if (preview[0] == "timeBetweenGenerateVisualThing")
                data.second.setTimeBetweenGenerateVisualThing(stoi(preview[1]));
            else if (preview[0] == "timeBetweenGenerateHealThing")
                data.second.setTimeBetweenGenerateHealThing(stoi(preview[1]));
        }
    }
    return data;
}

std::unordered_map<std::string, DifficultPreset> DifficultDataReader::readRulesPresets(const std::string &nameFile) {
    std::fstream input(nameFile, std::ios_base::in);
    int cntDifficult;
    input >> cntDifficult;
    input.get();
    std::unordered_map<std::string, DifficultPreset> presets(cntDifficult);
    for (int i = 0; i < cntDifficult; ++i) {
        auto data = readRule(input);
        presets[data.first] = data.second;
    }
    return presets;
}
