#include <fstream>
#include <algorithm>
#include "DifficultDataReader.h"

std::string DifficultDataReader::startTag = "<start>";
std::string DifficultDataReader::endTag = "<end>";

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

std::vector<std::unordered_map<std::string, std::string>> DifficultDataReader::readSetData(std::fstream &input) {
    auto paramsName = readLine(input);
    std::vector<std::unordered_map<std::string, std::string>> arraySetData;
    if (readLine(input)[0] == startTag) {
        while (true) {
            auto lineValues = readLine(input);
            if (lineValues[0] == endTag)
                break;
            if (paramsName.size() != lineValues.size())
                throw std::invalid_argument("В файле несоответствие количества параметров и их значений");
            std::unordered_map<std::string, std::string> tempMap;
            for (int j = 0; j < paramsName.size(); ++j) {
                tempMap[paramsName[j]] = lineValues[j];
            }
            arraySetData.push_back(tempMap);
        }
    }
    return arraySetData;
}

std::unordered_map<std::string, CharacterProperties>
DifficultDataReader::readCharactersParams(std::fstream &input) {
    auto charactersData = readSetData(input);
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

std::unordered_map<std::string, ThingProperties> DifficultDataReader::readThingsProperties(std::fstream &input) {
    auto thingsData = readSetData(input);
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

std::unordered_map<std::string, int> DifficultDataReader::readCntKilledEnemies(std::fstream &input) {
    auto cntKilledEnemyData = readSetData(input);
    std::unordered_map<std::string, int> countersKilledEnemy;
    for (const auto &item: cntKilledEnemyData) {
        countersKilledEnemy[item.at("name")] = stoi(item.at("cnt"));
    }
    return countersKilledEnemy;
}

DifficultPreset DifficultDataReader::readRule(std::fstream &input) {
    DifficultPreset data;

    std::string str;
    while (true) {
        auto preview = readLine(input);
        if(preview.size() == 0 || std::count(preview[0].begin(), preview[0].end(), '-') == preview[0].size())
            break; // если разделитель или пустая строка, то выходим
        if (preview[0] == "Characters") {
            data.setCharactersParams(readCharactersParams(input));
        } else if (preview[0] == "Things") {
            data.setThingsParams(readThingsProperties(input));
        } else if (preview[0] == "cntKilledEnemy") {
            data.setCntKilledEnemy(readCntKilledEnemies(input));
        } else {
            if (preview[0] == "cntEnemyOnField")
                data.setCntEnemyOnField(stoi(preview[1]));
            else if (preview[0] == "levelAllThings")
                data.setLevelAllThings(stoi(preview[1]));
            else if (preview[0] == "cntHealThing")
                data.setCntHealThing(stoi(preview[1]));
            else if (preview[0] == "timeBetweenGenerateEnemy")
                data.setTimeBetweenGenerateEnemy(stoi(preview[1]));
            else if (preview[0] == "timeBetweenGenerateVisualThing")
                data.setTimeBetweenGenerateVisualThing(stoi(preview[1]));
            else if (preview[0] == "timeBetweenGenerateHealThing")
                data.setTimeBetweenGenerateHealThing(stoi(preview[1]));
        }
    }
    return data;
}

std::unordered_map<std::string, DifficultPreset> DifficultDataReader::readRulesPresets(const std::string &nameFile) {
    std::fstream input(nameFile, std::ios_base::in);
    auto line = readLine(input);
    if (line[0] != startTag)
        return {};
    std::unordered_map<std::string, DifficultPreset> presets;
    std::string namePreset;
    while (namePreset != endTag) {
         namePreset = readLine(input)[0];
        if (namePreset != endTag) {
            auto data = readRule(input);
            presets[namePreset] = data;
        } else
            break;
    }
    input.close();
    return presets;
}
